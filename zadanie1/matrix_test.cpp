#include "matrix.h"
#include <cstdio>
#include <iostream>
#include <cstdio>
#include <ctime>


using namespace std;


void test_mul(int size){

	srand(time(0));

	Matrix<double> m1(size);
	Matrix<double> m2(size);
	m1.randomize(0,10);
	m2.randomize(0,10);
	cout << "#! /usr/bin/octave -q\n";	
	cout << "A = " << m1 << ";";
	cout << "B = " << m2 << ";";
	cout << "C_fast = " << fast_mul(m1,m2) << ";";
	cout << "C_std = " << std_mul(m1,m2) << ";";
	cout << "printf(\"fast error matrix\\n\");\n";
	cout << "A * B - C_fast\n";
	cout << "printf(\"slow error matrix\\n\");\n";
	cout << "A * B - C_std\n";
	
	cout << "printf(\"identity squared fast\\n\");\n";
	MatrixIdentity<double> id(size);
	cout << "D = " << fast_mul(id,id);
}


void test_memory(){
	Matrix<float> M(10);
	M.randomize(0,1);
	Matrix<float> C(10);
	C.randomize(0,1);
	Matrix<float> D;
	D =  fast_mul(M,C);
	cout << D;
}

int main(int argc, char** argv){
	#ifdef TEST_MEMORY
		printf("testing memory:");
		test_memory();
	#else
		test_mul(8);
	#endif
	return 0;
}
