#include <matrix.h>
#include <cmath>


inline double sq(double x){
  return x * x;
}

double Matrix::frobeniusNorm() const{
  double sum = 0;
  for(int i = 0; i < m_size*m_size; i++)
    sum += sq(m_data[i]);
  return sqrt(sum);
}

double Matrix::scaledFrobeniusNorm() const{
  double size = sq(m_size);
  return frobeniusNorm() / size;
}

double Matrix::firstNorm() const{
  double result = 0;
  for(int column = 0; column < m_size; column++){
    double sum = 0;
    for(int row = 0; row < m_size; row++){
      sum += fabs(m_data[row*m_size + column]);
    }
    result = fmax(result, sum);
  }
}

double Matrix::infNorm() const{
  double result = 0;
  for(int row = 0; row < m_size; row++){
    double sum = 0;
    for(int column = 0; column < m_size; column++){
      sum += fabs(m_data[row*m_size + column]);
    }
    result = fmax(result, sum);
  }
}



