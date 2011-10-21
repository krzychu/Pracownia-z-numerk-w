#include <iostream>
#include "matrix.h"

template<class T>
Matrix<T> clement(int dim){
  Matrix<T> result(n);
  for(int i=1 ; i<n; i++){
    result.set(i, i-1, i);
  }
  return result;
}


int main(){
  st::cout << clement<double>(5);
  return 0;
}
