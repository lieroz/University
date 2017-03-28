//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_BASE_ITERATOR_HPP
#define LAB_02_BASE_ITERATOR_HPP

#include "ftlspace.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		class base_iterator {
				typedef __Tp* pointer;
			
			public:
				explicit base_iterator();
				explicit base_iterator(pointer ptr);
				virtual ~base_iterator();
			
			protected:
				pointer __ptr;
		};
	}
}

#include "../implementations/base_iterator_impl.hpp"

#endif //LAB_02_BASE_ITERATOR_HPP
