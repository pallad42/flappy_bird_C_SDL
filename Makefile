SRC = src
OBJ = obj
INCLUDE = include
LIB = lib
BIN = bin

CC = gcc
PROGRAM_NAME = $(BIN)\program

INCLUDE_PATHS = -I$(INCLUDE) -I$(LIB)\SDL2\include
LIBRARY_PATHS = -L$(LIB)\SDL2\lib

COMPILER_FLAGS = -std=c11 -Wall -std=gnu99
LIBRARY_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: $(OBJECTS)
	$(CC) $^ $(LIBRARY_PATHS) $(LIBRARY_FLAGS) -o $(PROGRAM_NAME)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -c $< -o $@
	
clean:
	del /S $(OBJ)\*.o $(PROGRAM_NAME).exe