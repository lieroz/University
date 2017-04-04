//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_CONST_VECTOR_ITERATOR_HPP
#define LAB_02_CONST_VECTOR_ITERATOR_HPP

#include "base_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	class const_set_iterator : public ftl_core::base_iterator<__Tp> {
		public:
			const_set_iterator(const const_set_iterator&);
			
			const __Tp& operator*();
			const __Tp* operator->();
			
			friend class ftl_core::expanding_container<__Tp>;
			
		private:
			const_set_iterator(__Tp*);
	};
}

#include "../implementations/const_set_iterator_impl.hpp"

#endif //LAB_02_CONST_VECTOR_ITERATOR_HPP
