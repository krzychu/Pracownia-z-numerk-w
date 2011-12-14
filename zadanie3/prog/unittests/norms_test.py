from pymatrix import Matrix
import unittest

class NormsTest(unittest.TestCase):
  matrix = Matrix([[1,2,3], [1,2,3], [1,2,3]])

  def testInfNorm(self):
    self.assertEqual(self.matrix.infNorm(), 6.0)

  def testFirstNorm(self):
    self.assertEqual(self.matrix.firstNorm(), 9.0)

  def testFrobeniusNorm(self):
    self.assertAlmostEqual(self.matrix.frobeniusNorm(), 6.4807407)

  def testScaledFrobeniusNorm(self):
    self.assertAlmostEqual(self.matrix.scaledFrobeniusNorm(),  0.7200823)

unittest.main()
