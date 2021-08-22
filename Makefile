CC = gcc

INCLUDEFLAGS = -Ithirdparty/glew/include -Ithirdparty/glfw/include -Ithirdparty/cglm/include -Isrc/modules
LIBS = thirdparty/glew/lib/libGLEW.a thirdparty/glfw/src/libglfw3.a thirdparty/cglm/libcglm.a
LINKFLAGS = -ldl -lGL -lX11 -lpthread -lm
EXECUTABLE = build/minecraft
SRC  = $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ  = $(SRC:.c=.o)

.PHONY: all run cleanobj

all: game

game: $(OBJ)
	$(CC) src/main.c $(LINKFLAGS) $(INCLUDEFLAGS) $(LIBS) $^ -o $(EXECUTABLE)
	$(MAKE) cleanobj

run: game
	./$(EXECUTABLE)

%.o: %.c
	$(CC) $(INCLUDEFLAGS) -o $@ -c $<
cleanobj:
	rm -rf $(OBJ)
