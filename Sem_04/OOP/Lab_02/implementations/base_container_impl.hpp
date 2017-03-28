//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_BASE_CONTAINER_IMPL_HPP
#define LAB_02_BASE_CONTAINER_IMPL_HPP

#include "base_container.hpp"

namespace ftl {
	
	namespace ftl_core {
		
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
		
		template <class __Tp>
		bool base_container<__Tp>::empty() const {
			return this->size() == 0;
		}
		
		template <class __Tp>
		typename base_container<__Tp>::size_type base_container<__Tp>::size() const {
			return this->__el_count;
		}
	}
}

#endif //LAB_02_BASE_CONTAINER_IMPL_HPP
