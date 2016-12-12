//
// Created by lieroz on 12.12.16.
//

#ifndef LAB_07_BASETREE_H
#define LAB_07_BASETREE_H

#include <cstddef>

template <class T>
class BaseTree {
	protected:

		struct Node {
			T key{};
			size_t level{1};

			Node* left{};
			Node* right{};

			explicit Node(const T& _key) : key{_key} {}
			~Node() { delete left; delete right; }
		};

		Node* root{};

	public:

		BaseTree() = default;
		virtual ~BaseTree() = default;

		// Adds element to tree
		void insert(const T& _key) {
			root = insert(root, _key);
		}

		// Removes element from tree
		void remove(const T& _key) {
			root = remove(root, _key);
		}

		// Returns true if element was found
		const Node* search(const T& _key) {
			return search(root, _key);
		}

	protected:

		virtual Node* insert(Node*, const T&) = 0;
		virtual Node* remove(Node*, const T&) = 0;

	private:

		const Node* search(const Node*, const T&);
};

template <class T>
const typename BaseTree<T>::Node* BaseTree<T>::search(const Node* node, const T& value) {
	while (node != nullptr) {

		if (node->key == value) {
			return node;
		} else if (node->key < value) {
			node = node->right;
		} else {
			node = node->left;
		}
	}

	return nullptr;
}

#endif //LAB_07_BASETREE_H
