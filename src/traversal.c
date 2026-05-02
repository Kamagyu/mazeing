#include "traversal.h"

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