//
// Created by lieroz on 17.03.17.
//

#ifndef LAB_02_VECTOR_HPP
#define LAB_02_VECTOR_HPP

#include "base_allocator.hpp"
#include "expanding_container.hpp"
#include "array_iterator.hpp"
#include "const_array_iterator.hpp"

namespace ftl {
	
	template <class __Tp, class __Al = ftl_core::base_allocator<__Tp>>
	class vector : public ftl_core::expanding_container<__Tp, __Al> {
			typedef __Tp value_type;
			typedef __Tp* pointer;
			typedef const __Tp* const_pointer;
			typedef __Tp& reference;
			typedef const __Tp& const_reference;
			typedef size_t size_type;
			typedef std::ptrdiff_t difference_type;
			
			const size_type __GROW_COEF = 2;
		
		public:
			typedef typename ftl_core::expanding_container<__Tp, __Al>::iterator iterator;
			typedef typename ftl_core::expanding_container<__Tp, __Al>::const_iterator const_iterator;
			
			// Functions-members
			explicit vector();
			explicit vector(size_type);
			explicit vector(size_type, const value_type&);
			vector(iterator, iterator);
			vector(const_iterator, const_iterator);
			vector(std::initializer_list<__Tp>);
			vector(const vector&);
			vector(vector&&);
			~vector() = default;
			vector& operator=(const vector&);
			vector& operator=(vector&&);
			void assign(size_type, const value_type&);
			void assign(iterator, iterator);
			void assign(const_iterator, const_iterator);
			
			// Capacity
			size_type max_size() const;
			void reserve(size_type);
			void shrink_to_fit();
			
			// Modifiers
			void insert(size_type, const value_type&);
			void insert(size_type, value_type&&);
			void erase(size_type);
			void push_back(const value_type&);
			void push_back(value_type&&);
			void pop_back();
			void resize(size_type);
			void resize(size_type, const value_type&);
	};
}

#include "../implementation/vector_impl.hpp"

#endif //LAB_02_VECTOR_HPP
