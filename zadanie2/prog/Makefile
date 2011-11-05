CFLAGS = -c -g -Wall
LDFLAGS = -lm
LIBS = bitmap_channel.o bitmap_image.o bitmap_image_sin.o

all: bitmap_sin_test


bitmap_channel.o: bitmap_channel.cpp bitmap_channel.h
	g++ $(CFLAGS) bitmap_channel.cpp -o bitmap_channel.o 

bitmap_image.o: bitmap_image.cpp bitmap_image.h
	g++ $(CFLAGS) bitmap_image.cpp -o bitmap_image.o 

bitmap_image_sin.o: bitmap_image_sin.cpp bitmap_image_sin.h
	g++ $(CFLAGS) bitmap_image_sin.cpp -o bitmap_image_sin.o 


bitmap_load_test.run: $(LIBS) bitmap_load_test.cpp
	g++ $(CFLAGS) bitmap_load_test.cpp -o bitmap_load_test.o
	g++ $(LDFLAGS) $(LIBS) bitmap_load_test.o -o bitmap_load_test.run 
	

bitmap_sin_test.run: $(LIBS) bitmap_sin_test.cpp
	g++ $(CFLAGS) bitmap_sin_test.cpp -o bitmap_sin_test.o
	g++ $(LDFLAGS) $(LIBS) bitmap_sin_test.o -o bitmap_sin_test.run 


bitmap_sin_test: bitmap_sin_test.run
	./bitmap_sin_test.run 
	eog ../obrazki/sin_test.bmp

clean:
	rm *.o
	rm *.run
