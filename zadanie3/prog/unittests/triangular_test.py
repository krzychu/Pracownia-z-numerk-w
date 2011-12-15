from pymatrix import Matrix
import unittest

class TriangularTest(unittest.TestCase):
  
  def testUpperTriangularInversion(self):
    a = Matrix(15)
    a.randomUpperTriangular(87)
    b = a.invertUpperTriangular()
    c = Matrix(15)
    c.one()

    print (c - a * b).frobeniusNorm()

    self.assertTrue(c.isAlmostEqual(a * b))
    self.assertTrue(c.isAlmostEqual(b * a))


unittest.main()
