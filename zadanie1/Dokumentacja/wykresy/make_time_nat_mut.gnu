set terminal late
set output "time_nat_mut.tex"
set style line 1 linewidth 5
set logscale y 1000
set xrange[0:2000]
set key inside right bottom
set key font "Times,4"
plot "time_best.dat" using 1:2 ls 1 smooth sbezier title "algorytm naturalny", "time_best.dat" using 1:3 ls 4 smooth sbezier title "algorytm z progiem"
set output
