DEPS=Body.c Node.c NBody.c
CC=gcc

all:
	$(CC) main.c $(DEPS) -o main -lm

clean:
	rm main

run:
	./main
