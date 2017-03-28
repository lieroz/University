//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_VECTOR_IMPL_HPP
#define LAB_02_VECTOR_IMPL_HPP

#include "vector.hpp"

namespace ftl {
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector()
			: ftl_core::expanding_container<__Tp, __Al>() {
		
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(size_type count)
			: ftl_core::expanding_container<__Tp, __Al>(count) {
		
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(size_type count, const value_type& value)
			: ftl_core::expanding_container<__Tp, __Al>(count, value) {

	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(iterator first, iterator last)
			: ftl_core::expanding_container<__Tp, __Al>(first, last) {

	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(const_iterator first, const_iterator last)
			: ftl_core::expanding_container<__Tp, __Al>(first, last) {

	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(std::initializer_list<__Tp> lst)
			: ftl_core::expanding_container<__Tp, __Al>(lst) {

	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(const vector<__Tp, __Al>& other)
			: ftl_core::expanding_container<__Tp, __Al>(other) {
		
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>::vector(vector<__Tp, __Al>&& other)
			: ftl_core::expanding_container<__Tp, __Al>(std::move(other)) {

	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>& vector<__Tp, __Al>::operator=(const vector<__Tp, __Al>& rhs) {
		ftl_core::expanding_container<__Tp, __Al>::operator=(rhs);
		return *this;
	}
	
	template <class __Tp, class __Al>
	vector<__Tp, __Al>& vector<__Tp, __Al>::operator=(vector<__Tp, __Al>&& rhs) {
		ftl_core::expanding_container<__Tp, __Al>::operator=(std::move(rhs));
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
	void vector<__Tp, __Al>::shrink_to_fit() {
		this->__mem_dump = this->size();
		this->reallocate();
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
}

#endif //LAB_02_VECTOR_IMPL_HPP
