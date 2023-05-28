all: hungarian
 
hungarian: graph.o matching.o aps.o hungarian.o
	gcc -o hungarian graph.o matching.o aps.o hungarian.o main.c -Wall

clean:
	rm -rf *.o