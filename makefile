DEPS=Body.c Node.c NBody.c
CC=mpicc

all:
	$(CC) main.c $(DEPS) -o main -lm

clean:
	rm main

run:
	./main
