set terminal late
set output "inverse_X-1_X_float.tex"
set style line 1 linewidth 5
set logscale y 1000
set xrange [0:500]
plot "inverse_float.dat" using 1:5 ls 1 smooth sbezier title "algorytm naturalny", "inverse_float.dat" using 1:6 ls 4 smooth sbezier title "algorytm Strassena", "inverse_float.dat" using 1:7 ls 5 smooth sbezier title "algorytm z progiem"
set output
