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



class InvertQRSimpleTest(unittest.TestCase):
  size = 50

  def testUnit(self):
    one = Matrix(self.size)
    one.one()
    self.assertTrue(one.isAlmostEqual(one.invertQRSimple()))


  def testRandom(self):
    m = Matrix(self.size) 
    m.random(3);
    one = Matrix(self.size)
    one.one()
    self.assertTrue(one.isAlmostEqual(m * m.invertQRSimple()))


class InvertQRHouseholderTest(unittest.TestCase):
  size = 50

  def testUnit(self):
    one = Matrix(self.size)
    one.one()
    self.assertTrue(one.isAlmostEqual(one.invertQRHouseholder()))


  def testRandom(self):
    m = Matrix(self.size) 
    m.random(3);
    one = Matrix(self.size)
    one.one()
    self.assertTrue(one.isAlmostEqual(m * m.invertQRHouseholder()))


unittest.main()
