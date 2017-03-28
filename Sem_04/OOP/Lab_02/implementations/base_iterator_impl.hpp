//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_BASE_ITERATOR_IMPL_HPP
#define LAB_02_BASE_ITERATOR_IMPL_HPP

#include "base_iterator.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		base_iterator<__Tp>::base_iterator()
				: __ptr(nullptr) {
			
		}
		
		template <class __Tp>
		base_iterator<__Tp>::base_iterator(pointer ptr)
				: __ptr(ptr) {
			
		}
		
		template <class __Tp>
		base_iterator<__Tp>::~base_iterator() {
			this->__ptr = nullptr;
		}
	}
}

#endif //LAB_02_BASE_ITERATOR_IMPL_HPP
