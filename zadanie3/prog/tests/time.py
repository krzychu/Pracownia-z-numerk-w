from pymatrix import Matrix
from time import time

minsize = 10
maxsize = 50

print "# time test"
print "# size LU QR-Gram QR-Householder"

for size in range(minsize, maxsize + 1):
  m = Matrix(size)
  m.random(int(time()))
  
  m, lu_time = m.invertLUTimed()
  m, qr_gram_time = m.invertQRSimpleTimed()
  m, qr_house_time = m.invertQRHouseholderTimed()
  print size, lu_time, qr_gram_time, qr_house_time
