//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_VECTOR_ITERATOR_HPP
#define LAB_02_VECTOR_ITERATOR_HPP

#include <cstddef>

#include "base_vector_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	class vector_iterator : public base_vector_iterator<__Tp> {
			typedef __Tp& reference;
			typedef __Tp* pointer;
		
		public:
			vector_iterator(pointer);
			vector_iterator(const vector_iterator&);
			
			reference operator*();
			pointer operator->();
	};
	
	template <class __Tp>
	vector_iterator<__Tp>::vector_iterator(pointer ptr)
			: base_vector_iterator<__Tp>{ptr} {
		
	}
	
	template <class __Tp>
	vector_iterator<__Tp>::vector_iterator(const vector_iterator& other)
			: base_vector_iterator<__Tp>{other.__ptr} {
		
	}
	
	template <class __Tp>
	typename vector_iterator<__Tp>::reference vector_iterator<__Tp>::operator*() {
		return *this->__ptr;
	}
	
	template <class __Tp>
	typename vector_iterator<__Tp>::pointer vector_iterator<__Tp>::operator->() {
		return this->__ptr;
	}
}

#endif //LAB_02_VECTOR_ITERATOR_HPP
