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
    while (!WindowShouldClose())   
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        draw_maze(maze, BLACK);

        int trav[mazeSize][mazeSize];
        int clock = 0;
        reset_traversal(trav);

        int start_point[2];
        
        if (IsMouseButtonDown(0)) {
            int x_f = mazeSize*GetMouseX()/screenWidth;
            int y_f = mazeSize*GetMouseY()/screenHeight;
            if (!maze[x_f][y_f]) {
                max_dist = dfs(x_f, y_f, maze, trav, &clock);
            }
        }
        
        draw_traversal(trav, max_dist);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}