#include <iostream>
#include <random>

#include "AVLTree.h"
#include "NaiveTree.h"

#include "HashFunc.h"

#include "OpenHash.h"
#include "ClosedHash.h"

int GenerateRandomInteger() {
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_int_distribution<> dist(0, 1000);
	return dist(e2);
}

int main() {

	AVLTree<int> avl_tree;
	NaiveTree<int> naive_tree;
	ClosedHash<int, HashFunc<int>> closed_hash;
	OpenHash<int, HashFunc<int>> open_hash;

	for (size_t i{}; i < 1000; ++i) {
		int temp = GenerateRandomInteger();
		avl_tree.insert(temp);
		naive_tree.insert(temp);
		closed_hash.insert(temp);
		open_hash.insert(temp);
	}

//	std::cout << BOLD << MAGENTA << avl_tree << RST << std::endl;
//	std::cout << BOLD << CYAN << naive_tree << RST << std::endl;
	std::cout << closed_hash << std::endl;
	std::cout << open_hash << std::endl;

	return 0;
}