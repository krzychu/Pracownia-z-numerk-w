#include <matrix.h>

using namespace MatLib;
using boost::shared_array;

MatLib::Matrix::Matrix(int size){
  m_size = size;
  m_data = shared_array<double>(new double[size*size]);
}

void MatLib::Matrix::zero(){
  for(int i=0 ; i<m_size*m_size; i++){
    m_data[i] = 0;
  }
}

void MatLib::Matrix::one(){
  zero();
  for(int i=0 ; i<m_size; i++){
    m_data[i + i*m_size] = 1;
  }
}

MatLib::Matrix::~Matrix(){}
