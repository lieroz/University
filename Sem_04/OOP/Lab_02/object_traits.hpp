//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_OBJECT_TRAITS_HPP
#define LAB_02_OBJECT_TRAITS_HPP

#include "ftlspace.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		class object_traits {
				typedef __Tp* pointer;
				typedef const __Tp* const_pointer;
				typedef __Tp& reference;
				typedef const __Tp& const_reference;
				
			public:
				template <class T>
				struct rebind {
					typedef object_traits<T> other;
				};
				
				inline explicit object_traits();
				template <class T>
				inline explicit object_traits(const object_traits<T>&);
				inline virtual ~object_traits();
				
				static inline pointer address(reference);
				static inline const_pointer address(const_reference);
				
				static inline void construct(pointer, const_reference);
				static inline void destroy(pointer);
		};
		
		template <class __Tp>
		object_traits<__Tp>::object_traits() {
			
		}
		
		template <class __Tp>
		template <class T>
		object_traits<__Tp>::object_traits(const object_traits<T>&) {
			
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

#endif //LAB_02_OBJECT_TRAITS_HPP
