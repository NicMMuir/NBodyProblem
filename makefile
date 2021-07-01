DEPS=Body.c Node.c NBody.c

all:
	mpicc -g -I/usr/lib/x86_64-linux-gnu/openmpi/include/openmpi -o main main.c $(DEPS)  -lm

clean:
	rm main

run:
	./main
