//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_CONST_VECTOR_ITERATOR_HPP
#define LAB_02_CONST_VECTOR_ITERATOR_HPP

#include "base_array_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	class const_array_iterator : public base_array_iterator<__Tp> {
			typedef __Tp* pointer;
			typedef const __Tp* const_pointer;
			typedef const __Tp& const_reference;
		
		public:
			const_array_iterator(pointer);
			const_array_iterator(const const_array_iterator&);
			
			const_reference operator*();
			const_pointer operator->();
	};
}

#include "../implementation/const_array_iterator_impl.hpp"

#endif //LAB_02_CONST_VECTOR_ITERATOR_HPP
