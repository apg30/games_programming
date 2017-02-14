#ifndef MAZE_H
#define MAZE_H

#define ROWS 20
#define COLUMNS ROWS

#include "Cell.h"

class Maze{
public:

  // Functions
  Maze();
  ~Maze();
  void generate_maze();
  void print_maze();
  Cell select_start_position();
  Cell select_end_position();
  void reset_properties(Cell cell_to_reset);
  // Variables
  Cell cells[20][20];
};
#endif
