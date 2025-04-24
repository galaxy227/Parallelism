CC = g++
CCFLAGS = -O0 -fopenmp

main: main.o
	$(CC) $(CCFLAGS) main.o -o main

main.o: main.cc
	$(CC) $(CCFLAGS) -c main.cc -o main.o

clean:
	rm main *.o
