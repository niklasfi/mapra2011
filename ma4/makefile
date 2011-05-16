CC    = g++
CPPFLAGS = -g -Wall -std=c++0x -O3 -DNOBOUNDS
#-DNOBOUNDS definiert nobounds
LDFLAGS = -L. -lz

OBJECTS = vektor.o matrix.o

ifeq ($(shell uname -p | grep -o "64"),64)
	ARCH=64
else
	ARCH=32
endif

.PHONY : all
all: test4.exe powerit.exe

%.exe: %.o ${OBJECTS}
	${CXX} ${LDFLAGS} -o $@ $< ${OBJECTS} gcc-${ARCH}bit/unit4.o

%.o: %.cpp %.h
	${CXX} ${CPPFLAGS} -c $<

.PHONY : clean
clean : 
	rm -f *.exe ${OBJECTS}
