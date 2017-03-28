//
// Created by lieroz on 29.03.17.
//

#ifndef LAB_02_SET_TESTS_HPP
#define LAB_02_SET_TESTS_HPP

#include <iostream>

#include "timer.hpp"
#include "set.hpp"

namespace tests {
	
	void run_tests_for_set() {
		timer tmr;
		double elapsed_time = 0;
		
		std::cout << "Testing push_back and std::ostream..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		
		ftl::set<int> v1;
		tmr.reset();
		
		for (int i = 0; i < 35; ++i) {
			v1.add(i);
		}
		
		elapsed_time = tmr.elapsed();
		std::cout << "Appending elements time: " << elapsed_time << " (ns)" << std::endl;
		
		tmr.reset();
		std::cout << "v1 elements: " << v1 << std::endl;
		elapsed_time = tmr.elapsed();
		std::cout << "Printing elements time: " << elapsed_time << " (ns)" << std::endl << std::endl;
		
		std::cout << "Testing forward iterator and const_iterator and range-based for loop..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		std::cout << "forward iterator: ";
		tmr.reset();
		
		for (ftl::set<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter) {
			std::cout << *iter << " ";
		}
		
		elapsed_time = tmr.elapsed();
		std::cout << std::endl << "forward iterator time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "forward const_iterator: ";
		tmr.reset();
		
		for (ftl::set<int>::const_iterator iter = v1.begin(); iter != v1.end(); ++iter) {
			std::cout << *iter << " ";
		}
		
		elapsed_time = tmr.elapsed();
		std::cout << std::endl << "forward const_iterator time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "range-based for loop: ";
		tmr.reset();
		
		for (const auto& iter : v1) {
			std::cout << iter << " ";
		}
		
		elapsed_time = tmr.elapsed();
		std::cout << std::endl << "range-based for loop time: " << elapsed_time << " (ns)" << std::endl << std::endl;
		
		std::cout << "Testing reversed iterator and const_iterator..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		std::cout << "reversed iterator: ";
		tmr.reset();
		
		for (ftl::set<int>::iterator iter = v1.end() - 1; iter != v1.begin() - 1; --iter) {
			std::cout << *iter << " ";
		}
		
		elapsed_time = tmr.elapsed();
		std::cout << std::endl << "reversed iterator time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "reversed const_iterator: ";
		tmr.reset();
		
		for (ftl::set<int>::const_iterator iter = v1.end() - 1; iter != v1.begin() - 1; --iter) {
			std::cout << *iter << " ";
		}
		
		elapsed_time = tmr.elapsed();
		std::cout << std::endl << "reversed const_iterator time: " << elapsed_time << " (ns)" << std::endl << std::endl;
		std::cout << "Testing constructors and assignment operators calling time..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		
		tmr.reset();
		ftl::set<int> v2;
		elapsed_time = tmr.elapsed();
		std::cout << "Default constructor call time: " << elapsed_time << " (ns)" << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v3(10);
		elapsed_time = tmr.elapsed();
		std::cout << "Overloaded constructor call time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "v3 set: " << v3 << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v4(10, 666);
		elapsed_time = tmr.elapsed();
		std::cout << "Overloaded constructor with param call time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "v4 set: " << v4 << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v5(ftl::set<int>::const_iterator(v4.begin()), ftl::set<int>::const_iterator(v4.end()));
		elapsed_time = tmr.elapsed();
		std::cout << "Overloaded with iterator constructor call time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "v5 set: " << v5 << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v6({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
		elapsed_time = tmr.elapsed();
		std::cout << "Overloaded with initializer list constructor call time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "v6 set: " << v6 << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v7 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		elapsed_time = tmr.elapsed();
		std::cout << "Overloaded with initializer list assignment operator call time: " << elapsed_time << " (ns)"
		          << std::endl;
		std::cout << "v7 set: " << v7 << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v8(v6);
		elapsed_time = tmr.elapsed();
		std::cout << "Copy constructor call time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "v8 set: " << v8 << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v9 = v6;
		elapsed_time = tmr.elapsed();
		std::cout << "Copy assignment operator call time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "v9 set: " << v9 << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v10(std::move(v4));
		elapsed_time = tmr.elapsed();
		std::cout << "Move constructor call time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "v10 set: " << v10 << std::endl;
		std::cout << "v4 after move: " << v4 << std::endl << std::endl;
		
		tmr.reset();
		ftl::set<int> v11 = std::move(v5);
		elapsed_time = tmr.elapsed();
		std::cout << "Move assignment operator call time: " << elapsed_time << " (ns)" << std::endl;
		std::cout << "v11 set: " << v11 << std::endl;
		std::cout << "v5 after move: " << v5 << std::endl << std::endl;
		
		std::cout << "Testing compare operators..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		
		std::cout << "v10 == v11 ? " << (v10 == v11) << std::endl;
		std::cout << "v10 != v11 ? " << (v10 != v11) << std::endl;
		std::cout << "v10 <= v11 ? " << (v10 <= v11) << std::endl;
		std::cout << "v10 >= v11 ? " << (v10 >= v11) << std::endl;
		std::cout << "v10 < v11 ? " << (v10 < v11) << std::endl;
		std::cout << "v10 > v11 ? " << (v10 > v11) << std::endl << std::endl;
		
		std::cout << "Testing access operators and functions..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		ftl::set<int> v12 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		
		std::cout << "v12[0]: " << v12[0] << "   " << "v13.front(): " << v12.front() << std::endl;
		std::cout << "v12[4]: " << v12[4] << std::endl;
		std::cout << "v12[9]: " << v12[9] << "   " << "v13.back(): " << v12.back() << std::endl;
		std::cout << "v12.at(0): " << v12.at(0) << "   " << "v13.front(): " << v12.front() << std::endl;
		std::cout << "v12.at(4): " << v12.at(4) << std::endl;
		std::cout << "v12.at(9): " << v12.at(9) << "   " << "v13.back(): " << v12.back() << std::endl << std::endl;
		
		v1.clear();
		
		std::cout << "After clearing and shrinking: " << std::endl;
		std::cout << "v1 size: " << v1.size() << std::endl;
		std::cout << "v1 capacity: " << v1.capacity() << std::endl;
		std::cout << "v1 is empty ? " << v1.empty() << std::endl << std::endl;
		
		std::cout << "Testing modify functions..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		ftl::set<int> v13;
		std::cout << "add:" << std::endl;
		
		for (int i = 0; i < 14; ++i) {
			v13.add(i);
			std::cout << v13 << std::endl;
		}
		
		std::cout << std::endl << "remove:" << std::endl;
		
		for (int i = 0; i < 14; ++i) {
			std::cout << v13 << std::endl;
			v13.remove(i);
		}
		
		std::cout << std::endl;
		
		std::cout << std::endl;
		std::cout << "Testing std::swap function..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		ftl::set<char> v14({'a', 'b', 'c', 'd', 'e', 'f'});
		ftl::set<char> v15 = {'g', 'h', 'i', 'j', 'k', 'l'};
		
		std::cout << "Before swap: " << std::endl;
		std::cout << "v14 set: " << v14 << std::endl;
		std::cout << "v15 set: " << v15 << std::endl << std::endl;
		
		std::swap(v14, v15);
		
		std::cout << "After swap: " << std::endl;
		std::cout << "v14 set: " << v14 << std::endl;
		std::cout << "v15 set: " << v15 << std::endl << std::endl;
		
		std::cout << "v14 contains 'i': " << v14.contains('i') << std::endl;
		std::cout << "v14 contains 'a': " << v14.contains('a') << std::endl;
		
		std::cout << std::endl;
		std::cout << "Testing set operations..." << std::endl;
		std::cout << "=======================================================================" << std::endl;
		std::cout << "Test union: " << std::endl;
		ftl::set<int> v16 = {1, 2, 3, 4, 5, 6, 7, 8};
		ftl::set<int> v17 = {9, 10, 11, 12, 13, 14, 15, 16};
		
		std::cout << v16 + v17 << std::endl;
		std::cout << ftl::Union(v16, v17) << std::endl << std::endl;
		
		std::cout << "Test subtraction: " << std::endl;
		ftl::set<int> v18 = {1, 2, 3, 4, 5, 6, 7, 8};
		ftl::set<int> v19 = {4, 5, 6, 7, 8, 9, 10, 11};
		
		std::cout << v18 - v19 << std::endl;
		std::cout << ftl::Subtraction(v18, v19) << std::endl << std::endl;
		
		std::cout << "Test intersection: " << std::endl;
		ftl::set<int> v20 = {1, 2, 3, 4, 5, 6, 7, 8};
		ftl::set<int> v21 = {4, 5, 6, 7, 8, 9, 10, 11};

		std::cout << (v20 ^ v21) << std::endl;
		std::cout << ftl::Intersection(v20, v21) << std::endl;
	}
}

#endif //LAB_02_SET_TESTS_HPP
