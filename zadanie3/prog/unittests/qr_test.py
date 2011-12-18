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


class TestH(unittest.TestCase):
  size = 50

  def testRandom(self):
    m = Matrix(self.size)
    m.random(3)
    q, r = m.qr_householder()
    one = Matrix(self.size)
    one.one()
    self.assertTrue(m.isAlmostEqual(q*r))
    self.assertTrue(one.isAlmostEqual(q*q.transpose()))

   

unittest.main()
