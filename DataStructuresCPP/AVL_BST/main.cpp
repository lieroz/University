#include <iostream>
#include <ctime>
#include <cstring>

#include "AVLBinaryTree.h"

const size_t TEST_SIZE = 50;

void init_rand() {
	srand(static_cast<unsigned int>(time(nullptr)));
}

int get_random_int() {
	return rand() % 1000;
}

double get_random_double() {
	return static_cast<double>(get_random_int()) / get_random_int();
}

std::string get_random_string() {
	char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::string str;
	size_t STR_LEN = static_cast<size_t>(rand() % 8 + 1);

	for (size_t i{}; i < STR_LEN; i++) {
		str.push_back(alphanum[rand() % strlen(alphanum)]);
	}

	return str;
}

template <typename T, template <typename T> class TREE>
void UserInput() {
	TREE<T> tree;

	while (true) {

		std::cout << std::endl << fg_magenta << BOLD("---------------------------------------------") << std::endl
		          << std::endl;

		std::cout << fg_red << BOLD("Add node to tree { 1 }") << std::endl;
		std::cout << fg_yellow << BOLD("Remove node from tree { 2 }") << std::endl;
		std::cout << fg_blue << BOLD("Print tree { 3 }") << std::endl;
		std::cout << fg_cyan << BOLD("Exit { 0 }") << std::endl << std::endl;

		int choice = 0;
		std::cout << fg_green << BOLD("Enter your choice: ");
		std::cin >> choice;

		T value;

		switch (choice) {

			case 1: std::cout << BOLD("Enter value to add to tree: ") << fg_default;
				std::cin >> value;

				tree.insert(value);

				break;

			case 2: std::cout << BOLD("Enter value to remove from tree: ");
				std::cin >> value;

				tree.remove(value);

				break;

			case 3: std::cout << tree << std::endl;

				break;

			default: return;
		}
	}
}

int main(int argc, const char* argv[]) {
	init_rand();

	try {
		std::cout << fg_green <<BOLD("This is an example of tree:") << std::endl;

		AVLBinaryTree<std::string> AVL_BST;

		for (size_t i{}; i < TEST_SIZE; ++i) {
			AVL_BST.insert(get_random_string());
		}

		std::cout << AVL_BST << std::endl;

	} catch (...) {
		std::cerr << "ALERT!\n\tSOMETHING WENT WRONG! PLEASE CONTACT THE ADMINISTRATOR!" << std::endl;
	}

	try {

		char choice;
		std::cout << fg_green << BOLD("Do you want to test tree? {Y/N}: ");
		std::cin >> choice;

		if (choice == 'Y' || choice == 'y') {
			UserInput<int, AVLBinaryTree>();
		}

	} catch (...) {
		std::cerr << "ALERT!\n\tSOMETHING WENT WRONG! PLEASE CONTACT THE ADMINISTRATOR!" << std::endl;
	}

	return 0;
}
