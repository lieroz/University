//
// Created by lieroz on 17.03.17.
//

#ifndef LAB_02_FTLSPACE_HPP
#define LAB_02_FTLSPACE_HPP

#include <cstddef>

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp> class base_iterator;
		template <class __Tp> class base_allocator;
		template <class __Tp> class base_container;
	} // faster than light core
	
	template <class __Tp> class base_vector_iterator;
	template <class __Tp> class vector_iterator;
	template <class __Tp> class const_vector_iterator;
	template <class __Tp, class __Al> class vector;
} // faster than light


#endif // LAB_02_FTLSPACE_HPP
