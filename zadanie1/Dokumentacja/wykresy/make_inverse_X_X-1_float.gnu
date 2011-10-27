set terminal late
set output "inverse_X_X-1_float.tex"
set style line 1 linewidth 5
set xrange[0:500]
set logscale y 1000
plot "inverse_float_changed.dat" using 1:2 ls 1 smooth sbezier title "algorytm naturalny", "inverse_float_changed.dat" using 1:3 ls 4 smooth sbezier title "algorytm Strassena", "inverse_float_changed.dat" using 1:4 ls 5 smooth sbezier title "algorytm z progiem"
set output
