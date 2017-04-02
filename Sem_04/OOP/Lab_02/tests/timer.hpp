//
// Created by lieroz on 29.03.17.
//

#ifndef LAB_02_TIMER_HPP
#define LAB_02_TIMER_HPP

#include <chrono>

class timer {
		typedef std::chrono::high_resolution_clock __clock;
		typedef std::chrono::duration<double, std::ratio<1, 1000000000>> _second;
		
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
		std::chrono::time_point<__clock> __beg;
};

#endif //LAB_02_TIMER_HPP
