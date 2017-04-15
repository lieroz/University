#ifndef UPLOAD_EXCEPTIONS_HPP
#define UPLOAD_EXCEPTIONS_HPP

#include "base_exception.hpp"

class base_stream_exception : base_exception {
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
