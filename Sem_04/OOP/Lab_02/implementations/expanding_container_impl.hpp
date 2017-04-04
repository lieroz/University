//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_EXPANDING_CONTAINER_IMPL_HPP
#define LAB_02_EXPANDING_CONTAINER_IMPL_HPP

#include <exceptions.hpp>
#include "expanding_container.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		expanding_container<__Tp>::expanding_container()
				: __mem_dump(__BASE_SIZE) {
			try {
				this->__buffer = new __Tp[this->capacity()];
			
			} catch (std::bad_alloc& ex) {
				throw bad_memory_allocation_exception();
			}
		}
		
		template <class __Tp>
		expanding_container<__Tp>::expanding_container(size_t count)
				: base_container(count), __mem_dump(count) {
			try {
				this->__buffer = new __Tp[this->capacity()];
				
			} catch (std::bad_alloc& ex) {
				throw bad_memory_allocation_exception();
			}
		}
		
		template <class __Tp>
		expanding_container<__Tp>::expanding_container(size_t count, const __Tp& value)
				: expanding_container(count) {
			for (size_t i = 0; i < this->size(); ++i) {
				(*this)[i] = value;
			}
		}
		
		template <class __Tp>
		expanding_container<__Tp>::expanding_container(iterator first, iterator last)
				: expanding_container(last - first) {
			for (size_t i = 0; i < this->size(); ++i, ++first) {
				(*this)[i] = *first;
			};
		}
		
		template <class __Tp>
		expanding_container<__Tp>::expanding_container(const_iterator first, const_iterator last)
				: expanding_container(last - first) {
			for (size_t i = 0; i < this->size(); ++i, ++first) {
				(*this)[i] = *first;
			};
		}
		
		template <class __Tp>
		expanding_container<__Tp>::expanding_container(std::initializer_list<__Tp> lst)
				: expanding_container(lst.size()) {
			std::copy(lst.begin(), lst.end(), this->__buffer);
		}
		
		template <class __Tp>
		expanding_container<__Tp>::expanding_container(const expanding_container<__Tp>& other)
				: expanding_container(other.size()) {
			std::copy(other.__buffer, other.__buffer + other.size(), this->__buffer);
		}
		
		template <class __Tp>
		expanding_container<__Tp>::expanding_container(expanding_container<__Tp>&& other)
				:  ftl_core::base_container(other.size()), __mem_dump(other.capacity()), __buffer(other.__buffer) {
			other.__el_count = 0;
			other.__mem_dump = 0;
			other.__buffer = nullptr;
		}
		
		template <class __Tp>
		expanding_container<__Tp>::~expanding_container() {
			delete[] this->__buffer;
			this->__mem_dump = 0;
			this->__buffer = nullptr;
		}
		
		template <class __Tp>
		expanding_container<__Tp>& expanding_container<__Tp>::operator=(const expanding_container<__Tp>& rhs) {
			if (this != &rhs) {
				this->__el_count = rhs.size();
				this->__mem_dump = rhs.capacity();
				
				try {
					this->__buffer = new __Tp[this->capacity()];
					
				} catch (std::bad_alloc& ex) {
					throw bad_memory_allocation_exception();
				}
				
				std::copy(this->__buffer, this->__buffer + this->size(), this->begin());
			}
			
			return *this;
		}
		
		template <class __Tp>
		expanding_container<__Tp>& expanding_container<__Tp>::operator=(expanding_container<__Tp>&& rhs) {
			if (this != &rhs) {
				this->__el_count = rhs.size();
				this->__mem_dump = rhs.capacity();
				this->__buffer = (std::move(rhs.__buffer));
				
				rhs.__el_count = 0;
				rhs.__mem_dump = 0;
				rhs.__buffer = nullptr;
			}
			
			return *this;
		}
		
		template <class __Tp>
		expanding_container<__Tp>& expanding_container<__Tp>::operator=(std::initializer_list<__Tp> lst) {
			this->expanding_container(lst);
			return *this;
		}
		
		template <class __Tp>
		__Tp& expanding_container<__Tp>::at(size_t pos) {
			if (pos < this->size()) {
				return (*this)[pos];
				
			} else {
				throw out_of_range_exception();
			}
		}
		
		template <class __Tp>
		const __Tp& expanding_container<__Tp>::at(size_t pos) const {
			if (pos < this->size()) {
				return (*this)[pos];
				
			} else {
				throw out_of_range_exception();
			}
		}
		
		template <class __Tp>
		__Tp& expanding_container<__Tp>::operator[](size_t pos) {
			if (pos < this->size()) {
				return this->__buffer[pos];
				
			} else {
				throw out_of_range_exception();
			}
		}
		
		template <class __Tp>
		const __Tp& expanding_container<__Tp>::operator[](size_t pos) const {
			if (pos < this->size()) {
				return this->__buffer[pos];
				
			} else {
				throw std::out_of_range("Accessed position is out of range!");
			}
		}
		
		template <class __Tp>
		typename expanding_container<__Tp>::iterator expanding_container<__Tp>::begin() {
			return iterator(this->__buffer);
		}
		
		template <class __Tp>
		typename expanding_container<__Tp>::const_iterator expanding_container<__Tp>::cbegin() const {
			return const_iterator(this->__buffer);
		}
		
		template <class __Tp>
		typename expanding_container<__Tp>::iterator expanding_container<__Tp>::end() {
			return iterator(this->__buffer + this->size());
		}
		
		template <class __Tp>
		typename expanding_container<__Tp>::const_iterator expanding_container<__Tp>::cend() const {
			return const_iterator(this->__buffer + this->size());
		}
		
		template <class __Tp>
		typename expanding_container<__Tp>::iterator expanding_container<__Tp>::rbegin() {
			return iterator(this->__buffer + this->size() - 1);
		}
		
		template <class __Tp>
		typename expanding_container<__Tp>::const_iterator expanding_container<__Tp>::rcbegin() const {
			return const_iterator(this->__buffer + this->size() - 1);
		}
		
		template <class __Tp>
		typename expanding_container<__Tp>::iterator expanding_container<__Tp>::rend() {
			return iterator(this->__buffer - 1);
		}
		
		template <class __Tp>
		typename expanding_container<__Tp>::const_iterator expanding_container<__Tp>::rcend() const {
			return const_iterator(this->__buffer - 1);
		}
		
		template <class __Tp>
		size_t expanding_container<__Tp>::capacity() const {
			return this->__mem_dump;
		}
		
		template <class __Tp>
		void expanding_container<__Tp>::clear() {
			for (size_t i = 0; i < this->size(); ++i) {
				(*this)[i].~__Tp();
			}
			
			this->__el_count = 0;
		}
		
		template <class __Tp>
		inline void expanding_container<__Tp>::reallocate() {
			try {
				__Tp* __temp_buffer = new __Tp[this->capacity()];
				std::copy(this->__buffer, this->__buffer + this->size(), __temp_buffer);
				delete[] this->__buffer;
				this->__buffer = __temp_buffer;
				
			} catch (std::bad_alloc& ex) {
				throw bad_memory_allocation_exception();
			}
		}
		
		template <class __Tp>
		void expanding_container<__Tp>::swap(expanding_container<__Tp>& other) {
			std::swap(this->__el_count, other.__el_count);
			std::swap(this->__mem_dump, other.__mem_dump);
			std::swap(this->__buffer, other.__buffer);
		}
		
		template <class __Tp>
		void swap(expanding_container<__Tp>& lhs, expanding_container<__Tp>& rhs) {
			lhs.swap(rhs);
		}
		
		template <class __Tp>
		bool operator==(const expanding_container<__Tp>& lhs, const expanding_container<__Tp>& rhs) {
			bool are_equal = lhs.size() == rhs.size();
			
			if (are_equal) {
				
				for (size_t i = 0; i < lhs.size() && are_equal; ++i) {
					
					if (lhs[i] != rhs[i]) {
						are_equal = false;
					}
				}
			}
			
			return are_equal;
		}
		
		template <class __Tp>
		bool operator!=(const expanding_container<__Tp>& lhs, const expanding_container<__Tp>& rhs) {
			return !(rhs == lhs);
		}
		
		template <class __Tp>
		bool operator<(const expanding_container<__Tp>& lhs, const expanding_container<__Tp>& rhs) {
			bool is_less = lhs.size() < rhs.size();
			
			if (!is_less && lhs.size() == rhs.size()) {
				
				for (size_t i = 0; i < lhs.size() && !is_less; ++i) {
					
					if (lhs[i] < rhs[i]) {
						is_less = true;
					}
				}
			}
			
			return is_less;
		}
		
		template <class __Tp>
		bool operator<=(const expanding_container<__Tp>& lhs, const expanding_container<__Tp>& rhs) {
			return lhs < rhs || lhs == rhs;
		}
		
		template <class __Tp>
		bool operator>(const expanding_container<__Tp>& lhs, const expanding_container<__Tp>& rhs) {
			return !(lhs < rhs) && !(lhs == rhs);
		}
		
		template <class __Tp>
		bool operator>=(const expanding_container<__Tp>& lhs, const expanding_container<__Tp>& rhs) {
			return lhs > rhs || lhs == rhs;
		}
		
		template <class __Tp>
		std::ostream& operator<<(std::ostream& stream, const expanding_container<__Tp>& vec) {
			for (typename expanding_container<__Tp>::const_iterator iter = vec.cbegin(); iter != vec.cend(); ++iter) {
				std::cout << *iter << " ";
			}
			
			return stream;
		}
	}
}

#endif //LAB_02_EXPANDING_CONTAINER_IMPL_HPP
