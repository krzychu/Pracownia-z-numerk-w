#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <matrix.h>
#include <string>

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
};



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
    
    
    // arithmetic
    .def(self + self)
    .def(self - self)
    .def(self * self)
    ;
}
