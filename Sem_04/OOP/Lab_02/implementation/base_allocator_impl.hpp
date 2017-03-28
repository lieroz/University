//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_BASE_ALLOCATOR_IMPL_HPP
#define LAB_02_BASE_ALLOCATOR_IMPL_HPP

#include "base_allocator.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp, class __Pl, class __Tr>
		base_allocator<__Tp, __Pl, __Tr>::base_allocator() {
			
		}
		
		template <class __Tp, class __Pl, class __Tr>
		base_allocator<__Tp, __Pl, __Tr>::base_allocator(const base_allocator& rhs)
				: __Pl(rhs), __Tr(rhs) {
			
		}
		
		template <class __Tp, class __Pl, class __Tr>
		template <class T>
		base_allocator<__Tp, __Pl, __Tr>::base_allocator(const base_allocator<T>&) {
			
		}
		
		template <class __Tp, class __Pl, class __Tr>
		template <class T, class U, class V>
		base_allocator<__Tp, __Pl, __Tr>::base_allocator(const base_allocator<T, U, V>& rhs)
				: __Pl(rhs), __Tr(rhs) {
			
		}
		
		template <class __Tp, class __Pl, class __Tr>
		base_allocator<__Tp, __Pl, __Tr>::~base_allocator() {
			
		}
		
		template <class __Tp, class __Pl, class __Tr>
		inline bool
		operator==(const base_allocator<__Tp, __Pl, __Tr>& lhs, const base_allocator<__Tp, __Pl, __Tr>& rhs) {
			return operator==(static_cast<__Pl&>(lhs), static_cast<__Pl&>(rhs));
		}
		
		template <class __Tp1, class __Pl1, class __Tr1, class __Tp2, class __Pl2, class __Tr2>
		inline bool
		operator==(const base_allocator<__Tp1, __Pl1, __Tr1>& lhs, const base_allocator<__Tp2, __Pl2, __Tr2>& rhs) {
			return operator==(static_cast<__Pl1&>(lhs), static_cast<__Pl2&>(rhs));
		}
		
		template <class __Tp, class __Pl, class __Tr, class __Al>
		inline bool operator==(const base_allocator<__Tp, __Pl, __Tr>& lhs, const __Al& rhs) {
			return operator==(static_cast<__Pl&>(lhs), rhs);
		}
		
		template <class __Tp, class __Pl, class __Tr>
		inline bool
		operator!=(const base_allocator<__Tp, __Pl, __Tr>& lhs, const base_allocator<__Tp, __Pl, __Tr>& rhs) {
			return !operator==(lhs, rhs);
		}
		
		template <class __Tp1, class __Pl1, class __Tr1, class __Tp2, class __Pl2, class __Tr2>
		inline bool
		operator!=(const base_allocator<__Tp1, __Pl1, __Tr1>& lhs, const base_allocator<__Tp2, __Pl2, __Tr2>& rhs) {
			return !operator==(lhs, rhs);
		}
		
		template <class __Tp, class __Pl, class __Tr, class __Al>
		inline bool operator!=(const base_allocator<__Tp, __Pl, __Tr>& lhs, const __Al& rhs) {
			return !operator==(lhs, rhs);
		}
	}
}

#endif //LAB_02_BASE_ALLOCATOR_IMPL_HPP
