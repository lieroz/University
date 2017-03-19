//
// Created by lieroz on 17.03.17.
//

#ifndef LAB_02_BASE_VECTOR_HPP
#define LAB_02_BASE_VECTOR_HPP

#include "ftlspace.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		class base_container {
				typedef size_t size_type;
			
			public:
				explicit base_container();
				explicit base_container(size_type);
				virtual ~base_container();
			
			protected:
				size_type __el_count;
		};
		
		template <class __Tp>
		base_container<__Tp>::base_container()
				: __el_count(0) {
			
		}
		
		template <class __Tp>
		base_container<__Tp>::base_container(size_type count)
				: __el_count(count) {
			
		}
		
		template <class __Tp>
		base_container<__Tp>::~base_container() {
			this->__el_count = 0;
		}
	} // ftl_core
} // ftl

#endif //LAB_02_BASE_VECTOR_HPP
