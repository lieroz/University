//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_SET_IMPL_HPP
#define LAB_02_SET_IMPL_HPP

#include "set.hpp"
#include "exceptions.hpp"

namespace ftl {
	template <class __Tp>
	set<__Tp>::set()
			: ftl_core::expanding_container<__Tp>() {
	}
	
	template <class __Tp>
	set<__Tp>::set(size_t count)
			: ftl_core::expanding_container<__Tp>(count) {
	}
	
	template <class __Tp>
	set<__Tp>::set(size_t count, const __Tp& value)
			: ftl_core::expanding_container<__Tp>(count, value) {
	}
	
	template <class __Tp>
	set<__Tp>::set(iterator first, iterator last)
			: ftl_core::expanding_container<__Tp>(first, last) {
	}
	
	template <class __Tp>
	set<__Tp>::set(const_iterator first, const_iterator last)
			: ftl_core::expanding_container<__Tp>(first, last) {
	}
	
	template <class __Tp>
	set<__Tp>::set(std::initializer_list<__Tp> lst)
			: ftl_core::expanding_container<__Tp>(lst) {
	}
	
	template <class __Tp>
	set<__Tp>::set(const set<__Tp>& other)
			: ftl_core::expanding_container<__Tp>(other) {
	}
	
	template <class __Tp>
	set<__Tp>::set(set<__Tp>&& other)
			: ftl_core::expanding_container<__Tp>(std::move(other)) {
	}
	
	template <class __Tp>
	set<__Tp>& set<__Tp>::operator=(const set<__Tp>& rhs) {
		ftl_core::expanding_container<__Tp>::operator=(rhs);
		return *this;
	}
	
	template <class __Tp>
	set<__Tp>& set<__Tp>::operator=(set<__Tp>&& rhs) {
		ftl_core::expanding_container<__Tp>::operator=(std::move(rhs));
		return *this;
	}
	
	template <class __Tp>
	void set<__Tp>::add(const __Tp& value) {
		if (!this->contains(value)) {
			
			if (this->size() == this->capacity()) {
				this->__mem_dump <<= __GROW_COEF;
				this->reallocate();
			}
			
			(*this)[this->__el_count++] = value;
		}
	}
	
	template <class __Tp>
	void set<__Tp>::remove(const __Tp& value) {
		int pos = find_item_index(value);
		
		if (pos < 0) {
			throw item_not_found_exception();
		}
		
		__Tp* mem_flag = this->__buffer + pos;
		(*this)[pos].~__Tp();
		std::memmove(mem_flag, mem_flag + 1, (this->size() - (mem_flag - this->__buffer) - 1) * sizeof(__Tp));
		--this->__el_count;
	}
	
	template <class __Tp>
	bool set<__Tp>::contains(const __Tp& value) {
		return this->find_item_index(value) >= 0;
	}
	
	template <class __Tp>
	bool set<__Tp>::contains(const __Tp& value) const {
		return this->find_item_index(value) >= 0;
	}
	
	template <class __Tp>
	int set<__Tp>::count(const __Tp& value) {
		return static_cast<int>([this, &value]() -> int {
			int amount = 0;
			
			for (const_iterator iter = this->cbegin(); iter != this->cend(); ++iter) {
				amount += *iter == value;
			}
			
			return amount;
		});
	}
	
	template <class __Tp>
	size_t set<__Tp>::power() const {
		return this->size();
	};
	
	
	template <class T>
	set<T> operator^(const set<T>& first, const set<T>& second) {
		set<T> result_set;
		
		for (typename set<T>::const_iterator i = first.cbegin(); i != first.cend(); ++i) {
			
			for (typename set<T>::const_iterator j = second.cbegin(); j != second.cend(); ++j) {
				
				if (*i == *j) {
					result_set.add(*i);
				}
			}
		}
		
		return result_set;
	}
	
	template <class T>
	set<T> operator+(const set<T>& first, const set<T>& second) {
		set<T> result_set = first;
		
		for (typename set<T>::const_iterator iter = second.cbegin(); iter != second.cend(); ++iter) {
			result_set.add(*iter);
		}
		
		return result_set;
	}
	
	template <class T>
	set<T> operator-(const set<T>& first, const set<T>& second) {
		set<T> result_set = first;
		
		for (typename set<T>::const_iterator iter = second.cbegin(); iter != second.cend(); ++iter) {
			
			if (result_set.contains(*iter)) {
				result_set.remove(*iter);
			}
		}
		
		return result_set;
	}
	
	template <class T>
	set<T> Intersection(const set<T>& first, const set<T>& second) {
		return operator^(first, second);
	}
	
	template <class T>
	set<T> Union(const set<T>& first, const set<T>& second) {
		return operator+(first, second);
	}
	
	template <class T>
	set<T> Subtraction(const set<T>& first, const set<T>& second) {
		return operator-(first, second);
	}
	
	template <class __Tp>
	int set<__Tp>::find_item_index(const __Tp& value) const {
		int item_index = -1;
		
		for (int i = 0; i < this->size() && item_index == -1; ++i) {
			
			if ((*this)[i] == value) {
				item_index = i;
			}
		}
		
		return item_index;
	}
}

#endif //LAB_02_SET_IMPL_HPP
