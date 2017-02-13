#ifndef MAZE_H
#define MAZE_H

#define ROWS 20
#define COLUMNS ROWS

struct Cell{
    // Variables
    bool visited;
    bool obstacle;
};

class Maze{
public:

  // Functions
  Maze();
  ~Maze();
  void generate_maze();
  void print_maze();
  // Variables
  Cell cells[20][20];
};
#endif
