#ifndef UPLOAD_EXCEPTIONS_HPP
#define UPLOAD_EXCEPTIONS_HPP

#include <exception>
#include <string>

class base_stream_exception : public std::exception {
    public:
        virtual const char* what() const noexcept {
            return "uploader::(base stream exception)!";
        }
};

class open_stream_exception : public base_stream_exception {
    public:
        virtual const char* what() const noexcept {
            return "uploader::(opening stream exception)!";
        }
};

class read_stream_exception : public base_stream_exception {
    public:
        virtual const char* what() const noexcept {
            return "uploader::(reading stream exception)!";
        }
};

class close_stream_exception : public base_stream_exception {
    public:
        virtual const char* what() const noexcept {
            return "uploader::(closing stream exception)!";
        }
};

#endif // UPLOAD_EXCEPTIONS_HPP
