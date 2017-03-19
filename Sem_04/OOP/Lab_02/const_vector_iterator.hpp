//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_CONST_VECTOR_ITERATOR_HPP
#define LAB_02_CONST_VECTOR_ITERATOR_HPP

#include <cstddef>

#include "base_vector_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	class const_vector_iterator : public base_vector_iterator<__Tp> {
			typedef __Tp* pointer;
			typedef const __Tp* const_pointer;
			typedef const __Tp& const_reference;
		
		public:
			const_vector_iterator(pointer);
			const_vector_iterator(const const_vector_iterator&);
			
			const_reference operator*();
			const_pointer operator->();
	};
	
	template <class __Tp>
	const_vector_iterator<__Tp>::const_vector_iterator(pointer ptr)
			: base_vector_iterator<__Tp>(ptr) {
		
	}
	
	template <class __Tp>
	const_vector_iterator<__Tp>::const_vector_iterator(const const_vector_iterator& other)
			: base_vector_iterator<__Tp>(other.__ptr) {
		
	}
	
	template <class __Tp>
	typename const_vector_iterator<__Tp>::const_reference const_vector_iterator<__Tp>::operator*() {
		return *this->__ptr;
	}
	
	template <class __Tp>
	typename const_vector_iterator<__Tp>::const_pointer const_vector_iterator<__Tp>::operator->() {
		return this->__ptr;
	}
}

#endif //LAB_02_CONST_VECTOR_ITERATOR_HPP
