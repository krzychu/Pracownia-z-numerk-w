#include <sys/time.h>
#include "benchmark.h"
#include <iostream>

static long start_time_val;

long get_usec(){
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec;
}

void start_time(){
	start_time_val = get_usec();
}

long stop_timer(){
	return get_usec() - start_time_val;
}

void print_timer(){
	std::cout << "time : " << stop_timer() / 1000;
}
