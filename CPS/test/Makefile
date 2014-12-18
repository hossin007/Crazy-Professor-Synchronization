TARGET=crazyprofessor.o
CC=gcc
CFLAGS= -ggdb -Wall

all: test

test: test.o $(TARGET)
	gcc -o crazy test.o $(TARGET) -pthread
	mv crazy ../
	
test.o: test.c crazyprofessor.h
	gcc -c test.c

