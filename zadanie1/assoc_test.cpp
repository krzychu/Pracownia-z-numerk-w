#include <cstring>
#include <iostream>
#include "matrix.h"

#define RANGE_START 2
#define RANGE_END 512
#define THRESHOLD 128

using namespace std;

template<class T>
void test(){
  cout << "# test łączności dodawania\n";
  cout << "# rozmiar standard strassen mutant\n";

<<<<<<< HEAD
  for(int i= RANGE_START ; i<=RANGE_END; i+=2){
=======
  for(int i= RANGE_START ; i<=RANGE_END; i+=4){
    cerr << i << "\n";
>>>>>>> 2d8ff263d6985fdb8a0d47a57ef019788e59bbe2
    cout << i << " ";
    Matrix<T> a(i);
    Matrix<T> b(i);
    Matrix<T> c(i);
    a.randomize(-1,1);
    b.randomize(-1,1);
    c.randomize(-1,1);
    Matrix<T> diff_std = std_mul(std_mul(a,b),c) - std_mul(a,std_mul(b,c));
    Matrix<T> diff_fast = fast_mul(fast_mul(a,b),c) - fast_mul(a,fast_mul(b,c));
    Matrix<T> diff_mutant = fast_mul(fast_mul(a,b,THRESHOLD),c,THRESHOLD) - 
                fast_mul(a,fast_mul(b,c,THRESHOLD),THRESHOLD);
  
    cout << diff_std.delta() << " ";
    cout << diff_fast.delta() << " ";
    cout << diff_mutant.delta() << "\n";
  }
}

int main(int argc, char **argv){
 
  srand(time(0));
 
  if(argc != 2){
    cout << "podaj precyzję : double lub float\n";
    return -1;
  }

  if(0 == strcmp(argv[1], "double")){  
    cout << "# precyzja : double\n";
    test<double>();
  }
  else{
    cout << "# precyzja : float\n";
    test<float>();
  }

  return 0;
}
