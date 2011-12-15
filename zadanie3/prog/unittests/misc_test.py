import unittest
from pymatrix import Matrix

class TranspositionTest(unittest.TestCase):
  
  def testTransposition(self):
    m = Matrix([[1,2],[3,4]])
    tr = Matrix([[1,3], [2,4]])
    self.assertTrue(tr.isAlmostEqual(m.transpose()))


unittest.main()
