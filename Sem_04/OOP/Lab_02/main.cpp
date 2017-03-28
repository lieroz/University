#include <iostream>
#include <vector>
#include <chrono>

#include "vector.hpp"

class timer {
	public:
		timer() : __beg(__clock::now()) {
			
		}
		
		void reset() {
			__beg = __clock::now();
		}
		
		double elapsed() const {
			return std::chrono::duration_cast<_second>(__clock::now() - __beg).count();
		}
	
	private:
		typedef std::chrono::high_resolution_clock __clock;
		typedef std::chrono::duration<double, std::ratio<1, 1000000000>> _second;
		std::chrono::time_point<__clock> __beg;
};

int main() {
	timer tmr;
	double elapsed_time = 0;
	
	std::cout << "Testing push_back and std::ostream..." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	
	ftl::vector<int> v1;
	tmr.reset();
	
	for (int i = 0; i < 35; ++i) {
		v1.push_back(i);
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
	
	for (ftl::vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter) {
		std::cout << *iter << " ";
	}
	
	elapsed_time = tmr.elapsed();
	std::cout << std::endl << "forward iterator time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "forward const_iterator: ";
	tmr.reset();
	
	for (ftl::vector<int>::const_iterator iter = v1.begin(); iter != v1.end(); ++iter) {
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
	
	for (ftl::vector<int>::iterator iter = v1.end() - 1; iter != v1.begin() - 1; --iter) {
		std::cout << *iter << " ";
	}
	
	elapsed_time = tmr.elapsed();
	std::cout << std::endl << "reversed iterator time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "reversed const_iterator: ";
	tmr.reset();
	
	for (ftl::vector<int>::const_iterator iter = v1.end() - 1; iter != v1.begin() - 1; --iter) {
		std::cout << *iter << " ";
	}
	
	elapsed_time = tmr.elapsed();
	std::cout << std::endl << "reversed const_iterator time: " << elapsed_time << " (ns)" << std::endl << std::endl;
	std::cout << "Testing constructors and assignment operators calling time..." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	
	tmr.reset();
	ftl::vector<int> v2;
	elapsed_time = tmr.elapsed();
	std::cout << "Default constructor call time: " << elapsed_time << " (ns)" << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v3(10);
	elapsed_time = tmr.elapsed();
	std::cout << "Overloaded constructor call time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "v3 vector: " << v3 << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v4(10, 666);
	elapsed_time = tmr.elapsed();
	std::cout << "Overloaded constructor with param call time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "v4 vector: " << v4 << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v5(ftl::vector<int>::const_iterator(v4.begin()), ftl::vector<int>::const_iterator(v4.end()));
	elapsed_time = tmr.elapsed();
	std::cout << "Overloaded with iterator constructor call time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "v5 vector: " << v5 << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v6({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
	elapsed_time = tmr.elapsed();
	std::cout << "Overloaded with initializer list constructor call time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "v6 vector: " << v6 << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v7 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	elapsed_time = tmr.elapsed();
	std::cout << "Overloaded with initializer list assignment operator call time: " << elapsed_time << " (ns)"
	          << std::endl;
	std::cout << "v7 vector: " << v7 << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v8(v6);
	elapsed_time = tmr.elapsed();
	std::cout << "Copy constructor call time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "v8 vector: " << v8 << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v9 = v6;
	elapsed_time = tmr.elapsed();
	std::cout << "Copy assignment operator call time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "v9 vector: " << v9 << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v10(std::move(v4));
	elapsed_time = tmr.elapsed();
	std::cout << "Move constructor call time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "v10 vector: " << v10 << std::endl;
	std::cout << "v4 after move: " << v4 << std::endl << std::endl;
	
	tmr.reset();
	ftl::vector<int> v11 = std::move(v5);
	elapsed_time = tmr.elapsed();
	std::cout << "Move assignment operator call time: " << elapsed_time << " (ns)" << std::endl;
	std::cout << "v11 vector: " << v11 << std::endl;
	std::cout << "v5 after move: " << v5 << std::endl << std::endl;
	
	std::cout << "Testing compare operators..." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	
	std::cout << "v10 == v11 ? " << (v10 == v11) << std::endl;
	std::cout << "v10 != v11 ? " << (v10 != v11) << std::endl;
	std::cout << "v10 <= v11 ? " << (v10 <= v11) << std::endl;
	std::cout << "v10 >= v11 ? " << (v10 >= v11) << std::endl;
	std::cout << "v10 < v11 ? " << (v10 < v11) << std::endl;
	std::cout << "v10 > v11 ? " << (v10 > v11) << std::endl << std::endl;
	
	std::cout << "Testing assign functions..." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	
	ftl::vector<std::string> v12(12, "yay");
	std::cout << "Before assign function: " << v12 << std::endl;
	v12.assign(7, "nay");
	std::cout << "After assign function: " << v12 << std::endl << std::endl;
	
	std::cout << "Testing access operators and functions..." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	ftl::vector<int> v13 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	std::cout << "v13[0]: " << v13[0] << "   " << "v13.front(): " << v13.front() << std::endl;
	std::cout << "v13[4]: " << v13[4] << std::endl;
	std::cout << "v13[9]: " << v13[9] << "   " << "v13.back(): " << v13.back() << std::endl;
	std::cout << "v13.at(0): " << v13.at(0) << "   " << "v13.front(): " << v13.front() << std::endl;
	std::cout << "v13.at(4): " << v13.at(4) << std::endl;
	std::cout << "v13.at(9): " << v13.at(9) << "   " << "v13.back(): " << v13.back() << std::endl << std::endl;
	
	std::cout << "Testing capacity and size functions..." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	
	std::cout << "Before shrinking and clear: " << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 max_size: " << v1.max_size() << std::endl;
	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 is empty ? " << v1.empty() << std::endl << std::endl;
	
	v1.shrink_to_fit();
	
	std::cout << "After shrinking: " << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 max_size: " << v1.max_size() << std::endl;
	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 is empty ? " << v1.empty() << std::endl << std::endl;
	
	v1.clear();
	
	std::cout << "After clearing and shrinking: " << std::endl;
	std::cout << "v1 size: " << v1.size() << std::endl;
	std::cout << "v1 max_size: " << v1.max_size() << std::endl;
	std::cout << "v1 capacity: " << v1.capacity() << std::endl;
	std::cout << "v1 is empty ? " << v1.empty() << std::endl << std::endl;
	
	std::cout << "Testing modify functions..." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	ftl::vector<int> v14;
	std::cout << "push_back:" << std::endl;
	
	for (int i = 0; i < 14; ++i) {
		v14.push_back(i);
		std::cout << v14 << std::endl;
	}
	
	std::cout << std::endl << "pop_back:" << std::endl;
	
	for (int i = 0; i < 14; ++i) {
		std::cout << v14 << std::endl;
		v14.pop_back();
	}
	
	std::cout << std::endl;
	std::cout << "Testing std::swap function..." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	ftl::vector<char> v15({'a', 'b', 'c', 'd', 'e', 'f'});
	ftl::vector<char> v16 = {'g', 'h', 'i', 'j', 'k', 'l'};
	
	std::cout << "Before swap: " << std::endl;
	std::cout << "v15 vector: " << v15 << std::endl;
	std::cout << "v16 vector: " << v16 << std::endl << std::endl;
	
	std::swap(v15, v16);
	
	std::cout << "After swap: " << std::endl;
	std::cout << "v15 vector: " << v15 << std::endl;
	std::cout << "v16 vector: " << v16 << std::endl;
	
	return 0;
}