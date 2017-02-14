#ifndef MAZE_H
#define MAZE_H

#define ROWS 20
#define COLUMNS ROWS

#include "Cell.h"
#include <utility>

class Maze{
public:

  // Functions
  Maze();
  ~Maze();
  void generate_maze();
  void print_maze();
  std::pair<int,int> select_start_position();
  std::pair<int,int> select_end_position();
  void reset_properties(Cell cell_to_reset);
  // Variables
  Cell cells[20][20];
};
#endif
