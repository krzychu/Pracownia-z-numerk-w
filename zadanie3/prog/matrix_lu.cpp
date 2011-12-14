#include <matrix.h>


const std::pair<Matrix, Matrix> Matrix::lu() const{
  Matrix l(m_size);
  Matrix u(m_size);

  for(int i=0 ; i < m_size ; i++){
    l.set(i,i,1.0);
    for(int j = i; j < m_size; j++){
      double sum = get(i,j);
      for(int k = 0; k < i ; k++){
        sum -= l.get(i,k)*u.get(k,j);
      }
      u.set(i,j,sum);
    }

    for(int j = i+1; j < m_size; j++){
      double sum = get(j,i);
      for(int k = 0; k < i; k++){
        sum -= l.get(j,k)*u.get(k,i);  
      }
      sum /= u.get(i,i);
      l.set(j,i,sum);
    }
  }

  return std::make_pair(l,u);
}
