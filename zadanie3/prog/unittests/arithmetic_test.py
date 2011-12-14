from pymatrix import Matrix
import unittest

class ArithmeticTest(unittest.TestCase):
  a = Matrix([[1,2,3],[4,5,6],[7,8,9]])
  b = Matrix([[1,2,1],[4,3,1],[7,4,9]])

  plus = Matrix([[2,4,4],[8,8,7],[14,12,18]])
  minus = Matrix([[0,0,2],[0,2,5],[0,4,0]])
  mul = Matrix([[30,20,30],[66,47,63],[102,74,96]])

  def testSum(self):
    self.assertTrue(self.plus.isAlmostEqual(self.a + self.b))

  def testSub(self):
    self.assertTrue(self.minus.isAlmostEqual(self.a - self.b))

  def testMul(self):
    c = self.a * self.b
    self.assertTrue(self.mul.isAlmostEqual(c))



unittest.main()
