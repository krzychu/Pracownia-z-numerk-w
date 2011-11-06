import matplotlib.pyplot as plot
import math

def p3(x):
  return x*x*x

def float_range(begin, end, n_points):
  step = float(end - begin) / float(n_points-1)
  return [begin + step*k for k in range(0,n_points)]


def spline(ys, first_x):
  n = len(ys) - 1
  
  # calculate divided diffrences
  ds = []
  for k in range(0,n-1):
    diff = 0.5*(ys[k] + ys[k+2]) - ys[k+1]
    ds.append(6.0 * diff)

  # solve equations for M
  c_prim = n * [None]
  d_prim = n * [None]
  
  c_prim[1] = 0.25
  for k in range(2,n):
    c_prim[k] = 1.0 / (4 - c_prim[k-1])

  d_prim[1] = 0.5 * ds[0]
  for k in range(2,n):
    d_prim[k] =  (2*ds[k-1] - d_prim[k-1])/ (4 - c_prim[k-1])
  
  M = (n+1)*[None]
  M[0] = 0
  M[n] = 0
  M[n-1] = d_prim[n-1]
  for k in range(n-2, 0, -1):
    M[k] = d_prim[k] - c_prim[k]*M[k+1]

  # spline function
  def f(x):
    k = 1 + int(x - first_x)
    if k <= 0:
      k = 1
    elif k > n:
      k = n

    A = 1.0 / 6.0 * M[k-1]
    B = 1.0 / 6.0 * M[k]
    C = ys[k-1] - 1.0 / 6.0 * M[k-1] 
    D = ys[k] - 1.0 / 6.0 * M[k]
    val = A*p3(xs[k] - x) + B*p3(x - xs[k-1]) + C*(xs[k] - x) + D*(x - xs[k-1])
    return val 

  # display knots
  xs = [first_x + k for k in range(0,len(ys))]
  plot.plot(xs,ys,"ro")
  
  # display spline
  spline_xs = float_range(first_x-1, first_x + n + 1, n*100)
  spline_ys = [f(x) for x in spline_xs]
  plot.plot(spline_xs,spline_ys,"b-")
  plot.show()

spline([1.0,20.0,4.0,-3.0,166.0],2.0)
