//
// Created by lieroz on 12.12.16.
//

#ifndef LAB_07_OPENHASH_H
#define LAB_07_OPENHASH_H

#include "BaseHash.h"

template <class T, class HASH_FUNC>
class OpenHash : public BaseHash<T, HASH_FUNC> {

		typedef typename BaseHash<T, HASH_FUNC>::Node Node;

	public:

		explicit OpenHash() = default;
		~OpenHash() = default;

	private:

		void rehash() override;

		void _insert(const T&) override;
		void _remove(const T&) override;
		const T& _search(const T&) override;

		void print(std::ostream&) const override;
};

#endif // LAB_07_OPENHASH_H