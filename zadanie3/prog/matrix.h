#ifndef MATRIX_H_
#define MATRIX_H_

#include <boost/shared_array.hpp>
#include <iostream>

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

    // element manipulation
    inline void set(int row, int column, double value){
      m_data[row*m_size + column] = value;
    }

    inline double get(int row, int col) const{
      return m_data[row*m_size + col];
    }
    
    // norms
    double frobeniusNorm() const;
    double scaledFrobeniusNorm() const;
    double firstNorm() const;
    double infNorm() const;

    // entire array manipulation
    void zero();    // sets all elements to be 0
    void one();     // identity matrix
    void hilbert(); // hermite matrix


    virtual ~Matrix();

   
    // less typing
    typedef boost::shared_array<double> MatrixData;
    
    friend std::ostream& operator << (std::ostream& os, const Matrix& mat); 
  
  private:
    int m_size; 
    MatrixData m_data;
};


std::ostream& operator << (std::ostream& os, const Matrix& mat); 


#endif
