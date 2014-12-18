TARGET= crazyprofessor
SUBTARGET= test
CC= gcc
LDFLAGS= -pthread
SRC = crazyprofessor.c
MOVE=crazyprofessor.o

all: $(TARGET)

crazyprofessor: crazyprofessor.c
	$(CC) -c crazyprofessor.c
	mv $(MOVE) test/
	cd test; make
	
# let's clean up the mess
clean:
	rm -rf crazy
	cd test; rm -rf *.o


