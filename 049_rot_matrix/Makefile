rotateMatrix:rotateMatrix.o
	gcc -o rotateMatrix rotateMatrix.o

rotateMatrix.o:rotateMatrix.c
	gcc -Wall -std=gnu99 -pedantic -c rotateMatrix.c

.PHONY: clean
clean:
	rm -f rotateMatrix *.o
