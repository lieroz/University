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
				typedef std::size_t size_type;
			
			public:
				explicit base_container();
				explicit base_container(size_type);
				virtual ~base_container();
				
				bool empty() const;
				size_type size() const;
			
			protected:
				size_type __el_count;
		};
	} // ftl_core
} // ftl

#include "../implementations/base_container_impl.hpp"

#endif //LAB_02_BASE_VECTOR_HPP
