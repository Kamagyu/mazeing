#include <limits.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

const int screenWidth = 1000;
const int screenHeight = 1000;
const int mazeSize = 32;

const int tileWidth = screenWidth/mazeSize;
const int tileHeight = screenHeight/mazeSize;
 

void draw_tile(int x, int y, Color color) {
    assert(x < mazeSize && y < mazeSize);
    DrawRectangle(x * tileWidth, y * tileHeight, tileWidth, tileHeight, color);
}

void draw_maze(int mat[mazeSize][mazeSize], Color color) {
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            if (mat[i][j]) {
                draw_tile(i, j, color);
            }

        }

    }
}

void draw_traversal(int trav[mazeSize][mazeSize], int max_dist) {


    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            if (trav[i][j] == -1) continue;
            float l = (float)trav[i][j] / max_dist;
            Color c = ColorFromHSV(150*(1-l) + 0*l, 1., 1.);
            draw_tile(i, j, c);

        }

    }
}

void reset_traversal(int trav[mazeSize][mazeSize]) {
    for (int i = 0; i < mazeSize; i++){
        for (int j = 0; j < mazeSize; j++) {
            trav[i][j] = -1;
        }
    }
}

int dfs(int x, int y, int maze[mazeSize][mazeSize], int visited[mazeSize][mazeSize], int *clock) {
    if (visited[x][y] == -1) {
        (*clock)++;
        visited[x][y] = *clock;

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= mazeSize || ny < 0 || ny >= mazeSize) continue;

            if (maze[nx][ny] == 0) {
                dfs(nx, ny, maze, visited, clock);
            }
        }
    }
    return *clock;
}

int bfs(int sx, int sy, int maze[mazeSize][mazeSize], int d[mazeSize][mazeSize]) {
    for (int i = 0; i < mazeSize; i++)
        for (int j = 0; j < mazeSize; j++)
            d[i][j] = -1;

    int queue[mazeSize * mazeSize][2];
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

            if (nx < 0 || ny < 0 || nx >= mazeSize || ny >= mazeSize) continue;
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

int main(void)
{
    int maze[32][32] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},
{1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1},
{1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1},
{1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1},
{1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
{1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1},
{1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1},
{1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1},
{1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1},
{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1},
{1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1},
{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
{1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
{1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
{1,1,1,0,0,0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
{1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
{1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
{1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
{1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,0,1},
{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
{1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1},
{1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,1,0,1},
{1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1},
{1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
};

    InitWindow(screenWidth, screenHeight, "(A)Mazeing!");
    SetTargetFPS(60);

    int max_dist = 0;
    int trav[mazeSize][mazeSize];
    bool traversed = false;
    while (!WindowShouldClose())   
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        draw_maze(maze, BLACK);

        
        int clock = 0;
        
        int start_point[2];
        
        if (IsMouseButtonDown(0)) {
            int x_f = mazeSize*GetMouseX()/screenWidth;
            int y_f = mazeSize*GetMouseY()/screenHeight;
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
    return 0;
}