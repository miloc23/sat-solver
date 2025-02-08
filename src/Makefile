all: test_parse.c parse.c
	gcc -g parse.c test_parse.c -o test_parse

debug: test_parse.debug

test_parse.debug: test_parse.c parse.c
	gcc -g -D DEBUG test_parse.c parse.c -o $@ 
