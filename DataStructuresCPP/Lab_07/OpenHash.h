//
// Created by lieroz on 12.12.16.
//

#ifndef LAB_07_OPENHASH_H
#define LAB_07_OPENHASH_H

#include "BaseHash.h"

template <class K, class V, class F = HashFunc<K>>
class OpenHash : public BaseHash<K, V, F> {

		typedef typename BaseHash<K, V, F>::Node Node;

	public:

		explicit OpenHash() = default;
		~OpenHash() = default;

	private:

		void rehash() override;

		void _insert(const K&, const V&) override;
		void _remove(const K&) override;
		const Node* _search(const K&) override;
};

#endif // LAB_07_OPENHASH_H