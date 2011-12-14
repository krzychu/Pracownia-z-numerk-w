import unittest
from pymatrix import Matrix


class TestLUDecomposition(unittest.TestCase):


  def testKnown(self):
    m = Matrix([[1,2,3,4], [1,4,9,16], [1,8,27,64], [1,16,81,256]])
    l = Matrix([[1,0,0,0], [1,1,0,0], [1,3,1,0], [1,7,6,1]])
    u = Matrix([[1,2,3,4], [0,2,6,12], [0,0,6,24], [0 ,0,0,24]])

    (x,y) = m.lu()
    self.assertTrue(x.isAlmostEqual(l))
    self.assertTrue(y.isAlmostEqual(u))
    self.assertTrue(m.isAlmostEqual(x*y))

  def testHilbert(self):
    m = Matrix(50)
    m.hilbert()
    (l,u) = m.lu()
    self.assertTrue(m.isAlmostEqual(l*u))

  def testRandom(self):
    l = Matrix(5)
    l.randomLowerTriangular(5)
    u = Matrix(5)
    u.randomUpperTriangular(5)
    m = l*u
    (x,y) = m.lu()
    self.assertTrue(m.isAlmostEqual(x*y))

unittest.main()
