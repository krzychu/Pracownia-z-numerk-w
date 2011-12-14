from pymatrix import Matrix
import unittest

class TriangularTest(unittest.TestCase):
  
  def testUpperTriangularInversion(self):
    a = Matrix(5)
    a.randomUpperTriangular()
    b = a.invertUpperTriangular()
    c = Matrix(5)
    c.one()
    self.assertTrue(c.isAlmostEqual(a * b))
    self.assertTrue(c.isAlmostEqual(b * a))


unittest.main()
