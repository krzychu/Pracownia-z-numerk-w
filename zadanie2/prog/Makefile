CFLAGS = -c -g -Wall
LDFLAGS = -lm

all: bitmap_load_test


bitmap.o: bitmap.cpp bitmap.h
	g++ $(CFLAGS) bitmap.cpp -o bitmap.o 

bitmap_load_test: bitmap.o bitmap_load_test.cpp
	g++ $(CFLAGS) bitmap_load_test.cpp -o bitmap_load_test.o
	g++ $(LDFLAGS) bitmap.o bitmap_load_test.o -o bitmap_load_test.run 
	


clean:
	rm *.o
	rm *.run
