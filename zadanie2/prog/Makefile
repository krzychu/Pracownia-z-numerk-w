CFLAGS = -c -g -Wall -O2
LDFLAGS = -lm
LIBS = bitmap_channel.o bitmap_image.o bitmap_image_procedural.o \
       resizers_base.o resizers_closest.o resizers_linear.o resizers_cubic.o \
       resizers_combined.o resizers_utils.o
SHOW = eog

################################################################################
#                              Compilation
################################################################################
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
	$(SHOW) ../obrazki/sin_test.bmp
	$(SHOW) ../obrazki/saw_test.bmp
	$(SHOW) ../obrazki/runge_test.bmp

time_test.run: $(LIBS) time_test.cpp
	g++ $(CFLAGS) time_test.cpp -o time_test.o
	g++ $(LDFLAGS) $(LIBS) time_test.o -o time_test.run 


visual_order_test.run: $(LIBS) visual_order_test.cpp
	g++ $(CFLAGS) visual_order_test.cpp -o visual_order_test.o
	g++ $(LDFLAGS) $(LIBS) visual_order_test.o -o visual_order_test.run 


data_loss_test.run: $(LIBS) data_loss_test.cpp
	g++ $(CFLAGS) data_loss_test.cpp -o data_loss_test.o
	g++ $(LDFLAGS) $(LIBS) data_loss_test.o -o data_loss_test.run 


procedural_resize_test.run: $(LIBS) procedural_resize_test.cpp
	g++ $(CFLAGS) procedural_resize_test.cpp -o procedural_resize_test.o
	g++ $(LDFLAGS) $(LIBS) procedural_resize_test.o -o procedural_resize_test.run 



################################################################################
#                              Tests
################################################################################


X_res = 200
Y_res = 200
ORDER = xy
IMAGE_res = linia_50_linear	
OUTFILE_res = linia_50_200_linear

resizers_test: resizers_test.run
	./resizers_test.run ../obrazki/$(IMAGE_res).bmp linear $(ORDER) $(X_res) $(Y_res) \
	../obrazki/$(IMAGE_res)_out_linear.bmp
	./resizers_test.run ../obrazki/$(IMAGE_res).bmp closest $(ORDER) $(X_res) $(Y_res) \
	../obrazki/$(IMAGE_res)_out_closest.bmp
	./resizers_test.run ../obrazki/$(IMAGE_res).bmp cubic $(ORDER) $(X_res) $(Y_res) \
	../obrazki/$(IMAGE_res)_out_cubic.bmp
	./resizers_test.run ../obrazki/$(IMAGE_res).bmp combined $(ORDER) $(X_res) $(Y_res) \
	../obrazki/$(IMAGE_res)_out_combined.bmp

	convert \
	'(' ../obrazki/$(IMAGE_res)_out_cubic.bmp  ../obrazki/$(IMAGE_res)_out_linear.bmp +append ')' \
	'(' ../obrazki/$(IMAGE_res)_out_closest.bmp ../obrazki/$(IMAGE_res)_out_combined.bmp +append ')' \
	-append ../obrazki/$(OUTFILE_res).bmp
	
	rm ../obrazki/$(IMAGE_res)_out_linear.bmp
	rm ../obrazki/$(IMAGE_res)_out_cubic.bmp
	rm ../obrazki/$(IMAGE_res)_out_closest.bmp
	rm ../obrazki/$(IMAGE_res)_out_combined.bmp
	
	$(SHOW) ../obrazki/$(OUTFILE_res).bmp



IMAGE_time = liscie_male
time_test: time_test.run
	./time_test.run 10 1000 5 ../obrazki/$(IMAGE_time).bmp > ../data/time_test.dat


X_ord = 10
Y_ord = 10
IMAGE_ord = pokemon_bw
OUTFILE_ord = all
visual_order_test: visual_order_test.run
	./visual_order_test.run ../obrazki/$(IMAGE_ord).bmp cubic 50 500 ../obrazki/$(OUTFLIE).bmp
	$(SHOW) ../obrazki/$(OUTFLIE).bmp




procedural_resize_test: procedural_resize_test.run
	./procedural_resize_test.run linear sin > ../data/linear_sin.dat
	./procedural_resize_test.run cubic sin > ../data/cubic_sin.dat
	./procedural_resize_test.run closest sin > ../data/closest_sin.dat

	./procedural_resize_test.run linear saw > ../data/linear_saw.dat
	./procedural_resize_test.run cubic saw > ../data/cubic_saw.dat
	./procedural_resize_test.run closest saw > ../data/closest_saw.dat

	./procedural_resize_test.run linear runge > ../data/linear_runge.dat
	./procedural_resize_test.run cubic runge > ../data/cubic_runge.dat
	./procedural_resize_test.run closest runge > ../data/closest_runge.dat




X = 50 
Y = 50
INFILE = pokemon
OUTFILE = pokemon_diff
ALL = all

data_loss_test: data_loss_test.run
	./data_loss_test.run ../obrazki/$(INFILE).bmp linear $(X) $(Y) \
	../obrazki/$(OUTFILE)_diff_linear.bmp ../obrazki/$(OUTFILE)_img_linear.bmp
	./data_loss_test.run ../obrazki/$(INFILE).bmp cubic $(X) $(Y) \
	../obrazki/$(OUTFILE)_diff_cubic.bmp ../obrazki/$(OUTFILE)_img_cubic.bmp
	./data_loss_test.run ../obrazki/$(INFILE).bmp closest $(X) $(Y) \
	../obrazki/$(OUTFILE)_diff_closest.bmp ../obrazki/$(OUTFILE)_img_closest.bmp

	convert \
	'(' ../obrazki/$(OUTFILE)_diff_cubic.bmp  ../obrazki/$(OUTFILE)_img_cubic.bmp +append ')' \
	'(' ../obrazki/$(OUTFILE)_diff_linear.bmp  ../obrazki/$(OUTFILE)_img_linear.bmp +append ')' \
	'(' ../obrazki/$(OUTFILE)_diff_closest.bmp  ../obrazki/$(OUTFILE)_img_closest.bmp +append ')' \
	-append ../obrazki/$(ALL).bmp
	$(SHOW) ../obrazki/$(ALL).bmp

clean:
	rm *.o
	rm *.run
