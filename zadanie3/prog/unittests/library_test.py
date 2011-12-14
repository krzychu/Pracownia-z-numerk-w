from pymatrix import Matrix
import unittest

class exportsAllMethods(unittest.TestCase):
  
  def testConstructors(self):
    a = Matrix(44)
  
  def testNorms(self):
    a = Matrix(44)
    a.frobeniusNorm()
    a.scaledFrobeniusNorm()
    a.firstNorm()
    a.infNorm()

  def testManipulators(self):
    a = Matrix(44)
    a.zero()
    a.one()
    a.hilbert()

  def testSpecial(self):
    s = str(Matrix(44))

  def testOperators(self):
    a = Matrix(44)
    b = Matrix(44)
    c = a + b
    c = a - b
    c = a * b

unittest.main()
