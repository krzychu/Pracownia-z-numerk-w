#include <matrix.h>
#include <cmath>

const std::pair<Matrix, Matrix> Matrix::qr_simple() const{
  Matrix Q = this->copy();
  Matrix R(m_size);

  // frist column - calculate length
  double len = 0;
  for(int i=0; i<m_size;  i++)
    len += get(i,0) * get(i,0);
  len = sqrt(len);
  R.set(0,0,len);
  
  // frist column - scale
  for(int i=0; i<m_size; i++)
    Q.m_data[i*m_size] /= len;


  // all other columns
  for(int col = 1; col < m_size; col++){
    for(int i = 0; i < col; i++){
      // calculate scalar product
      double prod = 0;
      for(int k=0; k<m_size; k++)
        prod += get(k, col) * Q.get(k, i);
      R.set(i, col, prod);
      
      // subtract
      for(int k = 0; k < m_size; k++)
        Q.m_data[k*m_size + col] -= prod * Q.m_data[k*m_size + i];
    }

    // normalize vector
    Q.normalizeColumn(col);

    double prod = 0;
    for(int k = 0 ;  k <m_size; k++)
      prod += get(k, col) * Q.get(k, col);

    R.set(col, col, prod);

  }
  
  return std::make_pair(Q,R);
}
