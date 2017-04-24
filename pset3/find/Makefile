#
# Makefile
# CS50
#

all: find generate

find: find.c helpers.c helpers.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o find find.c helpers.c -lcs50 -lm

generate: generate.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o generate generate.c

clean:
	rm -f *.o a.out core find generate

test: test.c helpers.c helpers.h sorting_algos.c sorting_algos.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o test test.c helpers.c sorting_algos.c -lcs50 -lm

