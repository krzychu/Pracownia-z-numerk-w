CFLAGS = -c -g -Wall -O2
LDFLAGS = -lm
LIBS = bitmap_channel.o bitmap_image.o bitmap_image_procedural.o \
       resizers_base.o resizers_closest.o resizers_linear.o

resizers_closest.o: resizers_closest.cpp resizers_closest.h
	g++ $(CFLAGS) resizers_closest.cpp -o resizers_closest.o 

resizers_linear.o: resizers_linear.cpp resizers_linear.h
	g++ $(CFLAGS) resizers_linear.cpp -o resizers_linear.o 

resizers_base.o: resizers_base.cpp resizers_base.h
	g++ $(CFLAGS) resizers_base.cpp -o resizers_base.o 

bitmap_channel.o: bitmap_channel.cpp bitmap_channel.h
	g++ $(CFLAGS) bitmap_channel.cpp -o bitmap_channel.o 

bitmap_image.o: bitmap_image.cpp bitmap_image.h
	g++ $(CFLAGS) bitmap_image.cpp -o bitmap_image.o 

bitmap_image_procedural.o: bitmap_image_procedural.cpp bitmap_image_procedural.h
	g++ $(CFLAGS) bitmap_image_procedural.cpp -o bitmap_image_procedural.o 


bitmap_load_test.run: $(LIBS) bitmap_load_test.cpp
	g++ $(CFLAGS) bitmap_load_test.cpp -o bitmap_load_test.o
	g++ $(LDFLAGS) $(LIBS) bitmap_load_test.o -o bitmap_load_test.run 
	

procedural_bitmap_test.run: $(LIBS) procedural_bitmap_test.cpp
	g++ $(CFLAGS) procedural_bitmap_test.cpp -o procedural_bitmap_test.o
	g++ $(LDFLAGS) $(LIBS) procedural_bitmap_test.o -o procedural_bitmap_test.run 

resizers_test.run: $(LIBS) resizers_test.cpp
	g++ $(CFLAGS) resizers_test.cpp -o resizers_test.o
	g++ $(LDFLAGS) $(LIBS) resizers_test.o -o resizers_test.run 

bitmap_load_test: bitmap_load_test.run
	./bitmap_load_test.run

procedural_bitmap_test: procedural_bitmap_test.run
	./procedural_bitmap_test.run 
	eog ../obrazki/sin_test.bmp
	eog ../obrazki/saw_test.bmp
	eog ../obrazki/runge_test.bmp

resizers_test: resizers_test.run
	./resizers_test.run ../obrazki/pizza.bmp linear 250 250 ../obrazki/pizza_out_linear.bmp
	./resizers_test.run ../obrazki/pizza.bmp closest 250 250 ../obrazki/pizza_out_closest.bmp
	
	convert '(' ../obrazki/pizza.bmp +append ')' \
	'(' ../obrazki/pizza_out_linear.bmp ../obrazki/pizza_out_closest.bmp +append ')' \
	-append ../obrazki/all.bmp
	
	eog ../obrazki/all.bmp


clean:
	rm *.o
	rm *.run
