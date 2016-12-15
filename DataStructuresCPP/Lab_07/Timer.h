#ifndef TIMER_H_DEF
#define TIMER_H_DEF

#ifdef WIN32
#include <windows.h>
#else

#include <sys/time.h>

#endif

class Timer {
	private:
		double start_time_in_microsec;
		double end_time_in_microsec;
		bool stopped;

#ifdef WIN32
		LARGE_INTEGER frequency;
		LARGE_INTEGER startCount;
		LARGE_INTEGER endCount;
#else
		timeval start_count;
		timeval end_count;
#endif

	public:
		Timer();

		~Timer() {}

		void start();
		void stop();

		double get_elapsed_time();
		double get_elapsed_time_in_milliseconds();
		double get_elapsed_time_in_microseconds();
};

#endif // TIMER_H_DEF