from pymatrix import Matrix
from time import time
from numpy import matrix as numpyMatrix
from numpy import linalg

def seed():
  return int(time())



def genMatrix(size, kind):
  m = Matrix(size)
  if kind == "random":
    m.random(seed())
  elif kind == "triangular":
    m.randomUpperTriangular(seed())
  else:
    return None
  return m



class AccuracyTest:
  matrixTypes = ["random", "triangular"]
  minsize = 10
  maxsize = 50


  def put(self, string):
    self.output.write(string + "\n")

  def putMany(self, array):
    for item in array:
      self.output.write(str(item) + " ")
    self.output.write("\n")

  def run(self):
    name = self.__class__.__name__
    print "running : ",  name
    
    for mtype in self.matrixTypes:
      print "matrix type : ", mtype
      output_name = name + "_" + mtype + ".dat"
      print "saving results to : ", output_name
      
      self.output = open(output_name, "w")
      self.put("# test : " + name);
      self.put("# matrix type : " + mtype)
      self.header()
     
      for size in range(self.minsize, self.maxsize + 1):
        m = genMatrix(size, mtype)
        self.test(m, size)
      
      self.output.close()

  def header(self):
    pass

  def test(self, matrix, size):
    pass



class QRAccuracyTest(AccuracyTest):
  def header(self):
    self.put("# A = frobenius_norm(Q * Q^T - I)")
    self.put("# B = frobenius_norm(A - Q*R)")
    self.put("# size A_simple B_simple A_householder B_householder")

  def test(self, m, size):
    one = Matrix(size)
    one.one()
    m.random(int(time()))

    q, r = m.QRSimple()
    a_simple = (q*q.transpose() - one).frobeniusNorm()
    b_simple = (m - q*r).frobeniusNorm()
    
    q, r = m.QRHouseholder()
    a_house = (q*q.transpose() - one).frobeniusNorm()
    b_house = (m - q*r).frobeniusNorm()
     
    self.putMany([size, a_simple, b_simple, a_house, b_house])



class INVAccuracyTest(AccuracyTest):
  def header(self):
    self.put("# E = frobenius_norm(A * inv(A) - I)")
    self.put("# size E_LU E_QRSimple E_QRHouseholder")

  def test(self, m, size):
    one = Matrix(size)
    one.one()

    e_lu = (m * m.invertLU() - one).frobeniusNorm()
    e_qr_simple = (m * m.invertQRSimple() - one).frobeniusNorm()
    e_qr_house = (m * m.invertQRHouseholder() - one).frobeniusNorm()

    self.putMany([size, e_lu, e_qr_simple, e_qr_house])


class INVComparisonTest(AccuracyTest):
  def header(self):
    self.put("# E = frobenius_norm(inv(A) - numpy_inv(A))")
    self.put("# size E_LU E_QRSimple E_QRHouseholder")

  def np_invert(self, matrix, size):
    temp = []
    for r in range(size):
      row = []
      for c in range(size):
        row.append(matrix.get(r,c))
      temp.append(row)
    
    np = numpyMatrix(temp)
    np = np.I

    temp = []
    for r in range(size):
      row = []
      for c in range(size):
        row.append(np[r,c])
      temp.append(row)
    
    return Matrix(temp)

  def test(self, m, size):
    np = self.np_invert(m, size)
    e_lu = (np - m.invertLU()).frobeniusNorm()
    e_qr_simple = (np - m.invertQRSimple()).frobeniusNorm()
    e_qr_house = (np - m.invertQRHouseholder()).frobeniusNorm()
    
    self.putMany([size, e_lu, e_qr_simple, e_qr_house])


qr = QRAccuracyTest()
qr.run()

inv = INVAccuracyTest()
inv.run()


comp = INVComparisonTest()
comp.run()
