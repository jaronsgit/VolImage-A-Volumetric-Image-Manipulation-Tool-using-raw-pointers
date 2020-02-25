CC=g++         # the compiler
LIBS=-lm       # the libraries we will ref

volimage: driver.o VolImage.o
	$(CC) driver.o VolImage.o -o volimage -std=c++11 $(LIBS)

# Implicit pattern rule for compiling object files
%.o : %.cpp   # $< is the first dependancy and $@ is the target
	$(CC) -c $< -o $@ -std=c++11
   

# deletes all the object code files
clean:
	@rm -f *.o
	@rm volimage
   
# copies/moves the relevant binaries and/or libraries to the correct folders   
install:
  
	@mv volimage ~/bin

run:
	./volimage MRI -d 0 1 testOutFinal