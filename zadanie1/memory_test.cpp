#include "matrix.h"
#include <cstdio>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>


using namespace std;

#define STRASSEN 1
#define NORMAL 2

template<class T>
void test_memory(int method, int size, int thr){
	Matrix<T> M(size);
	M.randomize(0,1);
	Matrix<T> C(size);
	C.randomize(0,1);
	Matrix<T> D;
	if(method == STRASSEN)
		D = fast_mul(M,C, thr);
	else
		D = std_mul(M,C);
}

int main(int argc, char** argv){
	if(argc != 5){
		printf("memory_test.run precision method threshold size\n");
		return -1;
	}
	
	char* str_prec = argv[1];
	char* str_method = argv[2];
	char* str_threshold = argv[3];
	char* str_size = argv[4];

	int method;
	if(strcmp("strassen",str_method) == 0){
		method = STRASSEN;
	}
	else{
		method = NORMAL;
	}
	
	if(strcmp("double", str_prec) == 0)
		test_memory<double>(method, atoi(str_size), atoi(str_threshold));	
	else	
		test_memory<float>(method, atoi(str_size), atoi(str_threshold));	

	return 0;
}
