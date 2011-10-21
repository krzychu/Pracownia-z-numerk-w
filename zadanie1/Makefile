
# szybki test sprawdzający poprawność działania obu metod
matrix_test: matrix.h matrix_test.cpp
	g++ matrix_test.cpp benchmark.cpp -g -Wall -o matrix_test.run 
	./matrix_test.run > in.m
	octave in.m
	rm in.m


# sprawdza program pod kątem wycieków pamięci
memory_test: matrix.h memory_test.cpp
	g++ memory_test.cpp -g -Wall -o memory_test.run
	echo "strassen:"
	valgrind ./memory_test.run double strassen  5 10
	echo "normal:"
	valgrind ./memory_test.run double normal 5 10


# porównuje szybkość wszystkich trzech metod w zakresie [2;512]
time_test_all: time_test_all.cpp benchmark.cpp matrix.h
	g++  benchmark.cpp time_test_all.cpp -g -Wall -o time_test_all.run
	./time_test_all.run > time_all.dat


# porównuje szybkość metody naturalnej i zmodyfikowanej strassena w zakresie [2;2048]
time_test_best: time_test_best.cpp benchmark.cpp matrix.h
	g++  benchmark.cpp time_test_best.cpp -g -Wall -o time_test_best.run
	./time_test_best.run > time_best.dat



# porównuje wszystkie metody pod względem dokładności w zakresie [2:512]




# porównuje wszystkie metody pod względem dokładności w zakresie [2:512]
inverse_test: inverse_test.cpp matrix.h
	g++  inverse_test.cpp -g -Wall -o inverse_test.run
	./inverse_test.run double > inverse_double.dat
	./inverse_test.run float > inverse_float.dat



# pomaga wyznaczyć optymalny próg
threshold: threshold_test.cpp benchmark.o matrix.h
	g++  threshold_test.cpp -g -Wall -c -o threshold_test.o
	g++  threshold_test.o benchmark.o -o threshold_test.run
	./threshold_test.run > threshold.dat
	gnuplot -p threshold_plot.gnu
 



