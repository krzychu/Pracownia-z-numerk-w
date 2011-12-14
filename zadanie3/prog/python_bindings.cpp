#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <matrix.h>
#include <string>
#include <utility>
#include <cstdlib>

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
    
    void random(int seed);
    void randomUpperTriangular(int seed);
    void randomLowerTriangular(int seed);

    tuple pythonLu() const;
};


void PyMatrix::random(int seed){
  srand(seed);
  for(int i=0 ; i<m_size * m_size; i++){
    m_data[i] = double(rand()) * 100.0 / double(RAND_MAX) - 50.0;
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

tuple PyMatrix::pythonLu() const{
  std::pair<Matrix, Matrix> p = lu();
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
   
    // decompositions
    .def("lu", &PyMatrix::pythonLu)

    // triangular inversions

    // for tests
    .def("isAlmostEqual", &PyMatrix::isAlmostEqual)
    .def("randomUpperTriangular", &PyMatrix::randomUpperTriangular)
    .def("randomLowerTriangular", &PyMatrix::randomLowerTriangular)
    .def("random", &PyMatrix::random)

    // arithmetic
    .def(self + self)
    .def(self - self)
    .def(self * self)
    ;
}
