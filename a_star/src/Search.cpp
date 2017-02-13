

#include "Maze.h"



int main()
{
  Maze maze;
  maze.generate_maze();
  maze.print_maze();
  maze.select_positions();
  maze.print_maze();

//  generate_maze();
  return 0;
}
