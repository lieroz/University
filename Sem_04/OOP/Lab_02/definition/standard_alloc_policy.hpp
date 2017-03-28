//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_STANDARD_ALLOC_POLICY_HPP
#define LAB_02_STANDARD_ALLOC_POLICY_HPP

#include <memory>
#include <limits>

#include "ftlspace.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		class standard_alloc_policy {
			public :
				typedef __Tp* value_type;
				typedef __Tp* pointer;
				typedef const __Tp* const_pointer;
				typedef __Tp& reference;
				typedef const __Tp& const_reference;
				typedef size_t size_type;
				typedef std::ptrdiff_t difference_type;
				
				template<typename T>
				struct rebind {
					typedef standard_alloc_policy<T> other;
				};
				
				inline explicit standard_alloc_policy();
				inline explicit standard_alloc_policy(const standard_alloc_policy&);
				template <typename T>
				inline explicit standard_alloc_policy(const standard_alloc_policy<T>&);
				inline virtual ~standard_alloc_policy();
				
				static inline pointer allocate(size_type, typename std::allocator<void>::const_pointer = 0);
				static inline void deallocate(pointer, size_type);
				
				static inline size_type max_size();
		};
	}
}

#include "../implementation/standard_alloc_policy_impl.hpp"

#endif //LAB_02_STANDARD_ALLOC_POLICY_HPP
