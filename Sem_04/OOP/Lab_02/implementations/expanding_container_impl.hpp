//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_EXPANDING_CONTAINER_IMPL_HPP
#define LAB_02_EXPANDING_CONTAINER_IMPL_HPP

#include "expanding_container.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::expanding_container()
				: __mem_dump(__BASE_SIZE) {
			this->__buffer = __Al::allocate(this->capacity());
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::expanding_container(size_type count)
				: base_container<__Tp>(count), __mem_dump(count) {
			this->__buffer = __Al::allocate(this->capacity());
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::expanding_container(size_type count, const value_type& value)
				: expanding_container(count) {
			for (size_type i = 0; i < this->size(); ++i) {
				(*this)[i] = value;
			}
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::expanding_container(iterator first, iterator last)
				: expanding_container(last - first) {
			for (size_type i = 0; i < this->size(); ++i, ++first) {
				(*this)[i] = *first;
			};
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::expanding_container(const_iterator first, const_iterator last)
				: expanding_container(last - first) {
			for (size_type i = 0; i < this->size(); ++i, ++first) {
				(*this)[i] = *first;
			};
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::expanding_container(std::initializer_list<__Tp> lst)
				: expanding_container(lst.size()) {
			std::copy(lst.begin(), lst.end(), this->begin());
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::expanding_container(const expanding_container<__Tp, __Al>& other)
				: expanding_container(other.size()) {
			std::copy(other.begin(), other.end(), this->begin());
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::expanding_container(expanding_container<__Tp, __Al>&& other)
				:  ftl_core::base_container<__Tp>(other.size()), __mem_dump(other.capacity()), __buffer(other.data()) {
			other.__el_count = 0;
			other.__mem_dump = 0;
			other.__buffer = nullptr;
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>::~expanding_container() {
			__Al::deallocate(this->__buffer, this->capacity());
			this->__mem_dump = 0;
			this->__buffer = nullptr;
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>& expanding_container<__Tp, __Al>::operator=(const expanding_container<__Tp, __Al>& rhs) {
			if (this != &rhs) {
				this->__el_count = rhs.size();
				this->__mem_dump = rhs.capacity();
				this->__buffer = __Al::allocate(this->capacity());
				std::copy(rhs.begin(), rhs.end(), this->begin());
			}
			
			return *this;
		}
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>& expanding_container<__Tp, __Al>::operator=(expanding_container<__Tp, __Al>&& rhs) {
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
		
		template <class __Tp, class __Al>
		expanding_container<__Tp, __Al>& expanding_container<__Tp, __Al>::operator=(std::initializer_list<__Tp> lst) {
			this->expanding_container(lst);
			return *this;
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::reference expanding_container<__Tp, __Al>::at(size_type pos) {
			if (pos < this->size()) {
				return (*this)[pos];
				
			} else {
				throw std::out_of_range("Accessed position is out of range!");
			}
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_reference expanding_container<__Tp, __Al>::at(size_type pos) const {
			if (pos < this->size()) {
				return (*this)[pos];
				
			} else {
				throw std::out_of_range("Accessed position is out of range!");
			}
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::reference expanding_container<__Tp, __Al>::operator[](size_type pos) {
			if (pos < this->size()) {
				return this->__buffer[pos];
				
			} else {
				throw std::out_of_range("Accessed position is out of range!");
			}
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_reference expanding_container<__Tp, __Al>::operator[](size_type pos) const {
			if (pos < this->size()) {
				return this->__buffer[pos];
				
			} else {
				throw std::out_of_range("Accessed position is out of range!");
			}
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::reference expanding_container<__Tp, __Al>::front() {
			return (*this)[0];
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_reference expanding_container<__Tp, __Al>::front() const {
			return (*this)[0];
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::reference expanding_container<__Tp, __Al>::back() {
			return (*this)[this->size() - 1];
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_reference expanding_container<__Tp, __Al>::back() const {
			return (*this)[this->size() - 1];
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::pointer expanding_container<__Tp, __Al>::data() {
			return this->__buffer;
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_pointer expanding_container<__Tp, __Al>::data() const {
			return this->__buffer;
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::pointer expanding_container<__Tp, __Al>::begin() {
			return this->__buffer;
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_pointer expanding_container<__Tp, __Al>::begin() const {
			return this->__buffer;
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_pointer expanding_container<__Tp, __Al>::cbegin() const {
			return this->__buffer;
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::pointer expanding_container<__Tp, __Al>::end() {
			return this->__buffer + this->size();
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_pointer expanding_container<__Tp, __Al>::end() const {
			return this->__buffer + this->size();
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::const_pointer expanding_container<__Tp, __Al>::cend() const {
			return this->__buffer + this->size();
		}
		
		template <class __Tp, class __Al>
		typename expanding_container<__Tp, __Al>::size_type expanding_container<__Tp, __Al>::capacity() const {
			return this->__mem_dump;
		}
		
		template <class __Tp, class __Al>
		void expanding_container<__Tp, __Al>::clear() {
			for (size_type i = 0; i < this->size(); ++i) {
				(*this)[i].~__Tp();
			}
			
			this->__el_count = 0;
		}
		
		template <class __Tp, class __Al>
		inline void expanding_container<__Tp, __Al>::reallocate() {
			value_type* __temp_buffer = __Al::allocate(this->capacity());
			std::copy(this->begin(), this->end(), __temp_buffer);
			__Al::deallocate(this->__buffer, this->capacity());
			this->__buffer = __temp_buffer;
		}
		
		template <class __Tp, class __Al>
		void expanding_container<__Tp, __Al>::swap(expanding_container<__Tp, __Al>& other) {
			std::swap(this->__el_count, other.__el_count);
			std::swap(this->__mem_dump, other.__mem_dump);
			std::swap(this->__buffer, other.__buffer);
		}
		
		template <class __Tp>
		void swap(__Tp& lhs, __Tp& rhs) {
			lhs.swap(rhs);
		}
		
		template <class __Tp>
		bool operator==(const __Tp& lhs, const __Tp& rhs) {
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
		bool operator!=(const __Tp& lhs, const __Tp& rhs) {
			return !(rhs == lhs);
		}
		
		template <class __Tp>
		bool operator<(const __Tp& lhs, const __Tp& rhs) {
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
		bool operator<=(const __Tp& lhs, const __Tp& rhs) {
			return lhs < rhs || lhs == rhs;
		}
		
		template <class __Tp>
		bool operator>(const __Tp& lhs, const __Tp& rhs) {
			return !(lhs < rhs) && !(lhs == rhs);
		}
		
		template <class __Tp>
		bool operator>=(const __Tp& lhs, const __Tp& rhs) {
			return lhs > rhs || lhs == rhs;
		}
		
		template <class __Tp, class __Al>
		std::ostream& operator<<(std::ostream& stream, const expanding_container<__Tp, __Al>& vec) {
			for (const auto& iter : vec) {
				stream << iter << " ";
			}
			
			return stream;
		}
	}
}

#endif //LAB_02_EXPANDING_CONTAINER_IMPL_HPP
