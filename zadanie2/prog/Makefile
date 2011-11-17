CFLAGS = -c -g -Wall -O2
LDFLAGS = -lm
LIBS = bitmap_channel.o bitmap_image.o bitmap_image_procedural.o \
       resizers_base.o resizers_closest.o resizers_linear.o resizers_cubic.o \
       resizers_combined.o resizers_utils.o

resizers_utils.o: resizers_utils.cpp resizers_utils.h
	g++ $(CFLAGS) resizers_utils.cpp -o resizers_utils.o 

resizers_combined.o: resizers_combined.cpp resizers_combined.h
	g++ $(CFLAGS) resizers_combined.cpp -o resizers_combined.o 

resizers_cubic.o: resizers_cubic.cpp resizers_cubic.h
	g++ $(CFLAGS) resizers_cubic.cpp -o resizers_cubic.o 

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

X = 500
Y = 500
ORDER = xy
IMAGE = runge_test

resizers_test: resizers_test.run
	./resizers_test.run ../obrazki/$(IMAGE).bmp linear $(ORDER) $(X) $(Y) ../obrazki/$(IMAGE)_out_linear.bmp
	./resizers_test.run ../obrazki/$(IMAGE).bmp closest $(ORDER) $(X) $(Y) ../obrazki/$(IMAGE)_out_closest.bmp
	./resizers_test.run ../obrazki/$(IMAGE).bmp cubic $(ORDER) $(X) $(Y) ../obrazki/$(IMAGE)_out_cubic.bmp
	./resizers_test.run ../obrazki/$(IMAGE).bmp combined $(ORDER) $(X) $(Y) ../obrazki/$(IMAGE)_out_combined.bmp
	
	convert \
	'(' ../obrazki/$(IMAGE)_out_cubic.bmp  ../obrazki/$(IMAGE)_out_linear.bmp +append ')' \
	'(' ../obrazki/$(IMAGE)_out_closest.bmp ../obrazki/$(IMAGE)_out_combined.bmp +append ')' \
	-append ../obrazki/all.bmp
	
	eog ../obrazki/all.bmp


time_test.run: $(LIBS) time_test.cpp
	g++ $(CFLAGS) time_test.cpp -o time_test.o
	g++ $(LDFLAGS) $(LIBS) time_test.o -o time_test.run 
	
time_test: time_test.run
	./time_test.run 10 1000 5 ../obrazki/pizza.bmp

visual_order_test.run: $(LIBS) visual_order_test.cpp
	g++ $(CFLAGS) visual_order_test.cpp -o visual_order_test.o
	g++ $(LDFLAGS) $(LIBS) visual_order_test.o -o visual_order_test.run 
	
visual_order_test: visual_order_test.run
	./visual_order_test.run ../obrazki/saw_test.bmp linear 50 200 ../obrazki/saw_test_diff.bmp
	eog ../obrazki/saw_test_diff.bmp


clean:
	rm *.o
	rm *.run
