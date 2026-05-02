# Mazeing

A visualization of graphs traversal applied to mazes made with raylib that can generate mazes of various density.

<p align="center">
  <img height="200" hspace="10" src="https://github.com/user-attachments/assets/920ec8d7-8867-41a3-b2fe-c6ee61a60e3d" />
  <img height="200" hspace="10" src="https://github.com/user-attachments/assets/31542cdc-3661-4200-b908-ffc16eff998c" />
  <img height="200" hspace="10" src="https://github.com/user-attachments/assets/d32cba35-6090-45f2-9907-a8dd544e91b9" />
</p>

# How to use

- You can choose the size of the maze by changing the `MAZE_SIZE` macro. **It needs to be an odd number.**
- You can change the size of the window with `./build/main [window_size]` or `make run SIZE=[window_size]`. Doing this way will only create square windows.
- Click on any blank tile to show the distance to every other accessible tile.
- Press `r` to regenerate the maze with a random density of walls
- You can also hold `shift + r` to regenerate continuously 60 times/sec (epilepsy warning).
