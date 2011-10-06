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


void test_submatrix(int s){
	Matrix<float> m(s);
	int h = 0;
	for(int i=0; i<s ; i++){
		for(int j=0; j<s ; j++){
			m.set(i,j,h);
			h++;
		}
	}
	m.extend();
	cout << m;
	cout << m.getA();
	cout << m.getB();
	cout << m.getC();
	cout << m.getD();
}

void test_identity_square(int s){
	MatrixIdentity<float> id(s);
	cout << id;
	cout << fast_mul(id,id);
}

void test_partition(){
	MatrixIdentity<float> id(3);
	cout << id;
	id.extend();
	cout << id;
	cout << "Duze A\n";
	cout << id.getA().getA();
	cout << id.getA().getB();
	cout << id.getA().getC();
	cout << id.getA().getD();
	
	cout << "Duze B\n";
	cout << id.getB().getA();
	cout << id.getB().getB();
	cout << id.getB().getC();
	cout << id.getB().getD();
	
	cout << "Duze C\n";
	cout << id.getC().getA();
	cout << id.getC().getB();
	cout << id.getC().getC();
	cout << id.getC().getD();
	
	cout << "Duze D\n";
	cout << id.getD().getA();
	cout << id.getD().getB();
	cout << id.getD().getC();
	cout << id.getD().getD();
	
}

int main(int argc, char** argv){
	test_mul(8);
	return 0;
}
