#ifndef MAZE_H
#define MAZE_H

#include "config.h"

void carve(int maze[maze_size][maze_size], int x, int y);
void create_maze(int maze[maze_size][maze_size], double open_percentage);

#endif