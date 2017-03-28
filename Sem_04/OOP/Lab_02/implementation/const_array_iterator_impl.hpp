//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_CONST_ARRAY_ITERATOR_IMPL_HPP
#define LAB_02_CONST_ARRAY_ITERATOR_IMPL_HPP

#include "const_array_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	const_array_iterator<__Tp>::const_array_iterator(pointer ptr)
			: base_array_iterator<__Tp>(ptr) {
		
	}
	
	template <class __Tp>
	const_array_iterator<__Tp>::const_array_iterator(const const_array_iterator& other)
			: base_array_iterator<__Tp>(other.__ptr) {
		
	}
	
	template <class __Tp>
	typename const_array_iterator<__Tp>::const_reference const_array_iterator<__Tp>::operator*() {
		return *this->__ptr;
	}
	
	template <class __Tp>
	typename const_array_iterator<__Tp>::const_pointer const_array_iterator<__Tp>::operator->() {
		return this->__ptr;
	}
}

#endif // LAB_02_CONST_ARRAY_ITERATOR_IMPL_HPP
