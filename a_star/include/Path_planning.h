#ifndef PATH_PLANNING_H
#define PATH_PLANNING_H

#include <vector>
#include "vec3.h"

class Path_planning
{
public:
  Path_planning(void);
  ~Path_planning(void);

   void find_path(vec3 current_pos, vec3 target_pos);
   vec3 next_path_pos();
   void clear_open_list(){ open_list.clear();}
   void clear_visited_list() {visited_list.clear();}
   void clear_path_to_goal() {path_to_goal.clear();}

   bool start_to_end_init;
   bool goal_found;

}

#endif
