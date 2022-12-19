CC=gcc
CFLAGS=-Wall -Wextra -g
PACKAGE=$(shell pkg-config --cflags gtk4)
LDLIBS=$(shell pkg-config --libs gtk4)

SRC_DIR=src/
OBJ_DIR=obj/
CFILES=$(SRC_DIR)main.c
OBJECTS=$(OBJ_DIR)main.o
BINARY=bin

all: $(BINARY)


$(BINARY): $(OBJECTS)
		$(CC) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
		$(CC) $(PACKAGE) $(CFLAGS) -c -o $@ $^

clean:
		rm -r $(BINARY) $(OBJECTS)