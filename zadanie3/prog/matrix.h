#ifndef MATRIX_H_
#define MATRIX_H_


class Matrix{
  public:
    // creates size X size matrix
    Matrix(int size);
    
    // copy constructor
    Matrix(const Matrix& other);
   
    // multiplication
    const Matrix operator * (const Matrix& other) const;
    const Matrix operator

    // destructor, does not free the memory
    virtual ~Matrix();
  
  private:
    int m_size; 
};


#endif
