

#include "Maze.h"
#include <vector>




int main()
{
  Maze maze;
  maze.generate_maze();
  maze.print_maze();
  Cell start_position = maze.select_start_position();
  Cell end_position = maze.select_end_position();
  maze.print_maze();

  a_star(start_position,end_position);

  return 0;
}
