import unittest
from pymatrix import Matrix

class TranspositionTest(unittest.TestCase):
  
  def testTransposition(self):
    m = Matrix([[1,2],[3,4]])
    tr = Matrix([[1,3], [2,4]])
    self.assertTrue(tr.isAlmostEqual(m.transpose()))

  def testColumnNormalization(self):
    m = Matrix([[3,3],[4,4]]) 
    norm = Matrix([[0.6, 0.6],[0.8,0.8]])
    m.normalizeColumn(0)
    m.normalizeColumn(1)
    self.assertTrue(norm.isAlmostEqual(m))

  def testClone(self):
    m = Matrix(7)
    a = m.copy()
    self.assertTrue(m.isAlmostEqual(a))

unittest.main()
