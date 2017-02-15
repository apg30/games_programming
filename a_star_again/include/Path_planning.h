#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H

#include <vector>
#include <glm/glm.hpp>
#include "Maze.h"

#include "Cell.h"

class Path_planning
{
public:
  Path_planning(void);
  ~Path_planning(void);

   Maze maze;
   void setup();
   void find_path(int start_x, int start_y, int end_x, int end_y);
   glm::vec3 next_path_pos();
   void clear_open_list(){ open_list.clear();}
   void clear_visited_list() {visited_list.clear();}
   void clear_path_to_goal() {path_to_goal.clear();}

   bool initialized_start_to_end;
   bool goal_found;

private:
  void set_start_and_goal(Cell start, Cell end);
  void path_opened(int x, int z, float new_cost, Cell * parent);
  Cell *get_next_cell();
  void continue_path();

  Cell *start_cell;
  Cell *goal_cell;
  std::vector<Cell*> open_list;
  std::vector<Cell*> visited_list;
  int   obstacles[20][20] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
  std::vector<std::pair<int,int>> path_to_goal;

};
#endif
