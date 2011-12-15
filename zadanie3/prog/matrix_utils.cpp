#include <matrix.h>
#include <cmath>
#include <iomanip>

using boost::shared_array;

Matrix::Matrix(int size){
  m_size = size;
  m_data = shared_array<double>(new double[size*size]);
  zero();
}


Matrix::Matrix(const Matrix& other){
  m_size = other.m_size;
  m_data = other.m_data;
}


void Matrix::zero(){
  for(int i=0 ; i<m_size*m_size; i++){
    m_data[i] = 0;
  }
}

const Matrix Matrix::copy() const{
  Matrix result(m_size);
  for(int i=0; i < m_size * m_size; i++){
    result.m_data[i] = m_data[i];
  }  
  return result;
}

void Matrix::normalizeColumn(int col){
  double squareSum = 0; 
  for(int i=0; i<m_size; i++)
    squareSum += get(i, col) * get(i, col);

  double norm = sqrt(squareSum);

  for(int i=0; i<m_size ; i++){
    set(i, col, get(i, col) / norm); 
  }
}


void Matrix::one(){
  zero();
  for(int i=0 ; i<m_size; i++){
    m_data[i + i*m_size] = 1;
  }
}

void Matrix::hilbert(){
  for(int row = 0; row < m_size; row++){
    for(int column = 0; column < m_size; column++){
      m_data[row*m_size + column] = 
        1.0l / double(row + column + 1);
    } 
  }
}


const Matrix Matrix::transpose() const{
  Matrix result(m_size);
  for(int i = 0 ; i < m_size ; i++)
    for(int j = 0; j < m_size; j++)
      result.set(i,j, get(j,i));

  return result;
}


std::ostream& operator << (std::ostream& os, const Matrix& mat){
  os << "[\n";
  for(int row = 0; row < mat.m_size; row++){
    os << "    ";
    for(int col = 0; col < mat.m_size; col++){
      os << std::fixed << std::setw(5) << mat.m_data[row * mat.m_size + col] << " ";
    }
    os << ";\n";
  }
  os << "] \n";
  return os;
}


Matrix::~Matrix(){}
