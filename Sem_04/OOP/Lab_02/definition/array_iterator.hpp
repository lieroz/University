//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_ARRAY_ITERATOR_HPP
#define LAB_02_ARRAY_ITERATOR_HPP

#include "base_array_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	class array_iterator : public base_array_iterator<__Tp> {
			typedef __Tp& reference;
			typedef __Tp* pointer;
		
		public:
			array_iterator(pointer);
			array_iterator(const array_iterator&);
			
			reference operator*();
			pointer operator->();
	};
}

#include "../implementation/array_iterator_impl.hpp"

#endif //LAB_02_ARRAY_ITERATOR_HPP
