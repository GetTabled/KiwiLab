CC=gcc
CFLAGS=-Wall -Wextra -g

FFMPEG_LIBS=libavformat libavfilter libavcodec
PACKAGE=$(shell pkg-config --cflags gtk4 $(FFMPEG_LIBS))
LDLIBS=$(shell pkg-config --libs gtk4 $(FFMPEG_LIBS))

SRC_DIR=src/
OBJ_DIR=obj/
CFILES=$(SRC_DIR)*.c
OBJECTS=$(OBJ_DIR)main.o
BINARY=bin

all: $(BINARY)


$(BINARY): $(OBJECTS)
		$(CC) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
		$(CC) $(PACKAGE) $(CFLAGS) -c -o $@ $^

clean:
		rm -r $(BINARY) $(OBJECTS)