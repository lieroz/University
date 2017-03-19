//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_BASE_ITERATOR_HPP
#define LAB_02_BASE_ITERATOR_HPP

#include "ftlspace.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		class base_iterator {
				typedef __Tp* pointer;
			
			public:
				explicit base_iterator();
				explicit base_iterator(pointer ptr);
				virtual ~base_iterator();
			
			protected:
				pointer __ptr;
		};
		
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

#endif //LAB_02_BASE_ITERATOR_HPP
