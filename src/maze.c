#include "maze.h"
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

void carve(int maze[maze_size][maze_size], int x, int y) {
    int dx[] = {0, 0, -2, 2};
    int dy[] = {-2, 2, 0, 0};

    int order[] = {0, 1, 2, 3};
    for (int i = 3; i > 0; i--) {
        int j = arc4random_uniform(i+1);
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[order[d]];
        int ny = y + dy[order[d]];

        if (nx < 0 || ny < 0 || nx >= maze_size || ny >= maze_size) continue;
        if (maze[nx][ny] != 2) continue;

        maze[x + dx[order[d]]/2][y + dy[order[d]]/2] = 0;
        maze[nx][ny] = 0;

        carve(maze, nx, ny);
    }
}

void create_maze(int maze[maze_size][maze_size], double open_percentage) {
    assert(maze_size % 2 == 1);

    for (int i = 0; i < maze_size; i++)
        for (int j = 0; j < maze_size; j++)
            maze[i][j] = (i % 2 == 1 && j % 2 == 1) ? 2 : 1;

    maze[1][1] = 0;
    carve(maze, 1, 1);

    for (int i = 1; i < maze_size - 1; i++) {
        for (int j = 1; j < maze_size - 1; j++) {
            if (i % 2 != j % 2) {
                maze[i][j] &= ((float)arc4random()/UINT_MAX) > open_percentage;            
            }
        }
    }
}