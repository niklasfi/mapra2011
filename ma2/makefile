gpp=g++ -Wall
objects = quicksort.o

ifeq ($(shell uname -p | grep -o "64"),64)
	ARCH=64
else
	ARCH=32
endif

run.exe: unit2.cpp $(objects)
	$(gpp) -o run.exe unit2.cpp $(objects) gcc-${ARCH}bit/unit2.o
	
%.o: %.cpp
	$(gpp) -c $<


clean: 
	rm run.exe $(objects)
