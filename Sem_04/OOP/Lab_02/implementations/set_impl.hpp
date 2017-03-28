//
// Created by lieroz on 28.03.17.
//

#ifndef LAB_02_SET_IMPL_HPP
#define LAB_02_SET_IMPL_HPP

#include "set.hpp"

namespace ftl {
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>::set()
			: ftl_core::expanding_container<__Tp, __Al>() {
		
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>::set(size_type count)
			: ftl_core::expanding_container<__Tp, __Al>(count) {
		
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>::set(size_type count, const value_type& value)
			: ftl_core::expanding_container<__Tp, __Al>(count, value) {
		
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>::set(iterator first, iterator last)
			: ftl_core::expanding_container<__Tp, __Al>(first, last) {
		
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>::set(const_iterator first, const_iterator last)
			: ftl_core::expanding_container<__Tp, __Al>(first, last) {
		
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>::set(std::initializer_list<__Tp> lst)
			: ftl_core::expanding_container<__Tp, __Al>(lst) {
		
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>::set(const set<__Tp, __Al>& other)
			: ftl_core::expanding_container<__Tp, __Al>(other) {
		
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>::set(set<__Tp, __Al>&& other)
			: ftl_core::expanding_container<__Tp, __Al>(std::move(other)) {
		
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>& set<__Tp, __Al>::operator=(const set<__Tp, __Al>& rhs) {
		ftl_core::expanding_container<__Tp, __Al>::operator=(rhs);
		return *this;
	}
	
	template <class __Tp, class __Al>
	set<__Tp, __Al>& set<__Tp, __Al>::operator=(set<__Tp, __Al>&& rhs) {
		ftl_core::expanding_container<__Tp, __Al>::operator=(std::move(rhs));
		return *this;
	}
	
	template <class __Tp, class __Al>
	void set<__Tp, __Al>::add(const value_type& value) {
		if (!this->contains(value)) {
			
			if (this->size() == this->capacity()) {
				this->__mem_dump <<= __GROW_COEF;
				this->reallocate();
			}
			
			(*this)[this->__el_count++] = value;
		}
	}
	
	template <class __Tp, class __Al>
	void set<__Tp, __Al>::remove(const value_type& value) {
		int pos = find_item_index(value);
		
		if (pos < 0) {
			throw std::out_of_range("Removed item doesn't exist in set!");
		}
		
		value_type* mem_flag = this->__buffer + pos;
		(*this)[pos].~__Tp();
		std::memmove(mem_flag, mem_flag + 1, (this->size() - (mem_flag - this->__buffer) - 1) * sizeof(__Tp));
		--this->__el_count;
	}
	
	template <class __Tp, class __Al>
	bool set<__Tp, __Al>::contains(const value_type& value) {
		return this->find_item_index(value) >= 0;
	}
	
	template <class __Tp, class __Al>
	bool set<__Tp, __Al>::contains(const value_type& value) const {
		return this->find_item_index(value) >= 0;
	}
	
	template <class __Tp, class __Al>
	int set<__Tp, __Al>::count(const value_type& value) {
		return static_cast<int>([this, &value]() -> int {
			int amount = 0;
			
			for (const_iterator iter = this->cbegin(); iter != this->cend(); ++iter) {
				amount += *iter == value;
			}
			
			return amount;
		});
	}
	
	template <class T>
	set<T> operator^(const set<T>& first, const set<T>& second) {
		set<T> result_set;
		
		for (const auto& i : first) {
			
			for (const auto& j : second) {
				
				if (i == j) {
					result_set.add(i);
				}
			}
		}
		
		return result_set;
	}
	
	template <class T>
	set<T> operator+(const set<T>& first, const set<T>& second) {
		set<T> result_set = first;
		
		for (const auto& item : second) {
			result_set.add(item);
		}
		
		return result_set;
	}
	
	template <class T>
	set<T> operator-(const set<T>& first, const set<T>& second) {
		set<T> result_set = first;
		
		for (const auto& item : second) {
			
			if (result_set.contains(item)) {
				result_set.remove(item);
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
	
	template <class __Tp, class __Al>
	int set<__Tp, __Al>::find_item_index(const value_type& value) const {
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
