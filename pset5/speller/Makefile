# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# name for executable
EXE = speller

# space-separated list of header files
HDRS = dictionary.h hash-table.h linked-list.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = speller.c dictionary.c hash-table.c linked-list.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o dictionary trie linked_list hash_table linked-list

linked_list: test_linked_list.c linked-list.c linked-list.h Makefile
	$(CC) $(CFLAGS) -o $@ test_linked_list.c linked-list.c


hash_table: test_hash_table.c hash-table.c linked-list.c linked-list.h hash-table.h Makefile
	$(CC) $(CFLAGS) -o $@ test_hash_table.c hash-table.c linked-list.c
