#include "matrix.h"
#include "benchmark.h"
#include <iostream>


#define RANGE_START 2
#define RANGE_END 512
#define BEST_THRESHOLD 128

using namespace std;


int main(int argc, char** argv){
  
  // data file header
  cout << "#  size  standard  strassen  mutant\n";

  for(int size = RANGE_START; size <= RANGE_END; size+=4){
    Matrix<float> a(size);
    Matrix<float> b(size);
    a.randomize(-1,1);
    b.randomize(-1,1);
    
    cerr << size << "\n";
    cout << size << "  ";

    start_timer();
    Matrix<float> c = std_mul(a,b);
    cout << stop_timer() << "  ";
  
    start_timer();
    c = fast_mul(a,b,0);
    cout << stop_timer() << "  ";
  
    start_timer();
    c = fast_mul(a,b, BEST_THRESHOLD);
    cout << stop_timer() << "\n"; 
  }
  

  return 0;
}
