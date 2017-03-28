//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_EXPANDING_CONTAINER_HPP
#define LAB_02_EXPANDING_CONTAINER_HPP

#include <cstring>

#include "base_container.hpp"
#include "array_iterator.hpp"
#include "const_array_iterator.hpp"

namespace ftl {
	
	namespace ftl_core {
		
		template <class __Tp, class __Al>
		class expanding_container : public base_container<__Tp> {
				typedef std::size_t size_type;
				typedef __Tp value_type;
				typedef __Tp& reference;
				typedef const __Tp& const_reference;
				typedef __Tp* pointer;
				typedef const __Tp* const_pointer;
				typedef std::ptrdiff_t difference_type;
				
				const size_type __BASE_SIZE = 7;
			
			public:
				typedef array_iterator<__Tp> iterator;
				typedef const_array_iterator<__Tp> const_iterator;
				
				explicit expanding_container();
				explicit expanding_container(size_type);
				explicit expanding_container(size_type, const value_type&);
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
				reference at(size_type);
				const_reference at(size_type) const;
				reference operator[](size_type);
				const_reference operator[](size_type) const;
				reference front();
				const_reference front() const;
				reference back();
				const_reference back() const;
				pointer data();
				const_pointer data() const;
				
				// Iterators
				pointer begin();
				const_pointer begin() const;
				const_pointer cbegin() const;
				pointer end();
				const_pointer end() const;
				const_pointer cend() const;
				
				// Capacity operations
				size_type capacity() const;
				
				// Modifiers
				void clear();
				void swap(expanding_container&);
				
				template <class T>
				friend inline void swap(T&, T&);
				
				// Compare operators
				template <class T>
				friend inline bool operator==(const T&, const T&);
				template <class T>
				friend inline bool operator!=(const T&, const T&);
				template <class T>
				friend inline bool operator<(const T&, const T&);
				template <class T>
				friend inline bool operator<=(const T&, const T&);
				template <class T>
				friend inline bool operator>(const T&, const T&);
				template <class T>
				friend inline bool operator>=(const T&, const T&);
				
				template <class T, class A>
				friend inline std::ostream& operator<<(std::ostream&, const expanding_container<T, A>&);
			
			protected:
				size_type __mem_dump;
				value_type* __buffer;
				
				inline void reallocate();
		};
	}
}

#include "../implementations/expanding_container_impl.hpp"

#endif //LAB_02_EXPANDING_CONTAINER_HPP
