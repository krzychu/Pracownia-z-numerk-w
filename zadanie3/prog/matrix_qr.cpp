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


const std::pair<Matrix, Matrix> Matrix::qr_householder() const{
  Matrix R = copy();
  Matrix Q = Matrix(m_size);
  Q.one();

  double u[m_size];

  for(int k = 0; k < m_size - 1; k++){
    // generate u vector
    double sum = 0;
    for(int j = k; j < m_size; j++){
      u[j] = R.get(j,k);
      sum += u[j] * u[j]; 
    }
    double len = sqrt(sum);
    sum -= u[k] * u[k];
    u[k] -= len;
    sum += u[k] * u[k];
 
    if(sum == 0.0)
      continue;

    // get alpha constant
    double alpha = 2.0l / sum ;

    // transform R
    for(int column = k ; column < m_size; column++){
      // calculate scalar product of column and u
      double prod = 0;
      for(int row = k; row < m_size; row ++)
        prod += u[row] * R.get(row, column);
      // do subtractions
      for(int row = k; row < m_size; row++){
        int p = row * m_size + column;
        R.m_data[p] -= alpha * prod * u[row];
      }
    }

    // transform Q
    for(int column = 0 ; column < m_size; column++){
      // calculate scalar product of column and u
      double prod = 0;
      for(int row = k; row < m_size; row ++)
        prod += u[row] * Q.get(row, column);
      // do subtractions
      for(int row = k; row < m_size; row++){
        int p = row * m_size + column;
        Q.m_data[p] -= alpha * prod * u[row];
      }
    }

  }
  Q = Q.transpose();
  return std::make_pair(Q,R);
}
