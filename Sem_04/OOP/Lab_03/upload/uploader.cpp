#include "uploader.hpp"

uploader::uploader(std::string file_name) : file_name(file_name) {
    input_stream.exceptions(std::ifstream::badbit);
}

int uploader::json_equal(const char* json_str, jsmntok_t* token, const char* str) {
    if (token->type == JSMN_STRING && static_cast<int>(strlen(str)) == token->end - token->start &&
        strncmp(json_str + token->start, str, token->end - token->start) == 0) {
        return 0;
    }

    return -1;
}

pair<int, point3d<double>> uploader::get_point(int i, jsmntok_t* buffer, int offset) {
    int id = std::stoi(std::string(this->json_string.c_str() + buffer[i + 1 + offset].start,
                                   this->json_string.c_str() + buffer[i + 1 + offset].end));

    if (buffer[i + 3 - offset].type != JSMN_ARRAY) {
        throw json_exception("uploader::jsmn(object is not of type ARRAY)!");
    }

    vector<double> vec;

    for (int j = 0; j < buffer[i + 3 - offset].size; ++j) {
        jsmntok_t* element = &buffer[i + j + 4 - offset];
        vec.push_back(std::stod(std::string(this->json_string.c_str() + element->start,
                                            this->json_string.c_str() + element->end)));
    }

    return pair<int, point3d<double>>(id, point3d<double>(vec[0], vec[1], vec[2]));
}

pair<int, vector<int>> uploader::get_link(int i, jsmntok_t* buffer, int offset) {
    int id = std::stoi(std::string(this->json_string.c_str() + buffer[i + 1 + offset].start,
                                   this->json_string.c_str() + buffer[i + 1 + offset].end));

    if (buffer[i + 3 - offset].type != JSMN_ARRAY) {
        throw json_exception("uploader::jsmn(object is not of type ARRAY)!");
    }

    vector<int> vec;

    for (int j = 0; j < buffer[i + 3 - offset].size; ++j) {
        jsmntok_t* element = &buffer[i + j + 4 - offset];
        vec.push_back(std::stoi(std::string(this->json_string.c_str() + element->start,
                                            this->json_string.c_str() + element->end)));
    }

    return pair<int, vector<int>>(id, vec);
}

void uploader::open() {
    try {
        this->input_stream.open(this->file_name);

    } catch (std::ifstream::failure& e) {
        throw open_stream_exception();
    }
}

void uploader::serialize_json() {
    if (this->input_stream.is_open()) {

        try {
            std::string buffer;

            while (this->input_stream >> buffer) {
                this->json_string += buffer;
            }

        } catch (std::ifstream::failure& e) {
            input_stream.close();
            throw read_stream_exception();
        }
    }
}

model uploader::deserialize_json() {
    jsmntok_t buffer[this->json_string.size()];
    jsmn_init(&this->json_parser);
    const int root_keys_count = jsmn_parse(&this->json_parser, this->json_string.c_str(),
                                           this->json_string.size(), buffer, sizeof(buffer) / sizeof(*buffer));
    std::string model_name;
    vector<pair<int, point3d<double>>> points;
    vector<pair<int, vector<int>>> links;

    if (root_keys_count < 0) {
        throw json_exception("uploader::jsmn(empty document)!");
    }

    if (root_keys_count < 1 || (*buffer).type != JSMN_OBJECT) {
        throw json_exception("uploader::jsmn(object is not of type OBJECT)!");
    }

    for (int i = 1; i < root_keys_count; ++i) {

        if (json_equal(this->json_string.c_str(), &buffer[i], "object_name") == 0) {
            model_name = std::string(this->json_string.c_str() + buffer[i + 1].start,
                                     this->json_string.c_str() + buffer[i + 1].end);
            ++i;

        } else if (json_equal(this->json_string.c_str(), &buffer[i], "point") == 0) {
            i += 2;
            std::function<pair<int, point3d<double>>(int, jsmntok_t*, int)> func =
                                                      std::bind(&uploader::get_point, this, std::placeholders::_1,
                                                                std::placeholders::_2, std::placeholders::_3);
            this->import_data<pair<int, point3d<double>>>(points, i, buffer, func, "id", "coordinates");
            i += 6;

        } else if (json_equal(this->json_string.c_str(), &buffer[i], "link") == 0) {
            i += 2;
            std::function<pair<int, vector<int>>(int, jsmntok_t*, int)> func =
                                                  std::bind(&uploader::get_link, this, std::placeholders::_1,
                                                            std::placeholders::_2, std::placeholders::_3);
            this->import_data<pair<int, vector<int>>>(links, i, buffer, func, "id", "connections");
            i += 6;

        } else {
            throw json_exception("uploader::jsmn(corrupted document)!");
        }
    }

    vector<pair<point3d<double>, point3d<double>>> lines;
    vector<point3d<double>> normalized_points;

    retrieve_lines(lines, points, links);
    normalize_points(points, normalized_points);

    return model(model_name, lines, normalized_points);
}

void uploader::retrieve_lines(vector<pair<point3d<double>, point3d<double>>>& lines, vector<pair<int, point3d<double>>>& points,
                    vector<pair<int, vector<int>>>& links) {
    for (size_t i = 0; i < links.size(); ++i) {

        for (size_t k = 0; k < points.size(); ++k) {

            if (links.at(i).get_first() == points.at(k).get_first()) {

                for (size_t j = 0; j < links.at(i).get_second().size(); ++j) {

                    for (size_t w = 0; w < points.size(); ++w) {

                        if (links.at(i).get_second()[j] == points.at(w).get_first()) {
                            point3d<double> p1 = points.at(k).get_second();
                            point3d<double> p2 = points.at(w).get_second();
                            lines.push_back(pair<point3d<double>, point3d<double>>(p1, p2));
                        }
                    }
                }
            }
        }
    }
}

void uploader::normalize_points(vector<pair<int, point3d<double>>>& pair_points, vector<point3d<double>>& points) {
    for (size_t i = 0; i < pair_points.size(); ++i) {
        points.push_back(pair_points.at(i).get_second());
    }
}

void uploader::close() {
    try {
        this->input_stream.close();

    } catch (std::ifstream::failure& e) {
        throw close_stream_exception();
    }
}
