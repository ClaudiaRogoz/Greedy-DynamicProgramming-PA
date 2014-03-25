CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lm

SOURCES=$(wildcard *.cpp)
OBJECTS=$(addsuffix .o, $(basename ${SOURCES}))
EXECUTABLES=Sauron TheMatrix 
CFLAGS+=-g

build: $(OBJECTS) $(EXECUTABLES)

p1: Sauron.o
	$(CC) $(LDFLAGS) p1.o -o $@

p2: TheMatrix.o
	$(CC) $(LDFLAGS) p2.o -o $@

run-p1: Sauron
	./Sauron
	
run-p2: TheMatrix
	./TheMatrix
	
%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ${EXECUTABLES} ${OBJECTS} *.d

.PHONY: all clean