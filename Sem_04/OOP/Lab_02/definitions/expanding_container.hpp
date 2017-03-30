//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_EXPANDING_CONTAINER_HPP
#define LAB_02_EXPANDING_CONTAINER_HPP

#include <cstring>
#include <initializer_list>

#include "base_container.hpp"
#include "set_iterator.hpp"
#include "const_set_iterator.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp>
		class expanding_container : public base_container {
				const size_t __BASE_SIZE = 7;
			
			public:
				typedef set_iterator<__Tp> iterator;
				typedef const_set_iterator<__Tp> const_iterator;
				
				explicit expanding_container();
				explicit expanding_container(size_t);
				explicit expanding_container(size_t, const __Tp&);
				expanding_container(iterator, iterator);
				expanding_container(const_iterator, const_iterator);
				expanding_container(std::initializer_list<__Tp>);
				expanding_container(const expanding_container&);
				expanding_container(expanding_container&&);
				virtual ~expanding_container();
				expanding_container& operator=(const expanding_container&);
				expanding_container& operator=(expanding_container&&);
				expanding_container& operator=(std::initializer_list<__Tp>);
				
				// Data access opertator
				__Tp& at(size_t);
				const __Tp& at(size_t) const;
				__Tp& operator[](size_t);
				const __Tp& operator[](size_t) const;
				__Tp& front();
				const __Tp& front() const;
				__Tp& back();
				const __Tp& back() const;
				__Tp* data();
				const __Tp* data() const;
				
				// Iterators
				iterator begin();
				const_iterator cbegin() const;
				iterator end();
				const_iterator cend() const;
				
				iterator rbegin();
				const_iterator rcbegin() const;
				iterator rend();
				const_iterator rcend() const;
				
				// Capacity operations
				size_t capacity() const;
				
				// Modifiers
				void clear();
				void swap(expanding_container&);
				
				template <class T>
				friend inline void swap(expanding_container<T>&, expanding_container<T>&);
				
				// Compare operators
				template <class T>
				friend inline bool operator==(const expanding_container<T>&, const expanding_container<T>&);
				template <class T>
				friend inline bool operator!=(const expanding_container<T>&, const expanding_container<T>&);
				template <class T>
				friend inline bool operator<(const expanding_container<T>&, const expanding_container<T>&);
				template <class T>
				friend inline bool operator<=(const expanding_container<T>&, const expanding_container<T>&);
				template <class T>
				friend inline bool operator>(const expanding_container<T>&, const expanding_container<T>&);
				template <class T>
				friend inline bool operator>=(const expanding_container<T>&, const expanding_container<T>&);
				
				template <class T>
				friend inline std::ostream& operator<<(std::ostream&, const expanding_container<T>&);
			
			protected:
				size_t __mem_dump;
				__Tp* __buffer;
				
				inline void reallocate();
		};
	}
}

#include "../implementations/expanding_container_impl.hpp"

#endif //LAB_02_EXPANDING_CONTAINER_HPP
