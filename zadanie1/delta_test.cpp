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
T scan(FILE* f);

template<>
float scan<float>(FILE* f){
	float a;
	fscanf(f,"%f", &a);
	return a;
}

template<>
double scan<double>(FILE* f){
	double a;
	fscanf(f,"%lf", &a);
	return a;
}



template<class T>
Matrix<T> load_matrix(const char* file){
	FILE *f = fopen(file, "r");
	int size;
	fscanf(f, "%d %d", &size, &size);
	
	Matrix<T> a(size);
	for(int i=0 ; i<size ; i++){
		for(int j=0 ; j<size ; j++){
			a.set(i,j,scan<T>(f));
		}
	}

	fclose(f);
	return a;
}


template<class T>
T delta_test(const char* mat_file, const char* inv_file, int threshold){
	Matrix<T> A = load_matrix<T>(mat_file);
	Matrix<T> A_inv = load_matrix<T>(inv_file);
	Matrix<T> res(A.getSize());
	MatrixIdentity<T> I(A.getSize());
	if(method == STRASSEN)
		res = fast_mul(A, A_inv, threshold) - I;
	else
		res = std_mul(A, A_inv) - I;
	
	return res.delta();
}


int main(int argc, char** argv){
	if(argc != 6){
		printf("memory_test.run precision method threshold matrix_file inverse_file\n");
		return -1;
	}
	
	char* str_prec = argv[1];
	char* str_method = argv[2];
	char* str_threshold = argv[3];
	char* str_matrix_name = argv[4];
	char* str_inverse_name = argv[5];

	int method;
	if(strcmp("strassen",str_method) == 0){
		method = STRASSEN;
	}
	else{
		method = NORMAL;
	}

	load_matrix<double>(str_matrix_name);

	return 0;
}
