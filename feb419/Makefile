all: arith
arith:main.o addition.o subtract.o
	gcc main.o addition.o subtract.o -o arith
main.o:main.c
	gcc -c main.c
addition.o:addition.c
	gcc -c addition.c
subtract.o:subtract.c
	gcc -c subtract.c
clean:
	rm -rf *.o arith
	
	
