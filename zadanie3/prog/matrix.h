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
   
    // transposition
    const Matrix transpose() const;

    // norms
    double frobeniusNorm() const;
    double scaledFrobeniusNorm() const;
    double firstNorm() const;
    double infNorm() const;

    // entire array manipulation
    void zero();    // sets all elements to be 0
    void one();     // identity matrix
    void hilbert(); // hilbert matrix
  
    // lu decomposition
    const std::pair<Matrix, Matrix> lu() const;
    const std::pair<Matrix, Matrix> qr_simple() const;
    const std::pair<Matrix, Matrix> qr_householder() const;

    // inversions
    const Matrix invertLU() const;
    const Matrix invertQRSimple() const;
    const Matrix invertQRHouseholder() const;

    // triangular matrix operations
    const Matrix invertUpperTriangular() const;   
    const Matrix invertLowerTriangular() const;   


    // destructor, does nothing interesting
    virtual ~Matrix();
   
    // less typing
    const Matrix copy() const; 
    void normalizeColumn(int col);
    typedef boost::shared_array<double> MatrixData;
    friend std::ostream& operator << (std::ostream& os, const Matrix& mat); 
  
  protected:
    int m_size; 
    MatrixData m_data;
    
    // element manipulation
    inline double get(int row, int col) const{
      return m_data[row * m_size + col];
    }

   inline void set(int row, int col, double val){
      m_data[row * m_size + col] = val;
    }

};


std::ostream& operator << (std::ostream& os, const Matrix& mat); 


#endif
