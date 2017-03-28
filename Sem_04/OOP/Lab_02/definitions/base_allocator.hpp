//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_BASE_ALLOCATOR_HPP
#define LAB_02_BASE_ALLOCATOR_HPP

#include <memory>
#include <limits>

#include "object_traits.hpp"
#include "standard_alloc_policy.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp, class __Pl = standard_alloc_policy<__Tp>, class __Tr = object_traits<__Tp>>
		class base_allocator : public __Pl, public __Tr {
			public:
				typedef typename __Pl::size_type size_type;
				typedef typename __Pl::difference_type difference_type;
				typedef typename __Pl::pointer pointer;
				typedef typename __Pl::const_pointer const_pointer;
				typedef typename __Pl::reference reference;
				typedef typename __Pl::const_reference const_reference;
				typedef typename __Pl::value_type value_type;
				
				template <class T>
				struct rebind {
					typedef base_allocator<T> other;
				};
				
				inline explicit base_allocator();
				inline explicit base_allocator(const base_allocator&);
				template <class T>
				inline explicit base_allocator(const base_allocator<T>&);
				template <class T, class U, class V>
				inline base_allocator(const base_allocator<T, U, V>&);
				virtual inline ~base_allocator();
		};
	}
}

#include "../implementations/base_allocator_impl.hpp"

#endif //LAB_02_BASE_ALLOCATOR_HPP
