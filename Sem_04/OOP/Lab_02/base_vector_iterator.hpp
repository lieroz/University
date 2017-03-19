//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_BASE_VECTOR_ITERATOR_HPP
#define LAB_02_BASE_VECTOR_ITERATOR_HPP

#include "base_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	class base_vector_iterator : public ftl_core::base_iterator<__Tp> {
			typedef __Tp* pointer;
			typedef ptrdiff_t difference_type;
		
		public:
			base_vector_iterator(pointer);
			base_vector_iterator(const base_vector_iterator&);
			base_vector_iterator& operator=(const pointer);
			base_vector_iterator& operator=(const base_vector_iterator&);
			
			base_vector_iterator operator++();
			base_vector_iterator operator++(int);
			base_vector_iterator operator--();
			base_vector_iterator operator--(int);
			
			difference_type operator-(const base_vector_iterator&);
			
			bool operator==(const base_vector_iterator&);
			bool operator!=(const base_vector_iterator&);
	};
	
	template <class __Tp>
	base_vector_iterator<__Tp>::base_vector_iterator(pointer ptr)
			: ftl_core::base_iterator<__Tp>{ptr} {
		
	}
	
	template <class __Tp>
	base_vector_iterator<__Tp>::base_vector_iterator(const base_vector_iterator& other)
			: ftl_core::base_iterator<__Tp>{other.__ptr} {
		
	}
	
	template <class __Tp>
	base_vector_iterator<__Tp>& base_vector_iterator<__Tp>::operator=(const pointer ptr) {
		if (this->__ptr != ptr) {
			this->__ptr = ptr;
		}
		
		return *this;
	}
	
	template <class __Tp>
	base_vector_iterator<__Tp>& base_vector_iterator<__Tp>::operator=(const base_vector_iterator& rhs) {
		if (this != &rhs) {
			this->__ptr = rhs.__ptr;
		}
		
		return *this;
	}
	
	template <class __Tp>
	base_vector_iterator<__Tp> base_vector_iterator<__Tp>::operator++() {
		++this->__ptr;
		return *this;
	}
	
	template <class __Tp>
	base_vector_iterator<__Tp> base_vector_iterator<__Tp>::operator++(int) {
		base_vector_iterator temp(*this);
		operator++();
		return temp;
	}
	
	template <class __Tp>
	base_vector_iterator<__Tp> base_vector_iterator<__Tp>::operator--() {
		--this->__ptr;
		return *this;
	}
	
	template <class __Tp>
	base_vector_iterator<__Tp> base_vector_iterator<__Tp>::operator--(int) {
		base_vector_iterator temp(*this);
		operator--();
		return temp;
	}
	
	template <class __Tp>
	typename base_vector_iterator<__Tp>::difference_type base_vector_iterator<__Tp>::operator-(const base_vector_iterator<__Tp>& rhs) {
		return this->__ptr - rhs.__ptr;
	}
	
	template <class __Tp>
	bool base_vector_iterator<__Tp>::operator==(const base_vector_iterator& rhs) {
		return this->__ptr == rhs.__ptr;
	}
	
	template <class __Tp>
	bool base_vector_iterator<__Tp>::operator!=(const base_vector_iterator& rhs) {
		return this->__ptr != rhs.__ptr;
	}
}

#endif //LAB_02_BASE_VECTOR_ITERATOR_HPP
