# Make environment
CC = gcc
CFLAGS = -c -g -Wall

# Files
OBJECT_FILES = csapp.o shellex.o

# Productions
all: my257sh

my257sh : $(OBJECT_FILES)
	$(CC) -pthread $(OBJECT_FILES) -o $@

shellex.o : shellex.c csapp.h
	$(CC) $(CFLAGS) $< -o $@

csapp.o : csapp.c csapp.h
	$(CC) $(CFLAGS) $< -o $@
clean: 
	rm -v my257sh $(OBJECT_FILES)
