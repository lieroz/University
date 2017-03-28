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
	}
}

#include "../implementation/object_traits_impl.hpp"

#endif //LAB_02_OBJECT_TRAITS_HPP
