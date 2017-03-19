#include <iostream>
#include <vector>
#include <chrono>

#include "vector.hpp"

class timer {
	private:
		typedef std::chrono::high_resolution_clock __clock;
		typedef std::chrono::duration<double, std::ratio<1, 1000000000>> _second;
		std::chrono::time_point<__clock> __beg;
	
	public:
		timer() : __beg{__clock::now()} { }
		
		void reset() {
			__beg = __clock::now();
		}
		
		double elapsed() const {
			return std::chrono::duration_cast<_second>(__clock::now() - __beg).count();
		}
};

int main() {
	ftl::vector<int> v1;
	
	for (int i{ }; i < 10; ++i) {
		v1.push_back(i);
		std::cout << v1[i] << " ";
	}
	
	std::cout << std::endl;
	ftl::vector<int> v2(10);
	
	for (auto& iter : v2) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	ftl::vector<int> v3(10, 5);
	
	for (auto& iter : v3) {
		std::cout << iter << " ";
	}
	
	ftl::vector<int> v11;
	v11 = v3;
	
	std::cout << std::endl;
	ftl::vector<int> v4({1, 2, 3, 4, 5, 5, 7, 8, 9, 10});
	
	for (auto& iter : v4) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	ftl::vector<int> v5(v2);
	
	for (auto& iter : v5) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	ftl::vector<int> v6(std::move(v1));
	
	for (auto& iter : v6) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	
	ftl::vector<int> v7 = {1, 2, 3, 4, 5, 5, 7, 8, 9, 10};
	
	for (auto& iter : v7) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	ftl::vector<int> v8 = v6;
	
	for (auto& iter : v8) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	
	v8.assign(5, 14);
	
	for (auto& iter : v8) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	
	for (size_t i{ }; i < v2.size(); ++i) {
		std::cout << v2.at(i) << " ";
	}
	
	std::cout << std::endl;
	
	for (size_t i{ }; i < v4.size(); ++i) {
		std::cout << v4.front() << " " << v4.back() << " : ";
	}
	
	std::cout << std::endl;
	
	std::cout << v8.size() << std::endl;
	
	v8.pop_back();
	
	std::cout << v8.size() << std::endl;
	
	for (auto& iter : v8) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	
	v2.swap(v3);
	
	for (auto& iter : v2) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	
	for (auto& iter : v3) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	std::swap(v2, v3);
	
	for (auto& iter : v2) {
		std::cout << iter << " ";
	}
	
	std::cout << std::endl;
	
	std::cout << v3;
	
	std::cout << std::endl;
	
	for (ftl::vector<int>::const_iterator iter = v3.begin(); iter != v3.end(); ++iter) {
		std::cout << *iter << " ";
	}
	
	std::cout << std::endl;
	
	for (ftl::vector<int>::const_iterator iter = v3.end() - 1; iter == v3.begin(); --iter) {
		std::cout << *iter << " ";
	}
	
	ftl::vector<int>::const_iterator f = v2.begin();
	ftl::vector<int>::const_iterator l = v2.end();
	
	ftl::vector<int> test_iter(f, l);
	
	std::cout << test_iter << std::endl;
	
	test_iter.insert(test_iter.size(), 46);
	std::cout << test_iter << std::endl;
	
	test_iter.erase(test_iter.size() - 1);
	std::cout << test_iter << std::endl;
	
	std::cout << (v3 == v3) << std::endl;
	
//	ftl::vector<int> ftl_vector;
//	std::vector<int> std_vector;
//	timer tmr;
//	double elapsed_time = 0;
//
//	tmr.reset();
//
//	for (int i{ }; i < 100000000; ++i) {
//		ftl_vector.push_back(i);
//	}
//
//	elapsed_time = tmr.elapsed();
//	std::cout << elapsed_time << std::endl;
//
//	tmr.reset();
//
//	for (int i{ }; i < 100000000; ++i) {
//		std_vector.push_back(i);
//	}
//
//	elapsed_time = tmr.elapsed();
//	std::cout << elapsed_time;
	
	return 0;
}