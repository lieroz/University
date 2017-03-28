//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_STANDARD_ALLOC_POLICY_IMPL_HPP
#define LAB_02_STANDARD_ALLOC_POLICY_IMPL_HPP

#include "standard_alloc_policy.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		standard_alloc_policy<__Tp>::standard_alloc_policy() {
			
		}
		
		template <class __Tp>
		standard_alloc_policy<__Tp>::standard_alloc_policy(const standard_alloc_policy&) {
			
		}
		
		template <class __Tp>
		template <typename T>
		standard_alloc_policy<__Tp>::standard_alloc_policy(const standard_alloc_policy <T>&) {
			
		}
		
		template <class __Tp>
		standard_alloc_policy<__Tp>::~standard_alloc_policy() {
			
		}
		
		template <class __Tp>
		typename standard_alloc_policy<__Tp>::pointer
		standard_alloc_policy<__Tp>::allocate(size_type count, typename std::allocator<void>::const_pointer) {
			return reinterpret_cast<pointer>(::operator new(count * sizeof(__Tp)));
		}
		
		template <class __Tp>
		void standard_alloc_policy<__Tp>::deallocate(pointer ptr, size_type) {
			::operator delete(ptr);
		}
		
		template <class __Tp>
		typename standard_alloc_policy<__Tp>::size_type standard_alloc_policy<__Tp>::max_size() {
			return std::numeric_limits<size_type>::max() / sizeof(__Tp);
		}
		
		template <class __Tp1, class __Tp2>
		inline bool operator==(const standard_alloc_policy <__Tp1>&, const standard_alloc_policy <__Tp2>&) {
			return true;
		}
		
		template <class __Tp, class __Al>
		inline bool operator==(const standard_alloc_policy <__Tp>&, const __Al&) {
			return false;
		}
	}
}

#endif //LAB_02_STANDARD_ALLOC_POLICY_IMPL_HPP
