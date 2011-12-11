#include <matrix.h>

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


Matrix::~Matrix(){}
