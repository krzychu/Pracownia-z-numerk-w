
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


submatrix_test: matrix.h matrix_test.cpp
	g++ matrix_test.cpp -g -o matrix_test.run -DTEST_SUB
	./matrix_test.run
