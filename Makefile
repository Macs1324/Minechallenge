CC = gcc
DEST = build/minecraft

INCLUDES = -Ithirdparty/glfw/include -Ithirdparty/glew/include -Ithirdparty/cglm/include -Isrc/modules/include
LIBS = thirdparty/glew/lib/libGLEW.a thirdparty/glfw/src/libglfw3.a thirdparty/cglm/libcglm.a
FLAGS = -ldl -lX11 -lpthread -lm -lGL -lglfw3

all: game

game: $(wildcard src/modules/*)
	$(CC) src/main.c $(FLAGS) $(INCLUDES) $(LIBS) -o $(DEST) 

%.o: %.c
	$(CC) -o$@ -c $<

run: all
	./$(DEST)