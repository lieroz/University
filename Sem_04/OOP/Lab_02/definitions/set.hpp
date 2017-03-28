//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_SET_HPP
#define LAB_02_SET_HPP

#include "base_allocator.hpp"
#include "expanding_container.hpp"

namespace ftl {
	
	template <class __Tp, class __Al = ftl_core::base_allocator<__Tp>>
	class set : public ftl_core::expanding_container<__Tp, __Al> {
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
			explicit set();
			explicit set(size_type);
			explicit set(size_type, const value_type&);
			set(iterator, iterator);
			set(const_iterator, const_iterator);
			set(std::initializer_list<__Tp>);
			set(const set&);
			set(set&&);
			~set() = default;
			set& operator=(const set&);
			set& operator=(set&&);
			
			// Public members
			void add(const value_type&);
			void remove(const value_type&);
			bool contains(const value_type&);
			bool contains(const value_type&) const;
			int count(const value_type&);
			
			// Set operations with operators
			template <class T>
			friend set<T> operator^(const set<T>&, const set<T>&);
			template <class T>
			friend set<T> operator+(const set<T>&, const set<T>&);
			template <class T>
			friend set<T> operator-(const set<T>&, const set<T>&);
			
			// Set operations with wrappers
			template <class T>
			friend set<T> Intersection(const set<T>&, const set<T>&);
			template <class T>
			friend set<T> Union(const set<T>&, const set<T>&);
			template <class T>
			friend set<T> Subtraction(const set<T>&, const set<T>&);
			
		private:
			int find_item_index(const value_type&) const;
	};
}

#include "../implementations/set_impl.hpp"

#endif //LAB_02_SET_HPP
