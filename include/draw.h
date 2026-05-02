#ifndef DRAW_H
#define DRAW_H

#include <raylib.h>
#include "config.h"

void draw_tile(int x, int y, Color color);
void draw_maze(int mat[maze_size][maze_size], Color color);
void draw_traversal(int trav[maze_size][maze_size], int max_dist);

#endif