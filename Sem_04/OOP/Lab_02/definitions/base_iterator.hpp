//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_BASE_ARRAY_ITERATOR_HPP
#define LAB_02_BASE_ARRAY_ITERATOR_HPP

#include "ftlspace.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		class base_iterator {
			public:
				base_iterator(const base_iterator&);
				virtual ~base_iterator();
				base_iterator& operator=(const base_iterator&);
				
				base_iterator& operator++();
				base_iterator operator++(int);
				base_iterator& operator--();
				base_iterator operator--(int);
				
				ptrdiff_t operator-(const base_iterator&);
				
				bool operator==(const base_iterator&);
				bool operator!=(const base_iterator&);
				
			protected:
				base_iterator(__Tp*);
				
				__Tp* __ptr;
		};
	}
}

#include "../implementations/base_iterator_impl.hpp"

#endif //LAB_02_BASE_VECTOR_ITERATOR_HPP
