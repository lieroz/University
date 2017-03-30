//
// Created by lieroz on 17.03.17.
//

#ifndef LAB_02_BASE_VECTOR_HPP
#define LAB_02_BASE_VECTOR_HPP

#include "ftlspace.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		class base_container {
			public:
				explicit base_container();
				explicit base_container(size_t);
				virtual ~base_container();
				
				bool empty() const;
				size_t size() const;
			
			protected:
				size_t __el_count;
		};
	}
}

#endif //LAB_02_BASE_VECTOR_HPP
