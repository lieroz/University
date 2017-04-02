//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_SET_HPP
#define LAB_02_SET_HPP

#include "expanding_container.hpp"

namespace ftl {
	
	template <class __Tp>
	class set : public ftl_core::expanding_container<__Tp> {
			const size_t __GROW_COEF = 2;
		
		public:
			typedef typename ftl_core::expanding_container<__Tp>::iterator iterator;
			typedef typename ftl_core::expanding_container<__Tp>::const_iterator const_iterator;
			
			// Functions-members
			explicit set();
			explicit set(size_t);
			explicit set(size_t, const __Tp&);
			set(iterator, iterator);
			set(const_iterator, const_iterator);
			set(std::initializer_list<__Tp>);
			set(const set&);
			set(set&&);
			~set() = default;
			set& operator=(const set&);
			set& operator=(set&&);
			
			// Public members
			void add(const __Tp&);
			void remove(const __Tp&);
			bool contains(const __Tp&);
			bool contains(const __Tp&) const;
			int count(const __Tp&);
			size_t power() const;
			
			// Set operations with operators
			template <class T>
			friend set<T> operator^(const set<T>&, const set<T>&);
			template <class T>
			friend set<T> operator+(const set<T>&, const set<T>&);
			template <class T>
			friend set<T> operator-(const set<T>&, const set<T>&);
			
			set& operator^=(const set&);
			set& operator+=(const set&);
			set& operator-=(const set&);
			
			// Set operations with wrappers
			template <class T>
			friend set<T> Intersection(const set<T>&, const set<T>&);
			template <class T>
			friend set<T> Union(const set<T>&, const set<T>&);
			template <class T>
			friend set<T> Subtraction(const set<T>&, const set<T>&);
		
		private:
			int find_item_index(const __Tp&) const;
	};
}

#include "../implementations/set_impl.hpp"

#endif //LAB_02_SET_HPP
