
matrix_test: matrix.h matrix_test.cpp
	g++ matrix_test.cpp benchmark.cpp -g -Wall -o matrix_test.run 
	./matrix_test.run > in.m
	octave in.m
	rm in.m

memory_test: matrix.h memory_test.cpp
	g++ memory_test.cpp -g -Wall -o memory_test.run
	echo "strassen:"
	valgrind ./memory_test.run double strassen  5 10
	echo "normal:"
	valgrind ./memory_test.run double normal 5 10


time_test: time_test.cpp benchmark.cpp matrix.h
	g++  benchmark.cpp time_test.cpp -g -Wall -o time_test.run
	./time_test.run > time.dat
	gnuplot -p time_plot.gnu


inverse_test: test_inverses.cpp matrix.h
	g++  test_inverses.cpp -g -Wall -o inverse_test.run
	./inverse_test.run double > inverse_double.dat
	./inverse_test.run float > inverse_float.dat



threshold: threshold_test.cpp benchmark.o matrix.h
	g++  threshold_test.cpp -g -Wall -c -o threshold_test.o
	g++  threshold_test.o benchmark.o -o threshold_test.run
	./threshold_test.run > threshold.dat
	gnuplot -p threshold_plot.gnu
 

benchmark.o: benchmark.cpp
	g++ benchmark.cpp -g -Wall -c -o benchmark.o


