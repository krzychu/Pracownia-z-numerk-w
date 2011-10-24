set terminal late
set output "inverse_X_X-1.tex"
set style line 1 linewidth 5
set xrange [0:2000]
set key inside right bottom
plot "inverse_double.dat" using 1:2 ls 1 smooth sbezier title "algorytm naturalny", "inverse_double.dat" using 1:3 ls 4 smooth sbezier title "algorytm Strassena", "inverse_double.dat" using 1:4 ls 5 smooth sbezier title "algorytm z progiem"
set output
