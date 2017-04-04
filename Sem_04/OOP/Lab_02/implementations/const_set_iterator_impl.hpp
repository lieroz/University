//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_CONST_ARRAY_ITERATOR_IMPL_HPP
#define LAB_02_CONST_ARRAY_ITERATOR_IMPL_HPP

#include "const_set_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	const_set_iterator<__Tp>::const_set_iterator(__Tp* ptr)
			: ftl_core::base_iterator<__Tp>(ptr) {
	}
	
	template <class __Tp>
	const_set_iterator<__Tp>::const_set_iterator(const const_set_iterator& other)
			: ftl_core::base_iterator<__Tp>(other.__ptr) {
	}
	
	template <class __Tp>
	const __Tp& const_set_iterator<__Tp>::operator*() {
		return *this->__ptr;
	}
	
	template <class __Tp>
	const __Tp* const_set_iterator<__Tp>::operator->() {
		return this->__ptr;
	}
}

#endif // LAB_02_CONST_ARRAY_ITERATOR_IMPL_HPP
