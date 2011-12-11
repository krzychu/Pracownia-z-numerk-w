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
