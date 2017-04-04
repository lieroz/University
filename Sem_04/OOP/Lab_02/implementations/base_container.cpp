//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_BASE_CONTAINER_IMPL_HPP
#define LAB_02_BASE_CONTAINER_IMPL_HPP

#include "base_container.hpp"

using namespace ftl::ftl_core;

base_container::base_container()
		: __el_count(0) {
}

base_container::base_container(size_t count)
		: __el_count(count) {
}

base_container::~base_container() {
	this->__el_count = 0;
}

bool base_container::empty() const {
	return this->size() == 0;
}

size_t base_container::size() const {
	return this->__el_count;
}

#endif //LAB_02_BASE_CONTAINER_IMPL_HPP
