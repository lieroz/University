#include <set_tests.hpp>
#include "vector_tests.hpp"

int main() {
	try {
		tests::run_tests_for_vector();
		tests::run_tests_for_set();
	
	} catch (std::exception& ex) {
		std::cout << "ALARM BRO! Exception time: " << ex.what() << std::endl;
	}
	
	return 0;
}