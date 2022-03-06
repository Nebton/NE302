main : main.o abnf.o
	gcc main.o abnf.o -o main
	rm -f *.o
abnf.o : abnf.c
	gcc -c abnf.c -o abnf.o
main.o : main.c
	gcc -c main.c -o main.o

