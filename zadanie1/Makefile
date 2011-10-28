# porównuje szybkość wszystkich trzech metod w zakresie [2;512]
time_test_all: time_test_all.cpp benchmark.cpp matrix.h
	g++  benchmark.cpp time_test_all.cpp -g -O2 -Wall -o time_test_all.run
	./time_test_all.run > time_all.dat



# porównuje szybkość metody naturalnej i zmodyfikowanej strassena w zakresie [2;2048]
time_test_best: time_test_best.cpp benchmark.cpp matrix.h
	g++  benchmark.cpp time_test_best.cpp -g -O2 -Wall -o time_test_best.run
	./time_test_best.run > time_best.dat



# porównuje wszystkie metody pod względem dokładności w zakresie [2:512]
assoc_test: assoc_test.cpp matrix.h
	g++  assoc_test.cpp -g -Wall -O2 -o assoc_test.run
	./assoc_test.run double > assoc_double.dat
	./assoc_test.run float > assoc_float.dat



# porównuje wszystkie metody pod względem dokładności w zakresie [2:512]
inverse_test: inverse_test.cpp matrix.h
	g++  inverse_test.cpp -g -O2 -Wall -o inverse_test.run
	./inverse_test.run double > inverse_double.dat
	./inverse_test.run float > inverse_float.dat



# pomaga wyznaczyć optymalny próg, ale wymaga gnuplota
threshold: threshold_test.cpp benchmark.o matrix.h
	g++  threshold_test.cpp -g -O2 -Wall -c -o threshold_test.o
	g++  threshold_test.o benchmark.o -o threshold_test.run
	./threshold_test.run > threshold.dat
	gnuplot -p threshold_plot.gnu
 



