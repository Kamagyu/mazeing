#ifndef CONFIG_H
#define CONFIG_H

// May be overwritten by the -MSIZE flag using make run
#ifndef maze_size
#define maze_size 201
#endif

extern int screen_width;
extern int screen_height;
extern int tile_width;
extern int tile_height;

#endif
