#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdlib>



template <class T>
struct MatrixData{
	T* m_data;
	int m_nRefs;
	int m_size;

	MatrixData(int size){
		m_size = size;
		m_nRefs = 1;	
		m_data = new T[size*size];
		for(int i=0 ; i<size*size; i++)
			m_data[i] = 0;
	}

	void incRefs(){
		m_nRefs++;
	}

	void decRefs(){
		m_nRefs--;
		if(m_nRefs == 0){
			delete this;
		}
	}

	~MatrixData(){
		delete[] m_data;
	}
};


template <class T> class Matrix;

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

template <class Type>
Matrix<Type> fast_mul_internal(const Matrix<Type>& a, const Matrix<Type>& b){
	

	
	Matrix<Type> result(a.getSize());
	if(a.getSize() == 1){
		result.set(0,0,a.get(0,0) * b.get(0,0));
	}
	else{
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

			P1 = fast_mul_internal(A,G-H);	
			P2 = fast_mul_internal(A+B,H);
			P3 = fast_mul_internal(C+D,E);
			P4 = fast_mul_internal(D,F-E);
			P5 = fast_mul_internal(A+D,E+H);
			P6 = fast_mul_internal(B-D,F+H);
			P7 = fast_mul_internal(A-C,E+G);

			result.setR(P5 + P4 - P2 + P6);
			result.setS(P1 + P2);
			result.setT(P3 + P4);
			result.setU(P5 + P1 - P3 - P7);
	}
/*	std::cout << "A = " << a;
	std::cout << "B = " << b;
	std::cout << "A * B = " << result;*/
	return result;
}


template <class T>
Matrix<T> fast_mul(const Matrix<T>& a, const Matrix<T>& b){
	if(a.getSize() != b.getSize())
		throw "Matrix size mismatch";

	Matrix<T> a_big = a;
	a_big.extend();

	Matrix<T> b_big = b;
	b_big.extend();

	Matrix<T> result = fast_mul_internal<T>(a_big,b_big);
	result.cut(a.getSize());
	return result;
}


template <class T>
class Matrix{
	private:
		int m_size;
		int m_rowShift;
		int m_colShift;
		MatrixData<T>* m_data;

		// creates matrix 
		Matrix(MatrixData<T>* data, int rowShift, int colShift, int size){
			m_data = data;
			data->incRefs();
			m_size = size;
			m_rowShift = rowShift;
			m_colShift = colShift;
		}

		
	public:
		inline void set(int row, int col, T val) const{
			row += m_rowShift;
			col += m_colShift;
			if(row >= m_data->m_size || col >= m_data->m_size)
				return;
				
			m_data->m_data[row * m_data->m_size + col] = val;
		} 



		Matrix(){
			m_data = NULL;
			m_size = 0;
		}

		Matrix(int size){
			m_data = new MatrixData<T>(size);
			m_size = size;
			m_rowShift = 0;
			m_colShift = 0;
		}
	
		Matrix(const Matrix<T>& other){
			m_data = other.m_data;
			if(m_data)
				m_data->incRefs();

			m_rowShift = other.m_rowShift;
			m_colShift = other.m_colShift;
			m_size = other.m_size;
		}

		// returns element in row-th row and col-th column
		inline T get(int row, int col) const{
			row += m_rowShift;
			col += m_colShift;
			if(row >= m_data->m_size || col >= m_data->m_size)
				return 0;
				
			return m_data->m_data[row * m_data->m_size + col];
		} 


		// returns matrix size
		int getSize() const{
			return m_size;
		}

		// extends matrix to have size equal to some power of 2
		void extend(){
			m_size--;
			m_size |= m_size >> 1;
			m_size |= m_size >> 2;
			m_size |= m_size >> 4;
			m_size |= m_size >> 8;
			m_size |= m_size >> 16;
			m_size++;
		}

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

		Matrix<T> getA() const{
			int newsize = m_size/2;
			Matrix<T> result(m_data, m_rowShift, m_colShift, newsize);
			return result;
		}
		
		Matrix<T> getB() const{
			int newsize = m_size/2;
			Matrix<T> result(m_data, m_rowShift, m_colShift + newsize, newsize);
			return result;
		}
		
		Matrix<T> getC() const{
			int newsize = m_size/2;
			Matrix<T> result(m_data, m_rowShift + newsize, m_colShift, newsize);
			return result;
		}
		
		Matrix<T> getD() const{
			int newsize = m_size/2;
			Matrix<T> result(m_data, m_rowShift+newsize, 
				m_colShift + newsize, newsize);
			return result;
		}

		// additive operations
		Matrix<T> operator+(const Matrix<T>& other) const{
			Matrix m(m_size);
			for(int i=0 ; i<m_size; i++){
				for(int j=0 ; j<m_size; j++){
					m.set(i, j, get(i,j) + other.get(i,j));
				}
			}
			return m;
		}

		Matrix<T> operator-(const Matrix<T>& other) const{
			Matrix m(m_size);
			for(int i=0 ; i<m_size; i++){
				for(int j=0 ; j<m_size; j++){
					m.set(i, j, get(i,j) - other.get(i,j));
				}
			}
			return m;
		}


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

		void set(const Matrix<T> other){
			for(int i=0 ; i<m_size; i++){
				for(int j=0 ; j<m_size; j++){
					set(i, j, other.get(i,j));
				}
			}
		}

		virtual ~Matrix(){
			if(m_data)
				m_data->decRefs();
		}

		friend std::ostream& operator << <> (std::ostream& , const Matrix<T>& );
		friend Matrix<T> std_mul <> (const Matrix<T>& a, const Matrix<T>& b);
		friend Matrix<T> fast_mul_internal <> (const Matrix<T>& a, const Matrix<T>& b);
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
