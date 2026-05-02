#include <limits.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "maze.h"

#define maze_size 32

int screen_width;
int screen_height;
int tileWidth;
int tileHeight;
 
void draw_tile(int x, int y, Color color) {
    assert(x < maze_size && y < maze_size);
    DrawRectangle(x * tileWidth, y * tileHeight, tileWidth, tileHeight, color);
}

void draw_maze(int mat[maze_size][maze_size], Color color) {
    for (int i = 0; i < maze_size; i++) {
        for (int j = 0; j < maze_size; j++) {
            if (mat[i][j]) {
                draw_tile(i, j, color);
            }

        }

    }
}

void draw_traversal(int trav[maze_size][maze_size], int max_dist) {
    for (int i = 0; i < maze_size; i++) {
        for (int j = 0; j < maze_size; j++) {
            if (trav[i][j] == -1) continue;
            float l = (float)trav[i][j] / max_dist;
            Color c = ColorFromHSV(150*(1-l) + 0*l, 1., 1.);
            draw_tile(i, j, c);

        }

    }
}

void reset_traversal(int trav[maze_size][maze_size]) {
    for (int i = 0; i < maze_size; i++){
        for (int j = 0; j < maze_size; j++) {
            trav[i][j] = -1;
        }
    }
}

int dfs(int x, int y, int maze[maze_size][maze_size], int visited[maze_size][maze_size], int *clock) {
    if (visited[x][y] == -1) {
        (*clock)++;
        visited[x][y] = *clock;

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= maze_size || ny < 0 || ny >= maze_size) continue;

            if (maze[nx][ny] == 0) {
                dfs(nx, ny, maze, visited, clock);
            }
        }
    }
    return *clock;
}

int bfs(int sx, int sy, int maze[maze_size][maze_size], int d[maze_size][maze_size]) {
    for (int i = 0; i < maze_size; i++)
        for (int j = 0; j < maze_size; j++)
            d[i][j] = -1;

    int queue[maze_size * maze_size][2];
    int head = 0, tail = 0;

    d[sx][sy] = 0;
    queue[tail][0] = sx;
    queue[tail][1] = sy;
    tail++;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int max = 0;

    while (head < tail) {
        int x = queue[head][0];
        int y = queue[head][1];
        head++;

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx < 0 || ny < 0 || nx >= maze_size || ny >= maze_size) continue;
            if (maze[nx][ny] == 1) continue;
            if (d[nx][ny] != -1) continue;

            d[nx][ny] = d[x][y] + 1;
            if (d[nx][ny] > max) max = d[nx][ny];
            queue[tail][0] = nx;
            queue[tail][1] = ny;
            tail++;
        }
    }

    return max;
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        int size = atoi(argv[1]);
        screen_width = size;
        screen_height = size;
    } else { // Default value also handled in Makefile
        int size = 800;
        screen_width = size;
        screen_height = size;
    }

    tileWidth = (screen_width + maze_size - 1)/maze_size;
    tileHeight = (screen_height + maze_size - 1)/maze_size;

    InitWindow(screen_width, screen_height, "(A)Mazeing!");
    SetTargetFPS(60);

    int max_dist = 0;
    int trav[maze_size][maze_size];
    bool traversed = false;
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_maze(maze, BLACK);

        int clock = 0;        
        int start_point[2];
        
        if (IsMouseButtonDown(0)) {
            int x_f = maze_size*GetMouseX()/screen_width;
            int y_f = maze_size*GetMouseY()/screen_height;
            if (!maze[x_f][y_f]) {
                reset_traversal(trav);
                // max_dist = dfs(x_f, y_f, maze, trav, &clock);
                max_dist = bfs(x_f, y_f, maze, trav);
                traversed = true;
            }
        }
        
        if (traversed) draw_traversal(trav, max_dist);
        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}