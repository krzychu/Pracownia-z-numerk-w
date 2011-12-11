#include <iostream>
#include <matrix.h>


int main(){
  Matrix m(3);
  m.one();
  Matrix z(3);
  z.one();
  std::cout << m - z;
  return 0;
}
