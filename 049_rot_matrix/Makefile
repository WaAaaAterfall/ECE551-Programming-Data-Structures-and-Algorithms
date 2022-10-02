rotateMatrix:rotateMatrix.o
	gcc -ggdb3 -o rotateMatrix rotateMatrix.o

rotateMatrix.o:rotateMatrix.c
	gcc -ggdb3 -std=gnu99 -pedantic -c rotateMatrix.c

.PHONY: clean
clean:
	rm -f rotateMatrix *.o
