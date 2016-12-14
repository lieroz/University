//
// Created by lieroz on 12.12.16.
//

#ifndef LAB_07_BASEHASH_H
#define LAB_07_BASEHASH_H

#include <cstddef>

#include "Colors.h"

template <class T, class HASH_FUNC>
class BaseHash {
	protected:

		const size_t INIT_SIZE = 128;
		const double REHASH = 0.75;

		struct Node {
			T key{};
			bool is_deleted{false};

			Node* next{};

			explicit Node(const T& _key)
				: key{_key} {}
		};

		HASH_FUNC hash_func;
		size_t table_size{};
		std::vector<Node*> table{INIT_SIZE, nullptr};

	public:

		explicit BaseHash() = default;
		virtual ~BaseHash() = default;

		// Inserts element into a hash table
		void insert(const T& _key) {
			if (static_cast<double>(BaseHash<T, HASH_FUNC>::table_size)
				/ static_cast<double>(BaseHash<T, HASH_FUNC>::table.size()) >= BaseHash<T, HASH_FUNC>::REHASH) {
				rehash();
			}

			_insert(_key);
		}

		// Removes element from hash table
		void remove(const T& _key) {
			_remove(_key);
		}

		// Searches hash table for element
		const T& search(const T& _key) {
			return _search(_key);
		}

		template <class U, class F>
		friend std::ostream& operator<<(std::ostream& out, const BaseHash<U, F>& hash_table) {
			hash_table.print(out);
			return out;
		}

	protected:

		virtual void rehash() = 0;

		virtual void _insert(const T&) = 0;
		virtual void _remove(const T&) = 0;
		virtual const T& _search(const T&) = 0;

		virtual void print(std::ostream&) const = 0;
};

#endif //LAB_07_BASEHASH_H
