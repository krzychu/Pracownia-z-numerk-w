set terminal late
set output "timePlot.tex"
set style line 1 linewidth 5
set xrange[0:200]
set key inside right bottom
set key font "Times,4"
plot "timeTest.dat" using 1:2 ls 1 smooth sbezier title "LU", "timeTest.dat" using 1:3 ls 4 smooth sbezier title "GS", "timeTest.dat" using 1:4 smooth sbezier title "HH"
set output
