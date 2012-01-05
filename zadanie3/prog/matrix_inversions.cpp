#include <matrix.h>
#include <utility>

using std::pair;

const Matrix Matrix::invertLU() const{
  pair<Matrix, Matrix> lu_pair = lu();
  Matrix invL = lu_pair.first.invertLowerTriangular();
  Matrix invU = lu_pair.second.invertUpperTriangular();
  return invU * invL;
}

const Matrix Matrix::invertQRSimple() const{
  pair<Matrix, Matrix> qr = qr_simple();
  return qr.second.invertUpperTriangular() * qr.first.transpose();
}

const Matrix Matrix::invertQRHouseholder() const{
  pair<Matrix, Matrix> qr = qr_householder();
  return qr.second.invertUpperTriangular() * qr.first.transpose();
}
