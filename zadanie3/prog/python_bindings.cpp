#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <matrix.h>
#include <string>
#include <utility>
#include <cstdlib>
#include <benchmark.h>

using namespace boost::python;


class PyMatrix : public Matrix{
  public:

    // creates matrix from list of rows
    PyMatrix(const list& rows)
      : Matrix(len(rows))
    {
      int n = len(rows);
      for(int i=0; i<n; i++){
        list row = extract<list>(rows[i]);  
        for(int j=0; j<n; j++){
          double k = extract<double>(row[j]);
          set(i, j, k); 
        }
      }
    }

    PyMatrix(int size) : 
      Matrix(size)
    {}
    
    PyMatrix(const Matrix& m) :
      Matrix(m)
    {}

    const PyMatrix operator-(const Matrix& other) const{
      return PyMatrix(sub(other)); 
    }

    const PyMatrix operator+(const Matrix& other) const{
      return PyMatrix(add(other)); 
    }
    
    const PyMatrix operator*(const Matrix& other) const{
      return PyMatrix(mul(other)); 
    }

    // for testing purposes
    bool isAlmostEqual(const PyMatrix& other) const{
      Matrix diff = *this - other;
      return diff.frobeniusNorm() < 0.0001;
    }
    
    const PyMatrix invertUpperTriangular(){
      PyMatrix m(Matrix::invertUpperTriangular()); 
      return m;
    }

    const PyMatrix invertLowerTriangular(){
      PyMatrix m(Matrix::invertLowerTriangular()); 
      return m;
    }

    const PyMatrix transpose(){
      PyMatrix result(Matrix::transpose());
      return result;
    }
  
    const PyMatrix copy(){
      PyMatrix result(Matrix::copy());
      return result;
    }

    const PyMatrix invertLU(){
      PyMatrix result(Matrix::invertLU());
      return result;
    }
  
    const PyMatrix invertQRSimple(){
      PyMatrix result(Matrix::invertQRSimple());
      return result;
    }
    
    const PyMatrix invertQRHouseholder(){
      PyMatrix result(Matrix::invertQRHouseholder());
      return result;
    }

    const tuple invertLUTimed(){
      start_timer();
      PyMatrix m = invertLU();
      return make_tuple(m, stop_timer());
    }

    const tuple invertQRSimpleTimed(){
      start_timer();
      PyMatrix m = invertQRSimple();
      return make_tuple(m, stop_timer());
    }

    const tuple invertQRHouseholderTimed(){
      start_timer();
      PyMatrix m = invertQRHouseholder();
      return make_tuple(m, stop_timer());
    }

  
    double get(int row, int col){
      return Matrix::get(row, col);
    }

    void random(int seed);
    void randomUpperTriangular(int seed);
    void randomLowerTriangular(int seed);
    void randomDiagonalDominant(int seed);
    void randomAlmostSingular(int seed);
    void randomZeroMinor(int seed);
    void randomTridiagonal(int seed);


    tuple pythonLu() const;
    tuple pythonQRsimple() const;
    tuple pythonQRhouseholder() const;
};


double randnum(){
  return double(rand()) * 100.0 / double(RAND_MAX) - 50.0;
}

void PyMatrix::random(int seed){
  srand(seed);
  for(int i=0 ; i<m_size * m_size; i++){
    m_data[i] = randnum();
  }
}

void PyMatrix::randomUpperTriangular(int seed){
  random(seed);
  for(int i=0; i<m_size; i++)
    for(int j=0; j<i ; j++)
      set(i,j,0);
}

void PyMatrix::randomLowerTriangular(int seed){
  random(seed);
  for(int i=0; i<m_size; i++)
    for(int j=i+1; j < m_size; j++)
      set(i,j,0);
}

void PyMatrix::randomDiagonalDominant(int seed){
  random(seed);
  for(int row = 0; row < m_size; row++){
    double sum = 0;
    for(int col = 0; col < m_size; col++){
      if(col != row)
        sum += fabs(get(row, col));
    }
    set(row, row, sum + 1.0);
  }
}

void PyMatrix::randomAlmostSingular(int seed){
  random(seed);
  int a = rand() % m_size;
  int b = rand() % m_size;
  
  if(a == b)
    a = (a + 1) % m_size;

  for(int row = 0 ; row < m_size ; row++)
    set(row, a, get(row, b) * 2.0 + 0.001);
}

void PyMatrix::randomZeroMinor(int seed){
  random(seed);
  int half = m_size / 2;
  int a = rand() % half;
  int b = rand() % half;
  
  if(a == b)
    a = (a + 1) % half;

  for(int row = 0 ; row < half ; row++)
    set(row, a, get(row, b) * 2.0);
}

void PyMatrix::randomTridiagonal(int seed){
  srand(seed);
  for(int i = 0; i<m_size ; i++){
    set(i, i, randnum());
    if(i > 0)
      set(i, i-1, randnum());
    if(i < m_size - 1)
      set(i, i+1, randnum());
  }
}


tuple PyMatrix::pythonLu() const{
  std::pair<Matrix, Matrix> p = lu();
  PyMatrix l(p.first);
  PyMatrix u(p.second);
  return make_tuple(l,u);
}

tuple PyMatrix::pythonQRsimple() const{
  std::pair<Matrix, Matrix> p = QRSimple();
  PyMatrix l(p.first);
  PyMatrix u(p.second);
  return make_tuple(l,u);
}

tuple PyMatrix::pythonQRhouseholder() const{
  std::pair<Matrix, Matrix> p = QRHouseholder();
  PyMatrix l(p.first);
  PyMatrix u(p.second);
  return make_tuple(l,u);
}

BOOST_PYTHON_MODULE(pymatrix){
  class_<PyMatrix>("Matrix", init<int>())
    .def(init<PyMatrix>())
    .def(init<list>())
    .def(self_ns::str(self))
    
    // generators
    .def("zero", &Matrix::zero)
    .def("one", &Matrix::one)
    .def("hilbert", &Matrix::hilbert)
    
    // norms
    .def("frobeniusNorm", &Matrix::frobeniusNorm)
    .def("scaledFrobeniusNorm", &Matrix::scaledFrobeniusNorm)
    .def("firstNorm", &Matrix::firstNorm)
    .def("infNorm", &Matrix::infNorm)
  
    // utils
    .def("transpose", &PyMatrix::transpose)
    .def("normalizeColumn", &Matrix::normalizeColumn)
    .def("copy", &PyMatrix::copy)


    // inversions
    .def("invertLU", &PyMatrix::invertLU)
    .def("invertQRSimple", &PyMatrix::invertQRSimple)
    .def("invertQRHouseholder", &PyMatrix::invertQRHouseholder)

    // timed inversions
    .def("invertLUTimed", &PyMatrix::invertLUTimed)
    .def("invertQRSimpleTimed", &PyMatrix::invertQRSimpleTimed)
    .def("invertQRHouseholderTimed", &PyMatrix::invertQRHouseholderTimed)


    // decompositions
    .def("lu", &PyMatrix::pythonLu)
    .def("QRSimple", &PyMatrix::pythonQRsimple)
    .def("QRHouseholder", &PyMatrix::pythonQRhouseholder)

    // triangular inversions
    .def("invertUpperTriangular", &PyMatrix::invertUpperTriangular)
    .def("invertLowerTriangular", &PyMatrix::invertLowerTriangular)

    // for tests
    .def("isAlmostEqual", &PyMatrix::isAlmostEqual)
    .def("randomUpperTriangular", &PyMatrix::randomUpperTriangular)
    .def("randomLowerTriangular", &PyMatrix::randomLowerTriangular)
    .def("random", &PyMatrix::random)
    .def("randomDiagonalDominant", &PyMatrix::randomDiagonalDominant)
    .def("randomAlmostSingular", &PyMatrix::randomAlmostSingular)
    .def("randomZeroMinor", &PyMatrix::randomZeroMinor)
    .def("randomTridiagonal", &PyMatrix::randomTridiagonal)

    // element access
    .def("get", &PyMatrix::get)

    // arithmetic
    .def(self + self)
    .def(self - self)
    .def(self * self)
    ;
}
