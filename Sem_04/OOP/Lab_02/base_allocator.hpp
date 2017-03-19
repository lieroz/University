//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_BASE_ALLOCATOR_HPP
#define LAB_02_BASE_ALLOCATOR_HPP

#include <memory>
#include <limits>

#include "ftlspace.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		class base_allocator {
			public:
				typedef __Tp value_type;
				typedef __Tp* pointer;
				typedef const __Tp* const_pointer;
				typedef __Tp& reference;
				typedef const __Tp& const_reference;
				typedef size_t size_type;
				
				template <class T>
				struct rebind {
					typedef base_allocator<T> other;
				};
				
				inline explicit base_allocator();
				inline explicit base_allocator(const base_allocator&);
				template <class T>
				inline explicit base_allocator(const base_allocator<T>&);
				virtual inline ~base_allocator();
				
				inline pointer address(reference);
				inline const_pointer address(const_reference);
				
				static inline pointer allocate(size_type, typename std::allocator<void>::const_pointer = 0);
				static inline void deallocate(pointer, size_type);
				
				inline size_type max_size() const;
				
				inline void construct(pointer, const value_type&);
				inline void destroy(pointer);
				
				inline bool operator==(const base_allocator&);
				inline bool operator!=(const base_allocator& a);
		};
		
		template <class __Tp>
		base_allocator<__Tp>::base_allocator() {
			
		}
		
		template <class __Tp>
		base_allocator<__Tp>::base_allocator(const base_allocator& rhs) {
			
		}
		
		template <class __Tp>
		template <class T>
		base_allocator<__Tp>::base_allocator(const base_allocator<T>& rhs) {
			
		}
		
		template <class __Tp>
		base_allocator<__Tp>::~base_allocator() {
			
		}
		
		template <class __Tp>
		typename base_allocator<__Tp>::pointer base_allocator<__Tp>::address(reference ref) {
			return &ref;
		}
		
		template <class __Tp>
		typename base_allocator<__Tp>::const_pointer base_allocator<__Tp>::address(const_reference ref) {
			return &ref;
		}
		
		template <class __Tp>
		typename base_allocator<__Tp>::pointer
		base_allocator<__Tp>::allocate(size_type count, typename std::allocator<void>::const_pointer) {
			return reinterpret_cast<pointer>(::operator new(count * sizeof(__Tp)));
		}
		
		template <class __Tp>
		void base_allocator<__Tp>::deallocate(pointer ptr, size_type) {
			::operator delete(ptr);
		}
		
		template <class __Tp>
		typename base_allocator<__Tp>::size_type base_allocator<__Tp>::max_size() const {
			return std::numeric_limits<size_type>::max() / sizeof(__Tp);
		}
		
		template <class __Tp>
		void base_allocator<__Tp>::construct(pointer p, const value_type& t) {
			new(p) __Tp(t);
		}
		
		template <class __Tp>
		void base_allocator<__Tp>::destroy(pointer ptr) {
			ptr->~__Tp();
		}
		
		template <class __Tp>
		bool base_allocator<__Tp>::operator==(const base_allocator<__Tp>&) {
			return true;
		}
		
		template <class __Tp>
		bool base_allocator<__Tp>::operator!=(const base_allocator<__Tp>& rhs) {
			return !operator==(rhs);
		}
	}
}

#endif //LAB_02_BASE_ALLOCATOR_HPP
