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
all: mapraview.exe test.exe

%.exe: %.o $(OWN_OBJECTS)
	$(CC) $(FLAGS) -o $@ $< ${OBJECTS}

.PRECIOUS: %.o
%.o: %.cpp %.h
	${CC} ${FLAGS} -c -o $@ $<

.PHONY : clean
clean : 
	rm -f *.exe *.o
