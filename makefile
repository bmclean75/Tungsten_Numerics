#to run example, do "make run"

SHELL = /usr/bin/env bash
.PHONY: clean

CC = g++
CCFLAGS = -Wall -Werror -Wextra -O3 -std=c++20 -pedantic -g -ffast-math -fopenmp -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

all: example

example: 
	$(CC) $(CCFLAGS) example.cpp -o example

clean:
	rm -f example *.o
	
run:example
	./example
