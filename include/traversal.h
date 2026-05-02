#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "config.h"

void reset_traversal(int trav[maze_size][maze_size]);
int dfs(int x, int y, int maze[maze_size][maze_size], int visited[maze_size][maze_size], int *clock);
int bfs(int sx, int sy, int maze[maze_size][maze_size], int d[maze_size][maze_size]);

#endif