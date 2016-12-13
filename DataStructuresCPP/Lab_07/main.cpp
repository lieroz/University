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

//	AVLTree<int> avl_tree;
//	NaiveTree<int> naive_tree;
//
//	for (size_t i{}; i < 30; ++i) {
//		avl_tree.insert(GenerateRandomInteger());
//		naive_tree.insert(GenerateRandomInteger());
//	}
//
//	std::cout << BOLD << MAGENTA << avl_tree << RST << std::endl;
//	std::cout << BOLD << CYAN << naive_tree << RST << std::endl;

	ClosedHash<int, HashFunc<int>> closed_hash;

	for (size_t i{}; i < 1000; ++i) {
		closed_hash.insert(GenerateRandomInteger());
	}

	std::cout << closed_hash << std::endl;

	closed_hash.remove(1);

	std::cout << closed_hash << std::endl;

	int result = closed_hash.search(5);

	if (result != 0) {
		std::cout << result << std::endl;
	}

	return 0;
}