CC = g++

CFLAGS = -O1 -Wall -Wno-missing-braces
LIB = lib/
INCLUDE = include/
LINKERS = -lraylib -lopengl32 -lgdi32 -lwinmm #-mwindows

SRC = src/*.cpp
OUT = main

build:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) -I $(INCLUDE) -L $(LIB) $(LINKERS)