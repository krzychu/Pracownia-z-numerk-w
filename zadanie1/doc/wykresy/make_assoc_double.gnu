set terminal late
set output "assoc_double.tex"
set key right bottom
set style line 1 linewidth 5
set logscale y 1000
set ylabel "Jednostka: 1e-30" offset -8,10
set xrange [0:500]
plot "assoc_double_changed.dat" using 1:2 ls 1 smooth sbezier title "algorytm naturalny", "assoc_double_changed.dat" using 1:3 ls 4 smooth sbezier title "algorytm Strassena", "assoc_double_changed.dat" using 1:4 ls 5 smooth sbezier title "algorytm z progiem"
set output
