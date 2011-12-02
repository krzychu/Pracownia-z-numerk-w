set terminal late
set output "time_plot.tex"
set style line 1 linewidth 5
set xrange [0:1100]
set key left top
set key Left
set key width 5
plot "time_test.dat" using 1:2 ls 1 smooth sbezier title "algorytm NS", "time_test.dat" using 1:3 ls 4 smooth sbezier title "algorytm AFS(I)", "time_test.dat" using 1:4 ls 5 smooth sbezier title "algorytm AFS(III)"
set output
