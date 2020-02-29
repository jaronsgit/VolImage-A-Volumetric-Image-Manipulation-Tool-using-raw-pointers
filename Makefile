CC=g++
LIBS=-lm

volimage: driver.o VolImage.o
	$(CC) driver.o VolImage.o -o volimage -std=c++11 $(LIBS)


%.o : %.cpp   
	$(CC) -c $< -o $@ -std=c++11
   

# deletes all the object code files as well as the previously generated outputs
clean:
	@rm -f *.o
	@rm volimage
	@rm -f ./brain_mri_raws_output/*.raw
	@rm -f ./brain_mri_raws_output/*.dat
   
run:
	./volimage MRI