#ifndef MATRIX_H_
#define MATRIX_H_

#include <boost/shared_array.hpp>


class Matrix{
  public:
    // creates size X size matrix
    Matrix(int size);
    
    // copy constructor
    Matrix(const Matrix& other);
   
    // standard arithmetic operators
    const Matrix operator * (const Matrix& other) const;
    const Matrix operator + (const Matrix& other) const;
    const Matrix operator - (const Matrix& other) const;

    // element manipulation
    void set(int row, int column, double value);
    double get(int row, int col) const;
    
    // norms
    double frobeniusNorm() const;
    double scaledFrobeniusNorm() const;
    double firstNorm() const;
    double infNorm() const;

    // entire array manipulation
    void zero();  // sets all elements to be 0
    void one();   // identity matrix

    virtual ~Matrix();
  
    // less typing
    typedef boost::shared_array<double> MatrixData;

  private:
    int m_size; 
    MatrixData m_data;
};




#endif
