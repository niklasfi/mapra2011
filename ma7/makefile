CXX = g++
DEBUG = -DDEBUG -g -Wall
ifdef PROFILE
	PROF = -pg
endif
ifndef NPARALLEL
	OMP=-fopenmp
endif

ifdef EECHO
	E=-e
endif

CPPFLAGS = ${DEBUG} -std=c++0x -c -I. ${PROF} ${OMP} ${OPTIMIZE}
LDFLAGS = -L. -lz ${PROF} ${OMP} ${OPTIMIZE}
OBJECTS = container.o object.o

default: all
all: main.exe

ifndef NOCOLORS
BLACK = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
endif

%.test.exe: %.test.o ${OBJECTS}
	@${CXX} ${LDFLAGS} -o $@ $< ${OBJECTS}
	@echo $E -n "${YELLOW}$@${BLACK}"
	@./$@ && echo $E " ${GREEN}ok${BLACK}"

%.exe: %.o ${OBJECTS}
	${CXX} ${LDFLAGS} -o $@ $< ${OBJECTS}

.PHONY: tests
tests: ${TESTS}
	@echo $E "\n${GREEN}--> everything's good! <--${BLACK}"

.PRECIOUS: %.test.o
%.test.o: %.test.cpp %.h
	${CXX} ${CPPFLAGS} -c -o $@ $<

.PRECIOUS: %.o
%.o: %.cpp %.h
	${CXX} ${CPPFLAGS} -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o *.exe

.PHONY: ctests
ctests:
	rm -f ${TESTS}
	${MAKE} tests
