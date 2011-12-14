#include <boost/python.hpp>
#include <matrix.h>
#include <string>
#include <memory>

using namespace boost::python;
using std::auto_ptr;


class PyMatrix : public Matrix{
  public:
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
    
};



BOOST_PYTHON_MODULE(pymatrix){
  class_<PyMatrix>("Matrix", init<int>())
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
    ;
}
