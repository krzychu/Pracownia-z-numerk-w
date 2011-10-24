set terminal late
set output "inverse_X-1_X.tex"
set style line 1 linewidth 5
set xrange [0:2000]
set key inside right bottom
plot "inverse_double.dat" using 1:5 ls 1 smooth sbezier title "algorytm naturlany", "inverse_double.dat" using 1:6 ls 4 smooth sbezier title "algorytm Strassena", "inverse_double.dat" using 1:7 smooth sbezier title "algorytm Strassena"
set output
