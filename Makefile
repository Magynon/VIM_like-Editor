all: build

build:
	gcc -Wall -std=c99 -o editor *.c
clean:
	rm editor