//
// Created by lieroz on 12.12.16.
//

#ifndef LAB_07_CLOSEDHASH_H
#define LAB_07_CLOSEDHASH_H

#include "BaseHash.h"

template <class K, class V, class F = HashFunc<K>>
class ClosedHash : public BaseHash<K, V, F> {

		typedef typename BaseHash<K, V, F>::Node Node;

	public:

		explicit ClosedHash() = default;
		~ClosedHash();

	private:

		void rehash() override;

		void _insert(const K&, const V&) override;
		void _remove(const K&) override;
		const Node* _search(const K&) override;
};

template <class K, class V, class F>
ClosedHash<K, V, F>::~ClosedHash() {
	for (size_t hash{}; hash < BaseHash<K, V, F>::base_size; ++hash) {

		if (BaseHash<K, V, F>::table[hash] != nullptr) {
			Node* p_crawl = BaseHash<K, V, F>::table[hash];

			while (p_crawl != nullptr) {
				Node* prev = p_crawl;
				p_crawl = p_crawl->next;
				delete prev;
			}
		}
	}
}

template <class K, class V, class F>
void ClosedHash<K, V, F>::rehash() {
	size_t old_table_size{BaseHash<K, V, F>::base_size};
	BaseHash<K, V, F>::base_size *= 2;
	std::vector<Node*> old_table{BaseHash<K, V, F>::table};
	BaseHash<K, V, F>::table.resize(BaseHash<K, V, F>::base_size, nullptr);
	BaseHash<K, V, F>::table_size = 0;

	for (size_t hash{}; hash < old_table_size; ++hash) {

		if (old_table[hash] != nullptr) {
			Node* p_crawl = old_table[hash];

			while (p_crawl != nullptr) {
				_insert(p_crawl->key, p_crawl->value);
				Node* temp = p_crawl;
				p_crawl = p_crawl->next;
				delete temp;
			}
		}
	}
}

template <class K, class V, class F>
void ClosedHash<K, V, F>::_insert(const K& _key, const V& _value) {
	auto hash = BaseHash<K, V, F>::hash_func(_key, BaseHash<K, V, F>::base_size);

	if (BaseHash<K, V, F>::table[hash] == nullptr) {
		BaseHash<K, V, F>::table[hash] = new Node(_key, _value);
		++BaseHash<K, V, F>::table_size;
	} else {
		Node* p_crawl = BaseHash<K, V, F>::table[hash];

		while (p_crawl->next != nullptr) {
			p_crawl = p_crawl->next;
		}

		if (p_crawl->key == _key) {
			p_crawl->value = _value;
		} else {
			p_crawl->next = new Node(_key, _value);
		}
	}

	if ((static_cast<double>(BaseHash<K, V, F>::table_size) / static_cast<double>(BaseHash<K, V, F>::base_size))
		>= BaseHash<K, V, F>::REHASH) {
		rehash();
	}
};

template <class K, class V, class F>
void ClosedHash<K, V, F>::_remove(const K& _key) {
	auto hash = BaseHash<K, V, F>::hash_func(_key, BaseHash<K, V, F>::base_size);

	if (BaseHash<K, V, F>::table[hash] != nullptr) {
		Node* prev{nullptr};
		Node* p_crawl{BaseHash<K, V, F>::table[hash]};

		while (p_crawl->next != nullptr && p_crawl->key != _key) {
			prev = p_crawl;
			p_crawl = p_crawl->next;
		}

		if (p_crawl->key == _key) {
			if (prev == nullptr) {
				Node* next{p_crawl->next};
				delete p_crawl;
				BaseHash<K, V, F>::table[hash] = next;
			} else {
				Node* next = p_crawl->next;
				delete p_crawl;
				prev->next = next;
			}

			--BaseHash<K, V, F>::table_size;
		}
	}
}

template <class K, class V, class F>
const typename BaseHash<K, V, F>::Node* ClosedHash<K, V, F>::_search(const K& _key) {
	auto hash = BaseHash<K, V, F>::hash_func(_key, BaseHash<K, V, F>::base_size);

	if (BaseHash<K, V, F>::table[hash] == nullptr) {
		return nullptr;
	} else {
		Node* p_crawl = BaseHash<K, V, F>::table[hash];

		while (p_crawl != nullptr && p_crawl->key != _key) {
			p_crawl = p_crawl->next;
		}

		if (p_crawl == nullptr) {
			return nullptr;
		} else {
			return p_crawl;
		}
	}
}

#endif // LAB_07_CLOSEDHASH_H