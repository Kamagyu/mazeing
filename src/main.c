#include <limits.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "maze.h"
#include "traversal.h"
#include "draw.h"

int screen_width;
int screen_height;
int tile_width;
int tile_height;

int main(int argc, char **argv)
{
    screen_width = screen_height = (argc > 1) ? atoi(argv[1]) : 800;

    int maze[maze_size][maze_size];
    create_maze(maze, 0.);

    tile_width = (screen_width + maze_size - 1)/maze_size;
    tile_height = (screen_height + maze_size - 1)/maze_size;

    InitWindow(screen_width, screen_height, "(A)Mazeing!");
    SetTargetFPS(60);

    int max_dist = 0;
    int trav[maze_size][maze_size];
    bool traversed = false;

    printf("Starting!\n");

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

        // Press [R] to regenerate once
        // Hold [Shift + R] to regenerate continuously
        if (IsKeyPressed(KEY_R) ^ (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_R)) ) {
            const double max_openness = 0.75;
            double p = max_openness * (float)arc4random() / UINT_MAX;
            create_maze(maze, p*p*p);
            traversed = false;
        }

    }

    CloseWindow();
    return EXIT_SUCCESS;
}