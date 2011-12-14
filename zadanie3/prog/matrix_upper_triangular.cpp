#include <matrix.h>

bool Matrix::isUpperTriangular() const{
  for(int row = 0; row < m_size ; row++){
    for(int col = 0; col < row; col++){
      if(m_data[row*m_size + col] != 0){
        return false;
      }
    }
  }
  return true;
}

const Matrix Matrix::invertUpperTriangular() const{
  Matrix result(m_size);

  return result;
}
