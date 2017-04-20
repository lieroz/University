#ifndef UPLOAD_MANAGER_HPP
#define UPLOAD_MANAGER_HPP

#include "abstract_manager.hpp"
#include "upload/uploader.hpp"

class upload_manager : public abstract_manager {
    public:
        upload_manager() = default;
        upload_manager(upload_manager&) = delete;
        upload_manager(const upload_manager&) = delete;
        ~upload_manager() = default;

        model upload_model(const std::string& file_name) {
            uploader upldr(file_name);
            upldr.open();
            upldr.serialize_json();
            upldr.close();

            return upldr.deserialize_json();
        }
};

#endif // UPLOAD_MANAGER_HPP
