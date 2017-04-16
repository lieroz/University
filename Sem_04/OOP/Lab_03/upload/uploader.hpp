#ifndef UPLOADER_HPP
#define UPLOADER_HPP

#include <fstream>

#include "../exceptions/upload_exceptions.hpp"
#include "../container/vector/vector.hpp"

class uploader {
    public:
        uploader(std::string&);
        ~uploader() = delete;

        void open();
        template <class T>
        vector<T> read();
        void close();

    private:
        std::string file_name;
        std::ifstream input_stream;
};

uploader::uploader(std::string& file_name) : file_name(file_name) {
    input_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
}

void uploader::open() {
    try {
        this->input_stream.open(this->file_name);

    } catch (std::ifstream::failure& e) {
        throw open_stream_exception();
    }
}

template <class T>
vector<T> uploader::read() {
    vector<T> result;

    if (this->input_stream.is_open()) {
        T buffer = T();

        try {

            while (this->input_stream >> buffer) {
                result.push_back(buffer);
            }

        } catch (std::ifstream::failure& e) {
            input_stream.close();
            throw read_stream_exception();
        }
    }

    return result;
}

void uploader::close() {
    try {
        this->input_stream.close();

    } catch (std::ifstream::failure& e) {
        throw close_stream_exception();
    }
}

#endif // UPLOADER_HPP
