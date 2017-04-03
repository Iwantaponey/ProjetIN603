all : crypto

run : crypto
	./crypto

crypto: main.o fonction.o
	gcc main.o fonction.o  -o  crypto

main.o : main.c fonction.h 
	gcc -c -Wall -lgmp main.c

fonction.o : fonction.c fonction.h
	gcc -c -Wall -lgmp fonction.c

clean: 
	rm -rf *.o
	rm -rf crypto
