#include "Timer.h"

Timer::Timer() {
#ifdef WIN32
	QueryPerfomanceFrequency(&frequency);
	start_count.QuadPart = 0;
	end_count.QuadPart = 0;
#else
	start_count.tv_sec = start_count.tv_usec = 0;
	end_count.tv_sec = end_count.tv_usec = 0;
#endif

	start_time_in_microsec = 0;
	end_time_in_microsec = 0;
	stopped = false;
}

void Timer::start() {
	stopped = false;

#ifdef WIN32
	QueryPerfomanceCounter(&start_count);
#else
	gettimeofday(&start_count, nullptr);
#endif
}

void Timer::stop() {
	stopped = true;

#ifdef WIN32
	QueryPerfomanceCounter(&end_count);
#else
	gettimeofday(&end_count, nullptr);
#endif
}

double Timer::get_elapsed_time_in_microseconds() {
#ifdef WIN32
	if (!stopped){
		QueryPerfomanceCounter(&end_count);
	}

	start_time_in_microsec = start_count.QuadPart * (1000000.0 / frequency.QuadPart);
	end_time_in_microsec = end_count.QuadPart * (1000000.0 / frequency.QuadPart);
#else
	if (!stopped) {
		gettimeofday(&end_count, nullptr);
	}

	start_time_in_microsec = (start_count.tv_sec * 1000000.0) + start_count.tv_usec;
	end_time_in_microsec = (end_count.tv_sec * 1000000.0) + end_count.tv_usec;
#endif

	return end_time_in_microsec - start_time_in_microsec;
}

double Timer::get_elapsed_time_in_milliseconds() {
	return this->get_elapsed_time_in_microseconds() * 0.001;
}

double Timer::get_elapsed_time() {
	return this->get_elapsed_time_in_microseconds() * 0.000001;
}