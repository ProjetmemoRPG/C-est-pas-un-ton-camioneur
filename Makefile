CC=gcc
CFLAGS=-I.

finalfred: finalfred.c
	$(CC) -o fred finalfred.c $(CFLAGS)

newjamy: newjamy.c
	$(CC) -o jamy newjamy.c $(CFLAGS)

truesabine: truesabine.c
	$(CC) -o sabine truesabine.c $(CFLAGS)

marcel:
	./marcel.sh

clean:
	rm -f fred jamy sabine
