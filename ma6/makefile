CC    = g++
FLAGS = -g -Wall --std=c++0x

ifeq ($(shell uname -p | grep -o "64"),64)
	ARCH=64
else
	ARCH=32
endif

LIB_OBJECTS = gcc-${ARCH}bit/IGL.o gcc-${ARCH}bit/unit6.o
OWN_OBJECTS = greyscale.o
OBJECTS = ${LIB_OBJECTS} ${OWN_OBJECTS}

.PHONY: all
all: mapraview.exe test1.exe test2.exe test3.exe test4.exe test5.exe test6.exe test7.exe test8.exe test9.exe test10.exe test11.exe formattest.exe

%.exe: %.o $(OWN_OBJECTS)
	$(CC) $(FLAGS) -o $@ $< ${OBJECTS}

.PRECIOUS: %.o
%.o: %.cpp %.h
	${CC} ${FLAGS} -c -o $@ $<

.PHONY : clean
clean : 
	rm -f *.exe *.o

.PHONY : tests
tests : all
	./test1.exe
	./bildtest -a1 output/result1.pgm
	./test2.exe
	./bildtest -a2 output/result2.pgm
	./test3.exe
	./bildtest -a3 output/result3.pgm
	./test4.exe
	./bildtest -a4 output/result4.pgm
	./test5.exe
	./bildtest -a5 output/result5.pgm
	./test6.exe
	./bildtest -a6 output/result6.pgm
	./test7.exe
	./bildtest -a7 output/result7.pgm
	./test8.exe
	./bildtest -a8 output/result8.pgm	
	./test9.exe
	./bildtest -a9 output/result9.pgm	
	./test10.exe
	./bildtest -a10 output/result10.pgm	
	./test11.exe
	./bildtest -a11 output/result11.pgm	
	