DEPS=Body.c Node.c NBody.c
CC=gcc

all: main

main: main.c
	$(CC) main.c $(DEPS) -o main -lm

clean:
	rm main
