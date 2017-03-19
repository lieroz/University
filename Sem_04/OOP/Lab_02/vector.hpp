//
// Created by lieroz on 17.03.17.
//

#ifndef LAB_02_VECTOR_HPP
#define LAB_02_VECTOR_HPP

#include <cstring>

#include "base_allocator.hpp"
#include "base_container.hpp"
#include "vector_iterator.hpp"
#include "const_vector_iterator.hpp"

namespace ftl {
	
	template <class __Tp, class __Al = ftl_core::base_allocator<__Tp>>
	class vector : public ftl_core::base_container<__Tp> {
			typedef size_t size_type;
			typedef __Tp value_type;
			typedef __Tp& reference;
			typedef const __Tp& const_reference;
			typedef __Tp* pointer;
			typedef const __Tp* const_pointer;
			
			const size_type __BASE_SIZE = 7;
			const size_type __GROW_COEF = 2;
		
		public:
			typedef vector_iterator<__Tp> iterator;
			typedef const_vector_iterator<__Tp> const_iterator;
			
			// Functions-members
			explicit vector();
			explicit vector(size_type);
			explicit vector(size_type, const value_type&);
			vector(iterator, iterator);
			vector(const_iterator, const_iterator);
			vector(std::initializer_list<__Tp>);
			vector(const vector&);
			vector(vector&&);
			virtual ~vector();
			vector& operator=(const vector&);
			vector& operator=(vector&&);
			vector& operator=(std::initializer_list<__Tp>);
			void assign(size_type, const value_type&);
			void assign(iterator, iterator);
			void assign(const_iterator, const_iterator);
			
			// Access to elements
			reference at(size_type);
			const_reference at(size_type) const;
			reference operator[](size_type);
			const_reference operator[](size_type) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			pointer data();
			const_pointer data() const;
			
			// Iterators
			pointer begin();
			const_pointer begin() const;
			const_pointer cbegin() const;
			pointer end();
			const_pointer end() const;
			const_pointer cend() const;
			
			// Capacity
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			void reserve(size_type);
			size_type capacity() const;
			void shrink_to_fit();
			
			// Modifiers
			void clear();
			void insert(size_type, const value_type&);
			void insert(size_type, value_type&&);
			void erase(size_type);
			void push_back(const value_type&);
			void push_back(value_type&&);
			void pop_back();
			void resize(size_type);
			void resize(size_type, const value_type&);
			void swap(vector&);
			template <class T>
			friend inline void swap(T&, T&);
			
			// Compare operators
			template <class T>
			friend inline bool operator==(const T&, const T&);
			template <class T>
			friend inline bool operator!=(const T&, const T&);
			template <class T>
			friend inline bool operator<(const T&, const T&);
			template <class T>
			friend inline bool operator<=(const T&, const T&);
			template <class T>
			friend inline bool operator>(const T&, const T&);
			template <class T>
			friend inline bool operator>=(const T&, const T&);
			
			template <class T>
			friend inline std::ostream& operator<<(std::ostream&, const vector<T>&);
		
		private:
			size_type __mem_dump;
			value_type* __buffer;
			
			inline void reallocate();
	};
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector()
			: __mem_dump(__BASE_SIZE) {
		this->__buffer = __Al::allocate(this->capacity());
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(size_type count)
			: ftl_core::base_container<__Tp>(count), __mem_dump(count) {
		this->__buffer = __Al::allocate(this->capacity());
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(size_type count, const value_type& value)
			: vector(count) {
		for (size_type i = 0; i < this->size(); ++i) {
			(*this)[i] = value;
		}
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(iterator first, iterator last)
			: vector(last - first) {
		for (size_type i = 0; i < this->size(); ++i, ++first) {
			(*this)[i] = *first;
		};
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(const_iterator first, const_iterator last)
			: vector(last - first) {
		for (size_type i = 0; i < this->size(); ++i, ++first) {
			(*this)[i] = *first;
		};
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(std::initializer_list<__Tp> lst)
			: vector(lst.size()) {
		std::copy(lst.begin(), lst.end(), this->begin());
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(const vector<__Tp, __Al>& other)
			: vector(other.size()) {
		std::copy(other.begin(), other.end(), this->begin());
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(vector<__Tp, __Al>&& other)
			:  ftl_core::base_container<__Tp>(other.size()), __mem_dump(other.capacity()), __buffer(other.data()) {
		other.__el_count = 0;
		other.__mem_dump = 0;
		other.__buffer = nullptr;
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::~vector() {
		__Al::deallocate(this->__buffer, this->capacity());
		this->__mem_dump = 0;
		this->__buffer = nullptr;
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>& vector<__Tp, __Al>::operator=(const vector<__Tp, __Al>& rhs) {
		if (this != &rhs) {
			this->__el_count = rhs.size();
			this->__mem_dump = rhs.capacity();
			this->__buffer = __Al::allocate(this->capacity());
			std::copy(rhs.begin(), rhs.end(), this->begin());
		}
		
		return *this;
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>& vector<__Tp, __Al>::operator=(vector<__Tp, __Al>&& rhs) {
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
	vector<__Tp, __Al>& vector<__Tp, __Al>::operator=(std::initializer_list<__Tp> lst) {
		this->vector(lst);
		return *this;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::assign(size_type count, const value_type& value) {
		if (count > this->capacity()) {
			this->__mem_dump = count << __GROW_COEF;
			this->reallocate();
		}
		
		for (size_type i = 0; i < count; ++i) {
			(*this)[i] = value;
		}
		
		this->__el_count = count;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::assign(iterator first, iterator last) {
		size_type count = last - first;
		
		if (count > this->capacity()) {
			this->__mem_dump = count << __GROW_COEF;
			this->reallocate();
		}
		
		for (size_type i = 0; i < count; ++i, ++first) {
			(*this)[i] = *first;
		}
		
		this->__el_count = count;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::assign(const_iterator first, const_iterator last) {
		size_type count = last - first;
		
		if (count > this->capacity()) {
			this->__mem_dump = count << __GROW_COEF;
			this->reallocate();
		}
		
		for (size_type i = 0; i < count; ++i, ++first) {
			(*this)[i] = *first;
		}
		
		this->__el_count = count;
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::reference vector<__Tp, __Al>::at(size_type pos) {
		if (pos < this->size()) {
			return (*this)[pos];
			
		} else {
			throw std::out_of_range("Accessed position is out of range!");
		}
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_reference vector<__Tp, __Al>::at(size_type pos) const {
		if (pos < this->size()) {
			return (*this)[pos];
			
		} else {
			throw std::out_of_range("Accessed position is out of range!");
		}
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::reference vector<__Tp, __Al>::operator[](size_type pos) {
		if (pos < this->size()) {
			return this->__buffer[pos];
			
		} else {
			throw std::out_of_range("Accessed position is out of range!");
		}
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_reference vector<__Tp, __Al>::operator[](size_type pos) const {
		if (pos < this->size()) {
			return this->__buffer[pos];
			
		} else {
			throw std::out_of_range("Accessed position is out of range!");
		}
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::reference vector<__Tp, __Al>::front() {
		return (*this)[0];
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_reference vector<__Tp, __Al>::front() const {
		return (*this)[0];
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::reference vector<__Tp, __Al>::back() {
		return (*this)[this->size() - 1];
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_reference vector<__Tp, __Al>::back() const {
		return (*this)[this->size() - 1];
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::pointer vector<__Tp, __Al>::data() {
		return this->__buffer;
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_pointer vector<__Tp, __Al>::data() const {
		return this->__buffer;
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::pointer vector<__Tp, __Al>::begin() {
		return this->__buffer;
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_pointer vector<__Tp, __Al>::begin() const {
		return this->__buffer;
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_pointer vector<__Tp, __Al>::cbegin() const {
		return this->__buffer;
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::pointer vector<__Tp, __Al>::end() {
		return this->__buffer + this->size();
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_pointer vector<__Tp, __Al>::end() const {
		return this->__buffer + this->size();
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::const_pointer vector<__Tp, __Al>::cend() const {
		return this->__buffer + this->size();
	}
	
	template <class __Tp, class __Al>
	bool vector<__Tp, __Al>::empty() const {
		return this->size() == 0;
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::size_type vector<__Tp, __Al>::size() const {
		return this->__el_count;
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::size_type vector<__Tp, __Al>::max_size() const {
		return this->capacity();
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::reserve(size_type size) {
		if (size > this->__mem_dump) {
			this->__mem_dump = size;
			this->reallocate();
		}
	}
	
	template <class __Tp, class __Al>
	typename vector<__Tp, __Al>::size_type vector<__Tp, __Al>::capacity() const {
		return this->__mem_dump;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::shrink_to_fit() {
		this->__mem_dump = this->size();
		this->reallocate();
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::clear() {
		for (size_type i = 0; i < this->size(); ++i) {
			(*this)[i].~__Tp();
		}
		
		this->__el_count = 0;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::insert(size_type pos, const value_type& value) {
		if (this->size() == this->capacity()) {
			this->__mem_dump <<= __GROW_COEF;
			this->reallocate();
		}
		
		value_type* mem_flag = this->__buffer + pos;
		std::memmove(mem_flag + 1, mem_flag, (this->size() - (mem_flag - this->__buffer)) * sizeof(value_type));
		++this->__el_count;
		(*this)[pos] = value;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::insert(size_type pos, value_type&& value) {
		if (this->size() == this->capacity()) {
			this->__mem_dump <<= __GROW_COEF;
			this->reallocate();
		}
		
		value_type* mem_flag = this->__buffer + pos;
		std::memmove(mem_flag + 1, mem_flag, (this->size() - (mem_flag - this->__buffer)) * sizeof(__Tp));
		++this->__el_count;
		(*this)[pos] = std::move(value);
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::erase(size_type pos) {
		value_type* mem_flag = this->__buffer + pos;
		(*this)[pos].~__Tp();
		std::memmove(mem_flag, mem_flag + 1, (this->size() - (mem_flag - this->__buffer) - 1) * sizeof(__Tp));
		--this->__el_count;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::push_back(const value_type& value) {
		if (this->size() == this->capacity()) {
			this->__mem_dump <<= __GROW_COEF;
			this->reallocate();
		}
		
		(*this)[this->__el_count++] = value;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::push_back(value_type&& value) {
		if (this->size() == this->capacity()) {
			this->__mem_dump <<= __GROW_COEF;
			this->reallocate();
		}
		
		(*this)[this->__el_count++] = std::move(value);
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::pop_back() {
		size_type temp = this->__el_count;
		(*this)[--temp].~__Tp();
		--this->__el_count;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::resize(size_type size) {
		if (size > this->size()) {
			
			if (size > this->__mem_dump) {
				this->__mem_dump = size;
				this->reallocate();
			}
			
		} else {
			
			for (size_type i = this->size(); i < size; ++i) {
				(*this)[i].~__Tp();
			}
		}
		
		this->__el_count = size;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::resize(size_type size, const value_type& value) {
		if (size > this->size()) {
			
			if (size > this->capacity()) {
				this->__mem_dump = size;
				this->reallocate();
			}
			
			for (size_type i = this->size(); i < size; ++i) {
				(*this)[i] = value;
			}
			
		} else {
			
			for (size_type i = this->size(); i < size; ++i) {
				(*this)[i].~__Tp();
			}
		}
		
		this->__el_count = size;
	}
	
	template <class __Tp, class __Al>
	void vector<__Tp, __Al>::swap(vector<__Tp, __Al>& other) {
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
	
	template <class __Tp>
	std::ostream& operator<<(std::ostream& stream, const vector<__Tp>& vec) {
		for (const auto& iter : vec) {
			stream << iter << " ";
		}
		
		return stream;
	}
	
	template <class __Tp, class __Al>
	inline void vector<__Tp, __Al>::reallocate() {
		value_type* __temp_buffer = __Al::allocate(this->capacity());
		std::copy(this->begin(), this->end(), __temp_buffer);
		__Al::deallocate(this->__buffer, this->capacity());
		this->__buffer = __temp_buffer;
	}
}

#endif //LAB_02_VECTOR_HPP
