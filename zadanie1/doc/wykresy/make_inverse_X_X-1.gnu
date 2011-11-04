set terminal late
set output "inverse_X_X-1.tex"
set style line 1 linewidth 5
set logscale y 1000
set ylabel "Jednostka: 1e-30" offset -8,10 font ",2"
set xrange [0:500]
plot "inverse_double_changed.dat" using 1:2 ls 1 smooth sbezier title "algorytm naturalny", "inverse_double_changed.dat" using 1:3 ls 4 smooth sbezier title "algorytm Strassena", "inverse_double_changed.dat" using 1:4 ls 9 smooth sbezier title "algorytm z progiem"
set output
