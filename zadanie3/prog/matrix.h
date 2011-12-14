#ifndef MATRIX_H_
#define MATRIX_H_

#include <boost/shared_array.hpp>
#include <iostream>
#include <utility>

class Matrix{
  public:
    // creates size X size matrix
    Matrix(int size);
    
    // copy constructor
    Matrix(const Matrix& other);
   
    // standard arithmetic operators
    const Matrix sub(const Matrix& other) const;
    const Matrix add(const Matrix& other) const;
    const Matrix mul(const Matrix& other) const;
    
    // overloaded for convinience
    const Matrix operator * (const Matrix& other) const;
    const Matrix operator + (const Matrix& other) const;
    const Matrix operator - (const Matrix& other) const;
   
    // norms
    double frobeniusNorm() const;
    double scaledFrobeniusNorm() const;
    double firstNorm() const;
    double infNorm() const;

    // entire array manipulation
    void zero();    // sets all elements to be 0
    void one();     // identity matrix
    void hilbert(); // hilbert matrix
    
    // upper triangular matrix operations
    bool isUpperTriangular() const;
    const Matrix invertUpperTriangular() const;   

    // destructor, does nothing interesting
    virtual ~Matrix();
   
    // less typing
    typedef boost::shared_array<double> MatrixData;
   
    // output
    friend std::ostream& operator << (std::ostream& os, const Matrix& mat); 
  private:
    int m_size; 
    MatrixData m_data;
};


std::ostream& operator << (std::ostream& os, const Matrix& mat); 


#endif
