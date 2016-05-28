CC=clang

all: src/*.c 
	$(CC) -I ./include src/*.c -o server

clean:
	rm server
