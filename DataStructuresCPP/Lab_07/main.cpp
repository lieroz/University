#include <iostream>
#include <fstream>
#include <random>
#include <stdexcept>

#include "Timer.h"

#include "AVLTree.h"
#include "NaiveTree.h"

#include "HashFunc.h"

#include "OpenHash.h"
#include "ClosedHash.h"

int GenerateRandomInteger(const int& begin_x, const int& end_x) {
	std::random_device random_dev;
	std::mt19937 probability(random_dev());
	std::uniform_int_distribution<> range(begin_x, end_x);
	return range(probability);
}

void GenerateRandomFile(const std::string& file_name) {
	std::ofstream random_numbers(file_name);

	std::cout << BOLD GREEN << "Enter amount of numbers to generate: " << RST;
	size_t numbers_count{};
	std::cin >> numbers_count;

	std::cout << BOLD GREEN << "Enter diapason of generated numbers {-2^31...2^31}: " << RST;
	int begin_x, end_x;
	std::cin >> begin_x >> end_x;

	if (begin_x > end_x) {
		throw std::invalid_argument("ERROR: WRONG INPUT!");
	}

	if (random_numbers.is_open()) {

		for (size_t i{}; i < numbers_count; ++i) {
			random_numbers << GenerateRandomInteger(begin_x, end_x) << std::endl;
		}

		random_numbers.close();
	}
}

int main(const int argc, const char* argv[]) {

	if (argc != 2) {
		throw std::invalid_argument("ERROR: NO INPUT FILE!");
	}

	std::string file_name{argv[1]};

	try {
		GenerateRandomFile(file_name);
	} catch (...) {
		std::cerr << "ERROR! SOMETHING WENT WRONG, PLEASE CONTACT THE ADMINISTRATOR!" << std::endl;
	}

	AVLTree<int> avl_tree;
	NaiveTree<int> naive_tree;
	ClosedHash<int, HashFunc<int>> closed_hash;
	OpenHash<int, HashFunc<int>> open_hash;

	std::ifstream random_numbers(file_name);

	std::cout << BOLD GREEN << "Enter the number to search: " << RST;
	int number{};
	bool number_exists = false;
	std::cin >> number;

	if (random_numbers.is_open()) {
		int buffer{};

		while (random_numbers >> buffer) {

			if (buffer == number) {
				number_exists = true;
			}

			avl_tree.insert(buffer);
			naive_tree.insert(buffer);
			closed_hash.insert(buffer);
			open_hash.insert(buffer);
		}

		random_numbers.close();
	}

	std::cout << BOLD GREEN << "Do you want to print all data structures? {1/0}: " << RST;
	int choice{};
	std::cin >> choice;

	if (choice == 1) {
		std::cout << avl_tree << std::endl;
		std::cout << naive_tree << std::endl;
		std::cout << closed_hash << std::endl;
		std::cout << open_hash << std::endl;
	}

	if (!number_exists) {
		std::cout << BOLD RED << "NUMBER NOT FOUND!" << std::endl;
	} else {
		Timer timer;

		timer.start();
		avl_tree.search(number);
		timer.stop();

		std::cout << std::endl << BOLD GREEN << "Amount of comparisons in AVL Binary Tree: "
		          << BOLD BLUE << avl_tree.get_cmp_count() << RST << std::endl;
		std::cout << BOLD GREEN << "Amount of memory allocated for AVL Binary Tree data structure: "
		          << BOLD BLUE << avl_tree.get_memory_amount() << " (bytes)" << RST << std::endl;
		std::cout << BOLD GREEN << "Amount of time taken to find element in AVL Binary Tree: "
		          << BOLD BLUE << timer.get_elapsed_time_in_microseconds() << " (ms)" << RST << std::endl << std::endl;

		timer.start();
		naive_tree.search(number);
		timer.stop();

		std::cout << BOLD GREEN << "Amount of comparisons in Naive Binary Tree: "
		          << BOLD BLUE << naive_tree.get_cmp_count() << RST << std::endl;
		std::cout << BOLD GREEN << "Amount of memory allocated for Naive Binary Tree data structure: "
		          << BOLD BLUE << naive_tree.get_memory_amount() << " (bytes);" << RST << std::endl;
		std::cout << BOLD GREEN << "Amount of time taken to find element in Naive Binary Tree: "
		          << BOLD BLUE << timer.get_elapsed_time_in_microseconds() << " (ms)" << RST << std::endl << std::endl;

		timer.start();
		closed_hash.search(number);
		timer.stop();

		std::cout << BOLD GREEN << "Amount of comparisons in Closed Addressing Hash Table: "
		          << BOLD BLUE << closed_hash.get_cmp_count() << RST << std::endl;
		std::cout << BOLD GREEN << "Amount of memory allocated for Closed Hash Table data structure: "
		          << BOLD BLUE << closed_hash.get_memory_amount() << " (bytes)" << RST << std::endl;
		std::cout << BOLD GREEN << "Amount of time taken to find element in Closed Hash Table: "
		          << BOLD BLUE << timer.get_elapsed_time_in_microseconds() << " (ms)" << RST << std::endl << std::endl;

		timer.start();
		open_hash.search(number);
		timer.stop();

		std::cout << BOLD GREEN << "Amount of comparisons in Open Addressing Hash Table: "
		          << BOLD BLUE << open_hash.get_cmp_count() << RST << std::endl;
		std::cout << BOLD GREEN << "Amount of memory allocated for Open Hash Table data structure: "
		          << BOLD BLUE << open_hash.get_memory_amount() << " (bytes)" << RST << std::endl;
		std::cout << BOLD GREEN << "Amount of time taken to find element in Open Hash Table: "
		          << BOLD BLUE << timer.get_elapsed_time_in_microseconds() << " (ms)" << RST << std::endl << std::endl;
	}

	return 0;
}