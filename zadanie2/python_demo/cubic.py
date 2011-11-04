import matplotlib.pyplot as plot
import math


def float_range(begin, end, n_points):
  step = float(end - begin) / float(n_points-1)
  return [begin + step*k for k in range(0,n_points)]


def determine_interval(x, xs):
  k = 0
  while k < len(xs) and xs[k] <= x:
    k = k + 1
  return k

def p3(x):
  return x*x*x

def spline(points):
  n = len(points) - 1
  xs = [float(x) for (x,y) in points]
  ys = [float(y) for (x,y) in points]

  # calculate hs
  hs = [0]
  for k in range(1,n+1):
    hs.append(xs[k] - xs[k-1])
  print hs

  #calculate lambdas
  lambdas = [0]
  for i in range(1,n):
    lambdas.append(hs[i] / (hs[i] + hs[i+1]))
  print lambdas
    
  #calculate ds
  temp = []
  for k in range(0,n):
    diff = ys[k+1] - ys[k]
    diff = diff / (xs[k+1] - xs[k])
    temp.append(diff)
  
  ds = [0]
  for k in range(0,n-1):
    diff = temp[k+1] - temp[k]
    diff = diff / (xs[k+2] - xs[k])
    ds.append(6.0 * diff)
  print ds

  # slove the equations
  qs = [0]
  us = [0]
  ps = [0]
  for k in range(1,n):
    ps.append(lambdas[k]*qs[k-1] + 2)
    qs.append((lambdas[k] - 1)/ps[k])
    us.append((ds[k] - lambdas[k]*us[k-1]) / ps[k])

  ms = [us[n-1]] 
  for i in range(2,n):
    k = n - i
    ms.append(us[k] + qs[k]*ms(i-2))
  ms.append(0)
  ms.reverse()
  ms.append(0)
  print ms

  def f(x):
    k = determine_interval(x,xs)
    if k == 0:
      k = 1
    elif k == n+1:
      k = n

    A = 1.0 / 6.0 * ms[k-1]
    B = 1.0 / 6.0 * ms[k]
    C = ys[k-1] - 1.0 / 6.0 * ms[k-1] * hs[k] * hs[k]
    D = ys[k] - 1.0 / 6.0 * ms[k] * hs[k] * hs[k]
    val = A*p3(xs[k] - x) + B*p3(x - xs[k-1]) + C*(xs[k] - x) + D*(x - xs[k-1])
    return val / hs[k]


  plot.plot(xs,ys,"ro")
  spline_xs = float_range(xs[0]-1, xs[n]+1, n*100)
  spline_ys = [f(x) for x in spline_xs]
  plot.plot(spline_xs,spline_ys,"b-")
  plot.show()

points = [(1,1),(2,20),(4,-3)]
spline(points)
