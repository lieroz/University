//
// Created by lieroz on 29.03.17.
//

#ifndef LAB_02_EXCEPTIONS_HPP
#define LAB_02_EXCEPTIONS_HPP

#include <exception>

class base_exception : public std::exception {
	protected:
		std::string message;
		
	public:
		explicit base_exception() = default;
		
		explicit base_exception(const char* message) {
			this->message = message;
		}
		
		explicit base_exception(std::string& message) {
			this->message = message;
		}
};

class bad_memory_allocation_exception : public base_exception {
	public:
		explicit bad_memory_allocation_exception() = default;
		
		explicit bad_memory_allocation_exception(const char* message)
				: base_exception(message) {
		}
		
		explicit bad_memory_allocation_exception(std::string& message)
				: base_exception(message) {
		}
		
		virtual const char* what() const noexcept {
			return message.empty() ? "Memory allocation error!" : message.c_str();
		}
};

class out_of_range_exception : public base_exception {
	public:
		explicit out_of_range_exception() = default;
		
		explicit out_of_range_exception(const char* message)
				: base_exception(message) {
		}
		
		explicit out_of_range_exception(std::string& message)
				: base_exception(message) {
		}
		
		virtual const char* what() const noexcept {
			return message.empty() ? "Accessed position is out of range!" : message.c_str();
		}
};

class item_not_found_exception : public base_exception {
	public:
		explicit item_not_found_exception() = default;
		
		explicit item_not_found_exception(const char* message)
				: base_exception(message) {
		}
		
		explicit item_not_found_exception(std::string& message)
				: base_exception(message) {
		}
		
		virtual const char* what() const noexcept {
			return message.empty() ? "Item not found!" : message.c_str();
		}
};

#endif //LAB_02_EXCEPTIONS_HPP
