CC = gcc
CFLAGS = -Wall -Werror -fPIC -O0 -g
TRASH = *.o
EXECUTABLES = maze maze_1 maze_2 maze_3

all: maze maze_1 maze_2 maze_3

maze: maze.c
	$(CC) $(CFLAGS) maze.c -o $@

maze_1: maze.c patch_1
	patch -b maze.c patch_1
	$(CC) $(CFLAGS) maze.c -o maze_1
	mv maze.c.orig maze.c

maze_2: maze.c patch_2
	patch -b maze.c patch_2
	$(CC) $(CFLAGS) maze.c -o maze_2
	mv maze.c.orig maze.c

maze_3: maze.c patch_3
	patch -b maze.c patch_3
	$(CC) $(CFLAGS) maze.c -o maze_3
	mv maze.c.orig maze.c

run: all
	./maze
	./maze_1 10
	./maze_2 ._ 10
	./maze_3 0 ._ 10
	./maze_3 0 ._ 10

clean:
	rm -rf $(TRASH) $(EXECUTABLES)
