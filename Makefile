all : crypto

run : crypto
	./crypto

crypto: main.o fonction.o
	gcc main.o fonction.o  -o  crypto -lgmp

main.o : main.c fonction.h 
	gcc -c -Wall main.c -lgmp

fonction.o : fonction.c fonction.h
	gcc -c -Wall fonction.c -lgmp

clean: 
	rm -rf *.o
	rm -rf crypto
