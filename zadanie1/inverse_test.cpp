#include <iostream>
#include "matrix.h"
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;


#define RANGE_START 2
#define RANGE_END 512

template<class T>
pair< Matrix<T>, Matrix<T> > generate(int n){
  Matrix<T> result(n);
  
  // generation of b_k sequence
  Matrix<T> randoms(n/2);
  randoms.randomize(-1,1);
  T b[n+1];
  for(int i=1 ; i<= n/2 + 1 ; i++)
    b[i] = randoms.get(0,i-1);
  for(int i=n/2 + 1 ; i<=n ; i++)
    b[i] = b[n - i + 1];


  // generation of tridiagonal matrix
  for(int i=0 ; i<n; i++){
      result.set(i,i,b[i+1]);
      result.set(i,i+1, 1);
      result.set(i+1,i, 1);
  }

  // generation of inverse
  T r[n];
  r[0] = 1;
  r[1] = -b[1];
  for(int i=2 ; i<n ; i++)
    r[i] = -(b[i]*r[i-1] + r[i-2]);
  
  T R = b[n]*r[n-1] + r[n-2]; 
  

  Matrix<T> inverse(n);
  for(int j=1 ; j<=n  ;j++){
    for(int i=1 ; i<=j ; i++){
      T c = ((T)(r[i-1]*r[n-j])) / R;
      inverse.set(i-1,j-1,c);
      inverse.set(j-1,i-1,c);
    }
  }


  pair< Matrix<T>, Matrix<T> > ret = pair< Matrix<T>, Matrix<T> >(result, inverse);
  return ret;
}


template<class T>
void test(){
  cout << "# test dokładności, pierwsze 3 kolumny dla równania ^(X*(X^-1) - I)\n";
  cout << "# następne 3 kolumny dla równania ^((X^-1)*X - I)\n";
  cout << "# rozmiar delta_std delta_strassen delta_mutant  itd\n";
  for(int i = RANGE_START; i <= RANGE_END; i+=4){
    pair< Matrix<T>, Matrix<T> > ps = generate<T>(i);
    MatrixIdentity<T> id(i);
    Matrix<T> strassen_error1, std_error1, mutant_error1;
    Matrix<T> strassen_error2, std_error2, mutant_error2;
    
    strassen_error1 = fast_mul(ps.first, ps.second) - id;
    std_error1 = std_mul(ps.first, ps.second) - id;
    mutant_error1 = fast_mul(ps.first, ps.second, 128) - id;
   
    strassen_error2 = fast_mul(ps.second, ps.first) - id;
    std_error2 = std_mul(ps.second, ps.first) - id;
    mutant_error2 = fast_mul(ps.second, ps.first, 128) - id;
   
    cerr << i << "\n"; 
    cout << i << " ";
    
    cout << std_error1.delta() << " ";
    cout << strassen_error1.delta() << " ";
    cout << mutant_error1.delta() << " ";
    
    cout << std_error2.delta() << " ";
    cout << strassen_error2.delta() << " ";
    cout << mutant_error2.delta() << "\n";
  
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
