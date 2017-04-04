//
// Created by lieroz on 19.03.17.
//

#ifndef LAB_02_ARRAY_ITERATOR_HPP
#define LAB_02_ARRAY_ITERATOR_HPP

#include "base_iterator.hpp"

namespace ftl {
	
	template <class __Tp>
	class set_iterator : public ftl_core::base_iterator<__Tp> {
		public:
			set_iterator(const set_iterator&);
			
			__Tp& operator*();
			__Tp* operator->();
			
			friend class ftl_core::expanding_container<__Tp>;
			
		private:
			set_iterator(__Tp*);
	};
}

#include "../implementations/set_iterator_impl.hpp"

#endif //LAB_02_ARRAY_ITERATOR_HPP
