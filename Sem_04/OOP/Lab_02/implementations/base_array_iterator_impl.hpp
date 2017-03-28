//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_BASE_ARRAY_ITERATOR_IMPL_HPP
#define LAB_02_BASE_ARRAY_ITERATOR_IMPL_HPP

#include "base_array_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	base_array_iterator<__Tp>::base_array_iterator(pointer ptr)
			: ftl_core::base_iterator<__Tp>(ptr) {
		
	}
	
	template <class __Tp>
	base_array_iterator<__Tp>::base_array_iterator(const base_array_iterator& other)
			: ftl_core::base_iterator<__Tp>(other.__ptr) {
		
	}
	
	template <class __Tp>
	base_array_iterator<__Tp>& base_array_iterator<__Tp>::operator=(const pointer ptr) {
		if (this->__ptr != ptr) {
			this->__ptr = ptr;
		}
		
		return *this;
	}
	
	template <class __Tp>
	base_array_iterator<__Tp>& base_array_iterator<__Tp>::operator=(const base_array_iterator& rhs) {
		if (this != &rhs) {
			this->__ptr = rhs.__ptr;
		}
		
		return *this;
	}
	
	template <class __Tp>
	base_array_iterator<__Tp>& base_array_iterator<__Tp>::operator++() {
		++this->__ptr;
		return *this;
	}
	
	template <class __Tp>
	base_array_iterator<__Tp> base_array_iterator<__Tp>::operator++(int) {
		base_array_iterator temp(*this);
		this->operator++();
		return temp;
	}
	
	template <class __Tp>
	base_array_iterator<__Tp>& base_array_iterator<__Tp>::operator--() {
		--this->__ptr;
		return *this;
	}
	
	template <class __Tp>
	base_array_iterator<__Tp> base_array_iterator<__Tp>::operator--(int) {
		base_array_iterator temp(*this);
		this->operator--();
		return temp;
	}
	
	template <class __Tp>
	typename base_array_iterator<__Tp>::difference_type
	base_array_iterator<__Tp>::operator-(const base_array_iterator<__Tp>& rhs) {
		return this->__ptr - rhs.__ptr;
	}
	
	template <class __Tp>
	bool base_array_iterator<__Tp>::operator==(const base_array_iterator& rhs) {
		return this->__ptr == rhs.__ptr;
	}
	
	template <class __Tp>
	bool base_array_iterator<__Tp>::operator!=(const base_array_iterator& rhs) {
		return this->__ptr != rhs.__ptr;
	}
}

#endif // LAB_02_BASE_ARRAY_ITERATOR_IMPL_HPP
