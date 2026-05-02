#include "draw.h"
#include <assert.h>

void draw_tile(int x, int y, Color color) {
    assert(x < maze_size && y < maze_size);
    DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, color);
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
            float hue = 60. - l * (60. + 90.);
            if (hue < 0) hue += 360.;
            Color c = ColorFromHSV(hue, 1., 1.);
            draw_tile(i, j, c);

        }

    }
}