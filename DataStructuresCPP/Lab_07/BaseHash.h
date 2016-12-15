//
// Created by lieroz on 12.12.16.
//

#ifndef LAB_07_BASEHASH_H
#define LAB_07_BASEHASH_H

#include <cstddef>

#include "Colors.h"
#include "Timer.h"

template <class T, class HASH_FUNC>
class BaseHash {
	protected:

		const size_t INIT_SIZE = 128;
		const double REHASH_FACTOR = 0.72;

		struct Node {
			private:

				static size_t cmp_count;

			public:

				T key{};
				bool is_deleted{false};

				Node* next{};

				explicit Node(const T& _key)
					: key{_key} {}

				inline bool operator==(const T& rhs) {
					++cmp_count;
					return this->key == rhs;
				}

				static const size_t get_cmp_count() {
					return cmp_count;
				}

				static void reset_cmp_count() {
					cmp_count = 0;
				}
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
				/ static_cast<double>(BaseHash<T, HASH_FUNC>::table.size()) >= BaseHash<T, HASH_FUNC>::REHASH_FACTOR) {
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
			BaseHash<T, HASH_FUNC>::Node::reset_cmp_count();
			return _search(_key);
		}

		template <class U, class F>
		friend std::ostream& operator<<(std::ostream& out, const BaseHash<U, F>& hash_table) {
			hash_table.print(out);
			return out;
		}

		const size_t get_cmp_count() const {
			return BaseHash<T, HASH_FUNC>::Node::get_cmp_count();
		}

		const size_t get_memory_amount() const {
			return _get_memory_amount();
		}

	protected:

		virtual void rehash() = 0;

		virtual void _insert(const T&) = 0;
		virtual void _remove(const T&) = 0;
		virtual const T& _search(const T&) = 0;

		virtual const size_t _get_memory_amount() const = 0;

		virtual void print(std::ostream&) const = 0;
};

template <class T, class HASH_FUNC>
size_t BaseHash<T, HASH_FUNC>::Node::cmp_count{};

#endif //LAB_07_BASEHASH_H
