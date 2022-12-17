CC=gcc
INCDIRS=-I.
OPT=-00
CFLAGS=-Wall -Wextra -g $(INCDIRS) $(OPT)

CFILES=main.c
OBJECTS=main.o

BINARY=bin

all: $(BINARY)
		

$(BINARY): $(OBJECTS)
		$(CC) -o $@ $^

%.o:%.c
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
		rm -rf $(BINARY) $(OBJECTS)