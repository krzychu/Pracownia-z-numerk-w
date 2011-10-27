set terminal late
set output "assoc_float.tex"
set style line 1 linewidth 5
set logscale y 1000
set xrange [0:500]
set key right bottom
plot "assoc_float.dat" using 1:2 ls 1 smooth sbezier title "algorytm naturalny", "assoc_float.dat" using 1:3 ls 4 smooth sbezier title "algorytm Strassena", "assoc_float.dat" using 1:4 ls 5 smooth sbezier title "algorytm z progiem"
set output
