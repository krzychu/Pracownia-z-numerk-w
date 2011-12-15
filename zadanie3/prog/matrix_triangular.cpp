#include <matrix.h>


const Matrix Matrix::invertUpperTriangular() const{
  Matrix result(m_size);
  for(int i = 0; i < m_size; i++){
    result.set(i,i, 1.0l / get(i,i));
    for(int j = i+1; j < m_size; j++){
      double sum = 0;
      for(int k = i; k < j ; k++){
        sum += result.get(i,k) * get(k,j);
      }
      result.set(i,j, - sum / get(j,j));
    }
  }
  return result;
}



const Matrix Matrix::invertLowerTriangular() const{
  Matrix result(m_size);
  for(int j = 0; j < m_size; j++){
    result.set(j,j,1.0l / get(j,j));
    for(int i = j+1; i < m_size; i++){
      double sum = 0;
      for(int k = j; k < i ; k++)
        sum += get(i,k) * result.get(k,j);
      sum /= - get(i,i);
      result.set(i,j,sum);
    }
  }
  return result;
}
