//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_ARRAY_ITERATOR_IMPL_HPP
#define LAB_02_ARRAY_ITERATOR_IMPL_HPP

#include "set_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	set_iterator<__Tp>::set_iterator(__Tp* ptr)
			: ftl_core::base_iterator<__Tp>(ptr) {
		
	}
	
	template <class __Tp>
	set_iterator<__Tp>::set_iterator(const set_iterator& other)
			: ftl_core::base_iterator<__Tp>(other.__ptr) {
		
	}
	
	template <class __Tp>
	__Tp& set_iterator<__Tp>::operator*() {
		return *this->__ptr;
	}
	
	template <class __Tp>
	__Tp* set_iterator<__Tp>::operator->() {
		return this->__ptr;
	}
}

#endif // LAB_02_ARRAY_ITERATOR_IMPL_HPP
