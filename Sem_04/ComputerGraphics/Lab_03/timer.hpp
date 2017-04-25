#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
        typedef std::chrono::high_resolution_clock __clock;
        typedef std::chrono::duration<double, std::ratio<1, 1000000000>> _second;

    public:
        Timer() : __beg(__clock::now()) {

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

#endif // TIMER_HPP
