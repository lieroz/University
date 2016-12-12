#include "BaseTree.h"

template <class T>
class NaiveTree : public BaseTree<T> {

		typedef typename BaseTree<T>::Node Node;

	public:

		explicit NaiveTree() = default;
		~NaiveTree() { delete BaseTree<T>::root; }

	private:

		Node* insert(Node*, const T&) override;

		Node* find_min(Node*);
		Node* remove(Node*, const T&) override;
};

template <class T>
typename BaseTree<T>::Node* NaiveTree<T>::insert(Node* node, const T& value) {
	if (node == nullptr) {
		return new Node(value);
	} else if (value < node->key) {
		node->left = insert(node->left, value);
	} else {
		node->right = insert(node->right, value);
	}

	return node;
}

template <class T>
typename BaseTree<T>::Node* NaiveTree<T>::find_min(Node* node) {
	return node->left ? find_min(node->left) : node;
}

template <class T>
typename BaseTree<T>::Node* NaiveTree<T>::remove(Node* node, const T& value) {
	if (node == nullptr) {
		return nullptr;
	}

	if (value < node->key) {
		node->left = remove(node->left, value);
	} else if (value > node->key) {
		node->right = remove(node->right, value);
	} else {

		if (node->left == nullptr) {
			Node* temp = node->right;
			delete node;
			return temp;
		} else if (node->right == nullptr) {
			Node* temp = node->left;
			delete node;
			return temp;
		}

		Node* temp = find_min(node->right);
		node->key = temp->key;
		node->right = remove(node->right, temp->key);
	}

	return node;
}