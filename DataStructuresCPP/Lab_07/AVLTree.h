#include "BaseTree.h"

template <class T>
class AVLTree : public BaseTree<T> {

		typedef typename BaseTree<T>::Node Node;

	public:

		explicit AVLTree() = default;
		~AVLTree() { delete BaseTree<T>::root; }

	private:

		Node* insert(Node*, const T&) override;

		Node* find_min(Node*);
		Node* remove(Node*, const T&) override;

		const size_t node_level(const Node*);
		const int balance_factor(const Node*);
		void fix_height(Node*);
		Node* rotate_right(Node*);
		Node* rotate_left(Node*);
		Node* balance(Node*);
};

template <class T>
const size_t AVLTree<T>::node_level(const Node* node) {
	return node ? node->level : 0;
}

template <class T>
const int AVLTree<T>::balance_factor(const Node* node) {
	return static_cast<int>(node_level(node->right) - node_level(node->left));
}

template <class T>
void AVLTree<T>::fix_height(Node* node) {
	size_t left_level{node_level(node->left)};
	size_t right_level{node_level(node->right)};
	node->level = (left_level > right_level ? left_level : right_level) + 1;
}

template <class T>
typename BaseTree<T>::Node* AVLTree<T>::rotate_right(Node* node) {
	Node* left(node->left);
	node->left = left->right;
	left->right = node;

	fix_height(node);
	fix_height(left);

	return left;
}

template <class T>
typename BaseTree<T>::Node* AVLTree<T>::rotate_left(Node* node) {
	Node* right(node->right);
	node->right = right->left;
	right->left = node;

	fix_height(node);
	fix_height(right);

	return right;
}

template <class T>
typename BaseTree<T>::Node* AVLTree<T>::balance(Node* node) {
	fix_height(node);

	if (balance_factor(node) == 2) {

		if (balance_factor(node->right) < 0) {
			node->right = rotate_right(node->right);
		}

		return rotate_left(node);
	}

	if (balance_factor(node) == -2) {

		if (balance_factor(node->left) > 0) {
			node->left = rotate_left(node->left);
		}

		return rotate_right(node);
	}

	return node;
}

template <class T>
typename BaseTree<T>::Node* AVLTree<T>::insert(Node* node, const T& value) {
	if (!node) {
		return new Node(value);
	} else if (value < node->key) {
		node->left = insert(node->left, value);
	} else {
		node->right = insert(node->right, value);
	}

	return balance(node);
}

template <class T>
typename BaseTree<T>::Node* AVLTree<T>::find_min(Node* node) {
	return node->left ? find_min(node->left) : node;
}

template <class T>
typename BaseTree<T>::Node* AVLTree<T>::remove(Node* node, const T& value) {
	if (node == nullptr) {
		return nullptr;
	}

	if (value < node->key) {
		node->left = remove(node->left, value);
	} else if (value > node->key) {
		node->right = remove(node->right, value);
	} else {

		if (node->left == nullptr || node->right == nullptr) {
			Node* temp = node->left ? node->left : node->right;

			if (temp == nullptr) {
				temp = node;
				node = nullptr;
			} else {
				*node = *temp;
			}

			delete temp;
		} else {
			Node* temp = find_min(node->right);
			node->key = temp->key;
			node->right = remove(node->right, temp->key);
		}
	}

	if (node == nullptr) {
		return node;
	}

	return balance(node);
}