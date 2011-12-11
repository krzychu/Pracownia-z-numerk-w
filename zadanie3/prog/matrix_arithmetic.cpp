#include <matrix.h>


const Matrix Matrix::operator+(const Matrix& other) const{
  return add(other);
}

const Matrix Matrix::operator-(const Matrix& other) const{
  return sub(other);
}

const Matrix Matrix::add(const Matrix& other) const{
  Matrix result(m_size);  
  for(int i = 0; i < m_size * m_size ; i++){
    result.m_data[i] = m_data[i] + other.m_data[i];
  }
  return result;
}


const Matrix Matrix::sub(const Matrix& other) const{
  Matrix result(m_size);  
  for(int i = 0; i < m_size * m_size ; i++){
    result.m_data[i] = m_data[i] - other.m_data[i];
  }
  return result;
}


