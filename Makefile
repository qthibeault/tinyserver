CC=clang

all: src/*.c 
	$(CC) -lpthread -I ./include src/*.c -o server

clean:
	rm server
