#ifndef NODE_H_DEF
#define NODE_H_DEF

#include <iostream>

// Declaration of Node class for tree

template <class T>
class Node {
	private:
		T key{}; // Data contained in Node
		size_t level{1}; // Level on which Node is located

		Node* left{}; // Pointer to left child
		Node* right{}; // Pointer to right child

	public:
		// Constructors
		Node() = default;
		Node(T key) :
			key{key}, left{nullptr}, right{nullptr} {}

		// Prints Node into an output stream
		template <class U>
		friend std::ostream& operator<<(std::ostream&, const Node&);

		// Getters & setters
		// Sets key for Node
		void set_key(const T&);
		// Gets key from Node
		const T& get_key() const;

		// Sets level of Node
		void set_level(const size_t&);
		// Gets level of Node
		const size_t& get_level() const;

		// Sets left child of Node
		void set_left(Node*);
		// Gets left child of Node
		Node* get_left() const;

		// Sets right child of Node
		void set_right(Node*);
		// Gets right child of Node
		Node* get_right() const;
};

// Definition of Node class for tree

//----------------------------------------------------------------------------------------------------------------------
template <class T>
std::ostream& operator<<(std::ostream& output, const Node<T>& node) {
	return output << node.get_key();
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
void Node<T>::set_key(const T& data) {
	key = data;
}

template <class T>
const T& Node<T>::get_key() const {
	return key;
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
void Node<T>::set_level(const size_t& data) {
	level = data;
}

template <class T>
const size_t& Node<T>::get_level() const {
	return level;
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
void Node<T>::set_left(Node<T>* node) {
	left = node;
}

template <class T>
Node<T>* Node<T>::get_left() const {
	return left;
}

//----------------------------------------------------------------------------------------------------------------------
template <class T>
void Node<T>::set_right(Node<T>* node) {
	right = node;
}

template <class T>
Node<T>* Node<T>::get_right() const {
	return right;
}
//----------------------------------------------------------------------------------------------------------------------

#endif // NODE_H_DEF