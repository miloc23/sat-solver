all: parse.c
	gcc -g parse.c -o parse

debug: parse.debug

parse.debug: parse.c
	gcc -g -D DEBUG parse.c -o $@ 
