//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_BASE_ARRAY_ITERATOR_IMPL_HPP
#define LAB_02_BASE_ARRAY_ITERATOR_IMPL_HPP

#include "base_iterator.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		base_iterator<__Tp>::base_iterator(__Tp* ptr) {
			this->__ptr = ptr;
		}
		
		template <class __Tp>
		base_iterator<__Tp>::base_iterator(const base_iterator& other) {
			this->__ptr = other.__ptr;
		}
		
		template <class __Tp>
		base_iterator<__Tp>::~base_iterator() {
			this->__ptr = nullptr;
		}
		
		template <class __Tp>
		base_iterator<__Tp>& base_iterator<__Tp>::operator=(const base_iterator& rhs) {
			if (this != &rhs) {
				this->__ptr = rhs.__ptr;
			}
			
			return *this;
		}
		
		template <class __Tp>
		base_iterator<__Tp>& base_iterator<__Tp>::operator++() {
			++this->__ptr;
			return *this;
		}
		
		template <class __Tp>
		base_iterator<__Tp> base_iterator<__Tp>::operator++(int) {
			base_iterator temp(*this);
			this->operator++();
			return temp;
		}
		
		template <class __Tp>
		base_iterator<__Tp>& base_iterator<__Tp>::operator--() {
			--this->__ptr;
			return *this;
		}
		
		template <class __Tp>
		base_iterator<__Tp> base_iterator<__Tp>::operator--(int) {
			base_iterator temp(*this);
			this->operator--();
			return temp;
		}
		
		template <class __Tp>
		ptrdiff_t base_iterator<__Tp>::operator-(const base_iterator<__Tp>& rhs) {
			return this->__ptr - rhs.__ptr;
		}
		
		template <class __Tp>
		bool base_iterator<__Tp>::operator==(const base_iterator& rhs) {
			return this->__ptr == rhs.__ptr;
		}
		
		template <class __Tp>
		bool base_iterator<__Tp>::operator!=(const base_iterator& rhs) {
			return this->__ptr != rhs.__ptr;
		}
	}
}
#endif // LAB_02_BASE_ARRAY_ITERATOR_IMPL_HPP
