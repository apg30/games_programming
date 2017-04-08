#ifndef MAZE_H
#define MAZE_H

#define ROWS 20
#define COLUMNS ROWS

#include "Cell.h"
#include <utility>
#include <vector>

class Maze{
public:

  // Functions
  Maze();
  ~Maze();
//  void generate_maze(int obstacles[20][20]);
  void print_maze(int obstacles[20][20],int path[20][20], std::pair<int,int> start_position,std::pair<int,int> end_position);
  std::pair<int,int> select_start_position();
  std::pair<int,int> select_end_position();
  void reset_properties(Cell cell_to_reset);
  // Variables
  Cell cells[20][20];
};
#endif
