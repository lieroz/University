//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_OBJECT_TRAITS_IMPL_HPP
#define LAB_02_OBJECT_TRAITS_IMPL_HPP

#include "object_traits.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		object_traits<__Tp>::object_traits() {
			
		}
		
		template <class __Tp>
		template <class T>
		object_traits<__Tp>::object_traits(const object_traits <T>&) {
			
		}
		
		template <class __Tp>
		object_traits<__Tp>::~object_traits() {
			
		}
		
		template <class __Tp>
		typename object_traits<__Tp>::pointer object_traits<__Tp>::address(reference ref) {
			return &ref;
		}
		
		template <class __Tp>
		typename object_traits<__Tp>::const_pointer object_traits<__Tp>::address(const_reference ref) {
			return &ref;
		}
		
		template <class __Tp>
		void object_traits<__Tp>::construct(pointer ptr, const_reference obj) {
			new(ptr) __Tp(obj);
		}
		
		template <class __Tp>
		void object_traits<__Tp>::destroy(pointer ptr) {
			ptr->~__Tp();
		}
	}
}

#endif //LAB_02_OBJECT_TRAITS_IMPL_HPP
