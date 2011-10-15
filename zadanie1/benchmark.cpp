#include <sys/time.h>
#include "benchmark.h"
#include <iostream>

static long start_time_val;

long get_usec(){
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec + tv.tv_sec*1000000;
}

void start_timer(){
  start_time_val = get_usec();
}

long stop_timer(){
  return get_usec() - start_time_val;
}

void print_timer(){
  std::cout << "time : " << stop_timer()  << "us\n";
}

