# name of the project
PROJECTNAME = myframework
# destination folder (where the .exe will live)
OUTPUT_DIR = build

# include folder(s)
INCLUDE_DIRS = -Iinclude -Iheaders

# static lib directory and static libs used respectively
LIB_DIRS = -Llib
LIBS = -lmingw32 -lSDL2Main -lSDL2 -lSDL2_image

# source file(s)
SRC = $(wildcard src/*.cpp) testprogram/main.cpp # for testing

# general flags for compiling
CFLAGS = -g -DDEBUG

# compiler
CC = g++

# default compilation command (default = no additional args)
default:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)