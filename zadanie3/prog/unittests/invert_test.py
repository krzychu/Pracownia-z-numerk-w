import unittest
from pymatrix import Matrix

class InvertLUTest(unittest.TestCase):
  size = 5

  def testUnit(self):
    one = Matrix(self.size)
    one.one()
    self.assertTrue(one.isAlmostEqual(one.invertLU()))


  def testRandom(self):
    l = Matrix(self.size) 
    u = Matrix(self.size)
    l.randomLowerTriangular(5)
    u.randomUpperTriangular(5)

    m = l * u
    one = Matrix(self.size)
    one.one()
    self.assertTrue(one.isAlmostEqual(m * m.invertLU()))


unittest.main()
