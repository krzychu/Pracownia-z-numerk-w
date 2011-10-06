matrix_test: matrix.h matrix_test.cpp
	g++ matrix_test.cpp -g -o matrix_test.run
	./matrix_test.run > in.m
	octave in.m
	rm in.m

memory_test: matrix.h matrix_test.cpp
	g++ matrix_test.cpp -g -o matrix_test.run -DTEST_MEMORY
	valgrind ./matrix_test.run

submatrix_test: matrix.h matrix_test.cpp
	g++ matrix_test.cpp -g -o matrix_test.run -DTEST_SUB
	./matrix_test.run
