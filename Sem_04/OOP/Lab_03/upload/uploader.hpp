#ifndef UPLOADER_HPP
#define UPLOADER_HPP

#include <fstream>
#include <cstring>
#include <functional>

#include "../exceptions/upload_exceptions.hpp"
#include "../containers/vector/vector.hpp"
#include "../containers/pair/pair.hpp"
#include "../objects/model.hpp"
#include "../3dparty/jsmn.h"

class uploader {
    public:
        explicit uploader(std::string);
        virtual ~uploader() = default;

        void open();
        void serialize_json();
        model deserialize_json();
        void close();

    protected:
        static int json_equal(const char*, jsmntok_t*, const char*);

        pair<int, point3d<double>> get_point(int, jsmntok_t*, int);
        pair<int, vector<int>> get_link(int, jsmntok_t*, int);

        template <class T>
        void import_data(vector<T>&, int, jsmntok_t*, std::function<T(int, jsmntok_t*, int)>&, const char*, const char*);

        void retrieve_lines(vector<pair<point3d<double>, point3d<double>>>&,
                            vector<pair<int, point3d<double>>>&,
                            vector<pair<int, vector<int>>>&);

        void normalize_points(vector<pair<int, point3d<double>>>&,
                                        vector<point3d<double>>&);

    private:
        std::string file_name;
        std::ifstream input_stream;
        std::string json_string;
        jsmn_parser json_parser;
};

template<class T>
void uploader::import_data(vector<T>& data, int i, jsmntok_t* buffer,
                           std::function<T (int, jsmntok_t*, int)>& func, const char* str1, const char* str2) {
    if (json_equal(this->json_string.c_str(), &buffer[i], str1) == 0 &&
        json_equal(this->json_string.c_str(), &buffer[i + 2], str2) == 0) {
        data.push_back(func(i, buffer, 0));

    } else if (json_equal(this->json_string.c_str(), &buffer[i], str2) == 0 &&
               json_equal(this->json_string.c_str(), &buffer[i + 2], str1) == 0) {
        data.push_back(func(i, buffer, 2));

    } else {
        throw json_exception("uploader::jsmn(corrupted data)!");
    }
}

#endif // UPLOADER_HPP
