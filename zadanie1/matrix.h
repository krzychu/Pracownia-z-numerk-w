#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <algorithm>
#include <cstdlib>


/*
	This class holds actual matrix data, and keeps number of matrices
	referencing it. When no matrix needs its contents, MatrixData
	deletes itself.
*/
template <class T>
struct MatrixData{
	T* m_data;		// pointer to actual array of T
	int m_nRefs;	// number of matrices referencing data
	int m_size;		// dimension of matrix data

	/*
		creates MatrixData of spedified size, and fills it with 0's
		numer of references is set to 1
	*/
	MatrixData(int size){
		m_size = size;
		m_nRefs = 1;	
		m_data = new T[size*size];
		for(int i=0 ; i<size*size; i++)
			m_data[i] = 0;
	}

	/*
		increments number of matrices referencing this object
	*/
	void incRefs(){
		m_nRefs++;
	}


	/*
		decrements number of matrices referencing this object, and
		when it becomes 0, matrix data is deleted
	*/
	void decRefs(){
		m_nRefs--;
		if(m_nRefs == 0){
			delete this;
		}
	}

	/*
		frees allocated memory
	*/
	~MatrixData(){
		delete[] m_data;
	}
};


// forward declaration of matrix template
template <class T> class Matrix;


/*
	prints mat to os using matlab notation
*/
template<class T>
std::ostream& operator <<(std::ostream& os, const Matrix<T>& mat){
	os << "[ \n";
	for(int i=0 ; i<mat.m_size; i++){
		for(int j = 0; j < mat.m_size ; j++){
			os.width(10);
			os << mat.get(i,j) << ", ";
		}
		os << ";\n";
	}
	os << "]\n";
	return os;
}



/*
	O(n^3) straightforward matrix multiplication
*/
template<class T>
Matrix<T> std_mul (const Matrix<T>& a, const Matrix<T>& b){
	Matrix<T> m(a.getSize());
	for(int i=0 ; i<m.m_size; i++){
		for(int j = 0; j < m.m_size ; j++){
			T acc = 0;
			for(int k = 0; k < m.m_size ; k++){
				acc += a.get(i,k)*b.get(k,j);	
			}
			m.set(i,j,acc);
		}
	}
	return m;
}



/*
	Strassen matrix multiplication. We assume that a and b dimension is a power of 2
*/
template <class Type>
Matrix<Type> fast_mul_internal(
	const Matrix<Type>& a, 
	const Matrix<Type>& b, 
	int threshold)
{
	
	if(a.getSize() < threshold)
		return std_mul(a,b);

	Matrix<Type> result(a.getSize());
	if(a.getSize() == 1){
		result.set(0,0,a.get(0,0) * b.get(0,0));
		return result;
	}
	
	Matrix<Type> A,B,C,D,E,F,G,H;
	Matrix<Type> P1,P2,P3,P4,P5,P6,P7;
	A = a.getA();
	B = a.getB();
	C = a.getC();
	D = a.getD();

	E = b.getA();
	F = b.getC();
	G = b.getB();
	H = b.getD();

	P1 = fast_mul_internal(A,G-H, threshold);	
	P2 = fast_mul_internal(A+B,H, threshold);
	P3 = fast_mul_internal(C+D,E, threshold);
	P4 = fast_mul_internal(D,F-E, threshold);
	P5 = fast_mul_internal(A+D,E+H, threshold);
	P6 = fast_mul_internal(B-D,F+H, threshold);
	P7 = fast_mul_internal(A-C,E+G, threshold);

	result.setR(P5 + P4 - P2 + P6);
	result.setS(P1 + P2);
	result.setT(P3 + P4);
	result.setU(P5 + P1 - P3 - P7);
	
	return result;
}



/*
	Strassen multiplication, the only restriction is that sizes of a and b
	must be equal.
*/
template <class T>
Matrix<T> fast_mul(const Matrix<T>& a, const Matrix<T>& b, int threshold = 0){
	if(a.getSize() != b.getSize())
		throw "Matrix size mismatch";

	Matrix<T> a_big = a;
	a_big.extend();

	Matrix<T> b_big = b;
	b_big.extend();

	Matrix<T> result = fast_mul_internal<T>(a_big,b_big, threshold);
	result.cut(a.getSize());
	return result;
}



/*
	Matrix itself
*/
template <class T>
class Matrix{
	private:
		int m_size;					// matrix dimension
		int m_rowShift;				// if matrix is submatrix, it can be shifted
		int m_colShift;				
		MatrixData<T>* m_data;		// pointer to data(it is shared beetween matrices and their
									// submatrices)

		
		// constructor used for submatrix generation
		Matrix(MatrixData<T>* data, int rowShift, int colShift, int size){
			m_data = data;
			data->incRefs();		//another matrix depends on this data
			m_size = size;
			m_rowShift = rowShift;
			m_colShift = colShift;
		}

		
	public:
    
    enum{OP_ADD, OP_SUB, OP_COPY};

		// sets A_i,j to be val
		inline void set(int row, int col, T val) const{
			row += m_rowShift;
			col += m_colShift;
			if(row >= m_data->m_size || col >= m_data->m_size)
				return;
				
			m_data->m_data[row * m_data->m_size + col] = val;
		} 


		// creates empty matrix
		Matrix(){
			m_data = NULL;
			m_size = 0;
		}

		
		// creates 0 matrix of given dimension
		Matrix(int size){
			m_data = new MatrixData<T>(size);
			m_size = size;
			m_rowShift = 0;
			m_colShift = 0;
		}

		
		// copy constructor, necessary for correct handling of complicated
		// expressions
		Matrix(const Matrix<T>& other){
			m_data = other.m_data;
			if(m_data)
				m_data->incRefs();	

			m_rowShift = other.m_rowShift;
			m_colShift = other.m_colShift;
			m_size = other.m_size;
		}

		// returns A_row,col
		inline T get(int row, int col) const{
			row += m_rowShift;
			col += m_colShift;
			if(row >= m_data->m_size || col >= m_data->m_size)
				return 0;
				
			return m_data->m_data[row * m_data->m_size + col];
		} 

		
		/*
			returns sum of all elements squared
		*/
		T delta() const{
			T result = 0;
			T acc;
			for(int i=0; i<m_size; i++){
				for(int j=0 ; j<m_size; j++){
					acc = get(i,j);
					acc = acc * acc;
					result += acc;
				}
			}		
			return result;
		}


		// returns matrix size
		int getSize() const{
			return m_size;
		}


		/*
			extends matrix size to be smallest power of 2 greater or equal to
			current size. It doesn't change size of matrix data, just tells
			matrix to behave like it was completed with 0's where necessary 
		*/
		void extend(){
			m_size--;
			m_size |= m_size >> 1;
			m_size |= m_size >> 2;
			m_size |= m_size >> 4;
			m_size |= m_size >> 8;
			m_size |= m_size >> 16;
			m_size++;
		}


		// sets matrix size to given value
		void cut(int size){
			m_size = size;
		}
	

		// sets all matrix elements to be random from range [a,b]
		void randomize(T a, T b){
			T diff = b - a;
			for(int i=0; i<m_size; i++){
				for(int j=0 ; j<m_size; j++){
					set(i,j, a + diff * (T)((T) rand() / (T) RAND_MAX));
				}
			}		
		}

		/*
			Segment getters
			segments:
			A B
			C D

			R S
			T U

		*/
		
		void setR(const Matrix<T>& mat){
			getA().set(mat);	
		}

		void setS(const Matrix<T>& mat){
			getB().set(mat);	
		}

		void setT(const Matrix<T>& mat){
			getC().set(mat);	
		}

		void setU(const Matrix<T>& mat){
			getD().set(mat);	
		}

		inline Matrix<T> getA() const{
			int newsize = m_size/2;
			Matrix<T> result(m_data, m_rowShift, m_colShift, newsize);
			return result;
		}
		
		inline Matrix<T> getB() const{
			int newsize = m_size/2;
			Matrix<T> result(m_data, m_rowShift, m_colShift + newsize, newsize);
			return result;
		}
		
		inline Matrix<T> getC() const{
			int newsize = m_size/2;
			Matrix<T> result(m_data, m_rowShift + newsize, m_colShift, newsize);
			return result;
		}
		
		inline Matrix<T> getD() const{
			int newsize = m_size/2;
			Matrix<T> result(m_data, m_rowShift+newsize, 
				m_colShift + newsize, newsize);
			return result;
		}

		
		// adds other to this matrix
		Matrix<T> operator+(const Matrix<T>& other) const{
			Matrix m(m_size);
		  m.set(*this);
      m.apply(OP_ADD, other);
      return m;
		}

		// subtracts one matrix from another
		Matrix<T> operator-(const Matrix<T>& other) const{
			Matrix m(m_size);
		  m.set(*this);
      m.apply(OP_SUB, other);
      return m;
		}

	
		// assignment operator, takes care of proper refernece counting
		void operator=(const Matrix<T>& other){
			m_size = other.m_size;
			m_rowShift = other.m_rowShift;
			m_colShift = other.m_colShift;
			
			MatrixData<T> *old = m_data;
			m_data = other.m_data;
			if(m_data)
				m_data->incRefs();

			if(old)
				old->decRefs();
		}

    // apply operation to two matrices
    void apply(int operation, const Matrix<T>& other){
    	const int data_size = m_data->m_size;
      T* index = m_data->m_data + m_colShift + m_rowShift * data_size;
      const int rows = std::min(data_size - m_rowShift, m_size);
      const int cols = std::min(data_size - m_colShift, m_size);
      const int other_data_size = other.m_data->m_size; 
      const int other_rows = std::min(
        other_data_size - other.m_rowShift, other.m_size);
      const int other_cols = std::min(
        other_data_size - other.m_colShift, other.m_size);
      const int copy_cols = std::min(cols, other_cols);
      const int copy_rows = std::min(rows, other_rows);	
      T* copy_index = other.m_data->m_data + other.m_colShift + 
                      other.m_rowShift * other_data_size;
      
      if(operation == OP_COPY){
        for(int i=0 ; i < copy_rows; i++){
          for(int j=0; j < copy_cols; j++){
            *index++ = *copy_index++;
          }
          index += data_size - copy_cols;
          copy_index += other_data_size - copy_cols;
        }
      }
      else if(operation == OP_ADD){
        for(int i=0 ; i < copy_rows; i++){
          for(int j=0; j < copy_cols; j++){
            *index++ += *copy_index++;
          }
          index += data_size - copy_cols;
          copy_index += other_data_size - copy_cols;
        }
      }
      else if(operation == OP_SUB){
        for(int i=0 ; i < copy_rows; i++){
          for(int j=0; j < copy_cols; j++){
            *index++ -= *copy_index++;
          }
          index += data_size - copy_cols;
          copy_index += other_data_size - copy_cols;
        }
      }

    } 



    // sets matrix content to be 0
		void set_zero(){
			const int data_size = m_data->m_size;
      T* base_index = m_data->m_data + m_colShift + m_rowShift * data_size;
      T* index = base_index;
      const int rows = std::min(data_size - m_rowShift, m_size);
      const int cols = std::min(data_size - m_colShift, m_size);

      // set all values to 0
      for(int i=0 ; i < rows; i++){
				for(int j=0; j < cols; j++){
					*index = 0;
				  index++;
        }
        index += data_size - cols;
			}
    } 


		// copies contents of other matrix to this one
		void set(const Matrix<T>& other){
      set_zero();
      apply(OP_COPY,other);
    }

		virtual ~Matrix(){
			if(m_data)
				m_data->decRefs();
		}

		friend std::ostream& operator << <> (std::ostream& , const Matrix<T>& );
		friend Matrix<T> std_mul <> (const Matrix<T>& a, const Matrix<T>& b);
		friend Matrix<T> fast_mul_internal <> (const Matrix<T>& a, 
						const Matrix<T>& b, int theshold);
};


template<class T>
class MatrixIdentity : public Matrix<T>{
	public:
		MatrixIdentity(int size) : Matrix<T>(size){
			for(int i=0 ; i<size ; i++){
				this->set(i, i, 1);	
			}	
		}
};


#endif
