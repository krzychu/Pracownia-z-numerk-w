#include "matrix.h"
#include "benchmark.h"
#include <iostream>


#define RANGE_START 16
#define RANGE_END 512
#define STEP 16

using namespace std;


int main(int argc, char** argv){
  
  // data file header
  cout << "#  threshold  128 256 512\n";

  int sizes[] = {128, 256, 512};

  for(int threshold=RANGE_START; threshold <= RANGE_END; threshold += STEP){
    cout << threshold << " ";
    for(int i=0 ; i<3 ; i++){
      int size = sizes[i]; 
      Matrix<float> a(size);
      Matrix<float> b(size);
      a.randomize(-1,1);
      b.randomize(-1,1); 
      
      start_timer();
      Matrix<float> c = fast_mul(a,b,threshold);
      cout << stop_timer() << "  ";
    }
    cout << "\n";
  }
  return 0;
}
