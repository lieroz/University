#include <iostream>

#include "AVLTree.h"
#include "NaiveTree.h"

#include "OpenHash.h"
#include "ClosedHash.h"

int main() {

	AVLTree<int> avl_tree;
	NaiveTree<int> naive_tree;

	for (size_t i{}; i < 10; ++i) {
		avl_tree.insert(i);
		naive_tree.insert(i);
	}

	for (size_t i{}; i < 10; ++i) {
		avl_tree.remove(i);
		naive_tree.remove(i);
	}

	return 0;
}