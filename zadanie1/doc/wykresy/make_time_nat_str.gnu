set terminal late
set output "time_nat_str.tex"
set style line 1 linewidth 5
set style line 2 linewidth 8
set logscale y 1000
set xrange [0:500]
set key inside right bottom
set key font "Times,4"
plot "time_all.dat" using 1:2 ls 1 smooth sbezier title "algorytm naturalny", "time_all.dat" using 1:3 ls 4 smooth sbezier title "algorytm Strassena"
set output
