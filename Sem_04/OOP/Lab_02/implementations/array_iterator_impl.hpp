//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_ARRAY_ITERATOR_IMPL_HPP
#define LAB_02_ARRAY_ITERATOR_IMPL_HPP

#include "array_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	array_iterator<__Tp>::array_iterator(pointer ptr)
			: base_array_iterator<__Tp>(ptr) {
		
	}
	
	template <class __Tp>
	array_iterator<__Tp>::array_iterator(const array_iterator& other)
			: base_array_iterator<__Tp>(other.__ptr) {
		
	}
	
	template <class __Tp>
	typename array_iterator<__Tp>::reference array_iterator<__Tp>::operator*() {
		return *this->__ptr;
	}
	
	template <class __Tp>
	typename array_iterator<__Tp>::pointer array_iterator<__Tp>::operator->() {
		return this->__ptr;
	}
}

#endif // LAB_02_ARRAY_ITERATOR_IMPL_HPP
