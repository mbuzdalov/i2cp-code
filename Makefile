.PHONY: all
.RECIPEPREFIX=>

CC=g++
CPPFLAGS=-std=c++11 -O3 -Wall -Wextra

all: binsearch-1
clean:
> rm -f binsearch-1

