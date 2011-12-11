#include <matrix.h>
#include <cmath>

using boost::shared_array;

Matrix::Matrix(int size){
  m_size = size;
  m_data = shared_array<double>(new double[size*size]);
}

void Matrix::zero(){
  for(int i=0 ; i<m_size*m_size; i++){
    m_data[i] = 0;
  }
}

void Matrix::one(){
  zero();
  for(int i=0 ; i<m_size; i++){
    m_data[i + i*m_size] = 1;
  }
}

inline double sq(double x){
  return x * x;
}

double Matrix::frobeniusNorm() const{
  double sum = 0;
  for(int i = 0; i < m_size*m_size; i++)
    sum += sq(m_data[i]);
  return sum;
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

Matrix::~Matrix(){}
