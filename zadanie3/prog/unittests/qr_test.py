import unittest
from pymatrix import Matrix

class TestGS(unittest.TestCase):
  
  def testRandom(self):
    m = Matrix(5)
    m.random(3)
    q, r = m.qr_simple()
    one = Matrix(5)
    one.one()
    self.assertTrue(m.isAlmostEqual(q*r))
    self.assertTrue(one.isAlmostEqual(q*q.transpose()))

  def testOne(self):
    one = Matrix(5)
    one.one()
    q, r = one.qr_simple()

unittest.main()
