
#include "Path_planning.h"
#include <glm/glm.hpp>


int main()
{
  Path_planning planner;
  planner.find_path(2,2,13,13);
  return 0;
}
