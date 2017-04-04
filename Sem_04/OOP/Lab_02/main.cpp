#include <set_tests.hpp>

int main() {
	try {
		tests::run_tests_for_set();
	
	} catch (bad_memory_allocation_exception& ex) {
		std::cout << "ALARM BRO! Memory troubles time: " << ex.what() << std::endl;
		
	} catch (out_of_range_exception& ex) {
		std::cout << "ALARM BRO! Out of range time: " << ex.what() << std::endl;
	}
	
	return 0;
}