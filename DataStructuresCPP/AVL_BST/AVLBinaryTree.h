#ifndef AVLBINARYTREE_H_DEF
#define AVLBINARYTREE_H_DEF

#include <iostream>
#include <deque>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "Node.h"
#include "ColorModifier.h"

// Declaration of AVL-tree class

template <class T>
class AVLBinaryTree {
	private:
		// Root of tree
		Node<T>* _root{};

		/* level control how wide you want the tree to sparse
		 * (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes) */
		const size_t _level = 7;
		/* indent space  Change this to add some indent space to the left
		 * (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin) */
		const size_t _indent = 0;

	public:
		// Constructors & destructor
		explicit AVLBinaryTree() = default; // No need to define specific parameters
		AVLBinaryTree(const AVLBinaryTree&) {} // Copy constructor TODO
		AVLBinaryTree(const AVLBinaryTree&&) {} // Move constructor TODO
		~AVLBinaryTree(); // Destructor - destroys tree after finishing working with it

		// Adds Node to tree with priority
		void insert(const T&);
		// Removes Node from tree saving tree properties
		void remove(const T&);
		// Finds a Node with a specific key
		const Node<T>* search(const T&) const;
		// Returns the amount of nodes in tree
		const size_t& size() const;
		// Returns maximum height of tree
		const size_t& height() const;
		// Deletes all words with specified first character
		void delete_by_first(const char&);

		// Prints tree into output stream
		template <class U>
		friend std::ostream& operator<<(std::ostream&, AVLBinaryTree<U>&);

	private:
		// Clears tree in postorder
		void clear_tree(Node<T>*);

		// Inserts Node into a tree if key is unique
		Node<T>* insert(Node<T>*, const T&);
		// Removes Node with specified key from tree
		Node<T>* find_min(Node<T>*);
		Node<T>* remove_min(Node<T>*);
		Node<T>* remove(Node<T>*, const T&);
		// Finds Node with a specific key in a tree
		const Node<T>* search(const Node<T>*, const T&) const;
		// Computes the amount of Nodes in a tree
		const size_t& size(Node<T>*) const;
		// Computes the length of tree
		const size_t& height(Node<T>*) const;
		// Traverses tree in pre_order deleting Nodes with specifie dvalue
		void delete_by_first(Node<T>*, const char&);

		// Helpful methods for balancing
		// Returs the level on which Node is located
		const size_t& node_level(Node<T>*) const;
		// Computes difference between two branches
		const int& bfactor(Node<T>*) const;
		// Fixes height between two branches
		void fix_height(Node<T>*);
		// Rotates tree onto right side if right branch is heavier
		Node<T>* rotate_right(Node<T>*);
		// Rotates tree onto left side if left branch is heavier
		Node<T>* rotate_left(Node<T>*);
		// Restores balance between branches
		Node<T>* balance(Node<T>*);

		// Helpful methods for printing tree into output stream
		// Transfers all data to string
		std::string to_string(T);
		// Print the arm branches (eg, /    \ ) on a line
		void print_branches(std::ostream&, const std::deque<Node<T>*>&, size_t, size_t, size_t, size_t);
		// Print the branches and node (eg, ___10___ )
		void print_nodes(std::ostream&, const std::deque<Node<T>*>&, size_t, size_t, size_t, size_t);
		// Print the leaves only (just for the bottom row)
		void print_leaves(std::ostream&, const std::deque<Node<T>*>&, size_t, size_t, size_t);
		// Pretty formatting of a binary tree to the output stream
		void print_pretty(std::ostream&, Node<T>*, size_t level, size_t indent_space);
		// pretty_print wrapper
		void print(std::ostream&);
};

// Implementation of AVL-tree class
//----------------------------------------------------------------------------------------------------------------------
template <class T>
void AVLBinaryTree<T>::clear_tree(Node<T>* tree) {
	if (tree != nullptr) {
		clear_tree(tree->get_left());
		clear_tree(tree->get_right());
		delete tree;
	}
}

template <class T>
AVLBinaryTree<T>::~AVLBinaryTree() {
	clear_tree(_root);
	_root = nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
const size_t& AVLBinaryTree<T>::node_level(Node<T>* node) const {
	return node ? node->get_level() : 0;
}

template <class T>
const int& AVLBinaryTree<T>::bfactor(Node<T>* node) const {
	return static_cast<int>(node_level(node->get_right()) - node_level(node->get_left()));
}

template <class T>
void AVLBinaryTree<T>::fix_height(Node<T>* node) {
	size_t left_level{node_level(node->get_left())};
	size_t right_level{node_level(node->get_right())};
	node->set_level((left_level > right_level ? left_level : right_level) + 1);
}

template <class T>
Node<T>* AVLBinaryTree<T>::rotate_right(Node<T>* node) {
	Node<T>* left(node->get_left());
	node->set_left(left->get_right());
	left->set_right(node);

	fix_height(node);
	fix_height(left);

	return left;
}

template <class T>
Node<T>* AVLBinaryTree<T>::rotate_left(Node<T>* node) {
	Node<T>* right(node->get_right());
	node->set_right(right->get_left());
	right->set_left(node);

	fix_height(node);
	fix_height(right);

	return right;
}

template <class T>
Node<T>* AVLBinaryTree<T>::balance(Node<T>* node) {
	fix_height(node);

	if (bfactor(node) == 2) {

		if (bfactor(node->get_right()) < 0) {
			node->set_right(rotate_right(node->get_right()));
		}

		return rotate_left(node);
	}

	if (bfactor(node) == -2) {

		if (bfactor(node->get_left()) > 0) {
			node->set_left(rotate_left(node->get_left()));
		}

		return rotate_right(node);
	}

	return node;
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
Node<T>* AVLBinaryTree<T>::insert(Node<T>* root, const T& value) {
	if (!root) {
		return new Node<T>(value);
	} else if (value < root->get_key()) {
		root->set_left(insert(root->get_left(), value));
	} else {
		root->set_right(insert(root->get_right(), value));
	}

	return balance(root);
}

template <class T>
void AVLBinaryTree<T>::insert(const T& value) {
	_root = insert(_root, value);
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
Node<T>* AVLBinaryTree<T>::find_min(Node<T>* node) {
	return node->get_left() ? find_min(node->get_left()) : node;
}

template <class T>
Node<T>* AVLBinaryTree<T>::remove_min(Node<T>* node) {
	if (!node->get_left()) {
		return node->get_right();
	}

	node->set_left(remove_min(node->get_left()));
	return balance(node);
}

template <class T>
Node<T>* AVLBinaryTree<T>::remove(Node<T>* root, const T& value) {
	if (!root) {
		return nullptr;
	}

	if (value < root->get_key()) {
		root->set_left(remove(root->get_left(), value));
	} else if (value > root->get_key()) {
		root->set_right(remove(root->get_right(), value));
	} else {
		Node<T>* left(root->get_left());
		Node<T>* right(root->get_right());

		delete root;

		if (!right) {
			return left;
		}

		Node<T>* min = find_min(right);
		min->set_right(remove_min(right));
		min->set_left(left);

		return balance(min);
	}

	return balance(root);
}

template <class T>
void AVLBinaryTree<T>::remove(const T& value) {
	_root = remove(_root, value);
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
const Node<T>* AVLBinaryTree<T>::search(const Node<T>* root, const T& value) const {
	while (root != nullptr) {

		if (root->get_key() == value) {
			return root;
		} else if (root->get_key() < value) {
			root = root->get_right();
		} else {
			root = root->get_left();
		}
	}

	return nullptr;
}

template <class T>
const Node<T>* AVLBinaryTree<T>::search(const T& value) const {
	return search(_root, value);
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
const size_t& AVLBinaryTree<T>::size(Node<T>* node) const {
	if (!node) {
		return 0;
	}

	return size(node->get_left()) + 1 + size(node->get_right());
}

template <class T>
const size_t& AVLBinaryTree<T>::size() const {
	return size(_root);
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
const size_t& AVLBinaryTree<T>::height(Node<T>* node) const {
	if (!node || (!node->get_left() && !node->get_right())) {
		return 0;
	}

	size_t leftDepth{height(node->get_left())};
	size_t rightDepth{height(node->get_right())};

	return leftDepth > rightDepth ?
	       leftDepth + 1 : rightDepth + 1;
}

template <class T>
const size_t& AVLBinaryTree<T>::height() const {
	return height(_root);
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
std::string AVLBinaryTree<T>::to_string(T value) {
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

template <class T>
void AVLBinaryTree<T>::print_branches(std::ostream& out,
                                      const std::deque<Node<T>*>& nodes_queue,
                                      size_t branch_len,
                                      size_t node_space_len,
                                      size_t start_len,
                                      size_t level_node_count) {
	typename std::deque<Node<T>*>::const_iterator iter = nodes_queue.begin();

	for (size_t i{}; i < level_node_count / 2; ++i) {
		out << fg_green
		    << ((i == 0) ? std::setw(static_cast<int>(start_len - 1)) : std::setw(static_cast<int>(node_space_len - 2)))
		    << "" << ((*iter++) ? "/" : " ");
		out << std::setw(static_cast<int>(2 * branch_len + 2)) << "" << ((*iter++) ? "\\" : " ") << fg_default;
	}

	out << std::endl;
}

template <class T>
void AVLBinaryTree<T>::print_nodes(std::ostream& out,
                                   const std::deque<Node<T>*>& nodes_queue,
                                   size_t branch_len,
                                   size_t node_space_len,
                                   size_t start_len,
                                   size_t level_node_count) {
	typename std::deque<Node<T>*>::const_iterator iter = nodes_queue.begin();

	for (size_t i{}; i < level_node_count; ++i, ++iter) {
		out << ((i == 0) ? std::setw(static_cast<int>(start_len)) : std::setw(static_cast<int>(node_space_len))) << ""
		    << ((*iter && (*iter)->get_left()) ? std::setfill('_') : std::setfill(' '));
		out << fg_yellow << std::setw(static_cast<int>(branch_len + 2))
		    << ((*iter) ? to_string((*iter)->get_key()) : "");
		out << ((*iter && (*iter)->get_right()) ? std::setfill('_') : std::setfill(' '))
		    << std::setw(static_cast<int>(branch_len)) << "" << std::setfill(' ') << fg_default;
	}

	out << std::endl;
}

template <class T>
void AVLBinaryTree<T>::print_leaves(std::ostream& out,
                                    const std::deque<Node<T>*>& nodes_queue,
                                    size_t indent_space,
                                    size_t level,
                                    size_t level_node_count) {
	typename std::deque<Node<T>*>::const_iterator iter = nodes_queue.begin();

	for (size_t i{}; i < level_node_count; ++i, ++iter) {
		out << fg_green
		    << ((i == 0) ? std::setw(static_cast<int>(indent_space + 2)) : std::setw(static_cast<int>(2 * level + 2)))
		    << ((*iter) ? to_string((*iter)->get_key()) : "") << fg_default;
	}

	out << std::endl;
}

template <class T>
void AVLBinaryTree<T>::print_pretty(std::ostream& out, Node<T>* root, size_t level, size_t indent_space) {
	size_t h{height(root) + 1};
	size_t level_node_count{1};

	// eq of the length of branch for each node of each level
	size_t branch_len{2 * (static_cast<size_t>(pow(2.0, h)) - 1) - (3 - level) * static_cast<size_t>(pow(2.0, h - 1))};
	// distance between left neighbor node's right arm and right neighbor node's left arm
	size_t node_space_len{2 + (level + 1) * static_cast<size_t>(pow(2.0, h))};
	// starting space to the first node to print of each level (for the left most node of each level only)
	size_t start_len{branch_len + (3 - level) + indent_space};

	std::deque<Node<T>*> nodes_queue;
	nodes_queue.push_back(root);

	for (size_t r{1}; r < h; r++) {
		print_branches(out, nodes_queue, branch_len, node_space_len, start_len, level_node_count);
		branch_len = branch_len / 2 - 1;
		node_space_len = node_space_len / 2 + 1;
		start_len = branch_len + (3 - level) + indent_space;
		print_nodes(out, nodes_queue, branch_len, node_space_len, start_len, level_node_count);

		for (size_t i{}; i < level_node_count; i++) {
			Node<T>* current_node = nodes_queue.front();
			nodes_queue.pop_front();

			if (current_node) {
				nodes_queue.push_back(current_node->get_left());
				nodes_queue.push_back(current_node->get_right());
			} else {
				nodes_queue.push_back(nullptr);
				nodes_queue.push_back(nullptr);
			}
		}

		level_node_count *= 2;
	}

	print_branches(out, nodes_queue, branch_len, node_space_len, start_len, level_node_count);
	print_leaves(out, nodes_queue, indent_space, level, level_node_count);
}

template <class T>
void AVLBinaryTree<T>::print(std::ostream& out) {
	print_pretty(out, _root, _level, _indent);
}

template <class T>
std::ostream& operator<<(std::ostream& out, AVLBinaryTree<T>& tree) {
	tree.print(out);
	return out;
}
//----------------------------------------------------------------------------------------------------------------------

#endif // AVLBINARYTREE_H_DEF
