//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_BASE_ARRAY_ITERATOR_HPP
#define LAB_02_BASE_ARRAY_ITERATOR_HPP

#include "base_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	class base_array_iterator : public ftl_core::base_iterator<__Tp> {
			typedef __Tp* pointer;
			typedef std::ptrdiff_t difference_type;
		
		public:
			base_array_iterator(pointer);
			base_array_iterator(const base_array_iterator&);
			base_array_iterator& operator=(const pointer);
			base_array_iterator& operator=(const base_array_iterator&);
			
			base_array_iterator& operator++();
			base_array_iterator operator++(int);
			base_array_iterator& operator--();
			base_array_iterator operator--(int);
			
			difference_type operator-(const base_array_iterator&);
			
			bool operator==(const base_array_iterator&);
			bool operator!=(const base_array_iterator&);
	};
}

#include "../implementations/base_array_iterator_impl.hpp"

#endif //LAB_02_BASE_VECTOR_ITERATOR_HPP
