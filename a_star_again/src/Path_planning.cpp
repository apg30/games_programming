#include "Path_planning.h"
#include <iostream>


Path_planning::Path_planning(void)
{
  initialized_start_to_end = false;
  goal_found = false;
}

Path_planning::~Path_planning(void)
{
}

void Path_planning::setup()
{

  maze.generate_maze();
  maze.print_maze();
  std::pair<int,int> start_position = maze.select_start_position();
  std::pair<int,int> end_position = maze.select_end_position();
  maze.print_maze();

  std::cout <<start_position.first <<std::endl;
  std::cout <<start_position.second <<std::endl;
  std::cout <<end_position.first <<std::endl;
  std::cout <<end_position.second <<std::endl;

  find_path(start_position.first, start_position.second,end_position.first,end_position.second);

}

void Path_planning::find_path(int start_x, int start_y, int end_x, int end_y)
{
  if(!initialized_start_to_end)
  {
    for (int i = 0; i < open_list.size(); i++)
    {
      delete open_list[i];
    }
    open_list.clear();
    for (int i =0; visited_list.size(); i++)
    {
      delete visited_list[i];
    }
    visited_list.clear();
    for(int i=0; path_to_goal.size();i++)
    {
      delete path_to_goal[i];
    }
    path_to_goal.clear();

    //define start position
    Cell start;
    start.x_coord = start_x;
    start.y_coord = start_y;

    //define end position.
    Cell goal;
    goal.x_coord = end_x;
    goal.y_coord = end_y;

    //Set the start and end position
    set_start_and_goal(start,goal);
    initialized_start_to_end = true;
  }
  while(initialized_start_to_end)
  {
    continue_path();
  }

}
void Path_planning::set_start_and_goal(Cell start, Cell goal)
{

  //Get the start and end position
  start_cell = new Cell(start.x_coord, start.y_coord, NULL);
  goal_cell = new Cell(goal.x_coord, goal.y_coord, &goal);

  // Put start position in the open list.
  start_cell->g = 0;
  start_cell->h = start_cell->man_distance(goal_cell);
  start_cell->parent = 0;
  open_list.push_back(start_cell);
}

//Main a_star algorthim
void Path_planning::continue_path()
{
  // if nothing in open list return.
  if(open_list.empty())
  {
    return;
  }
  //get the next cell to evaluate.
  Cell * current_cell = get_next_cell();

  //check to see if next cell is the final cell.
  if (current_cell->x_coord == goal_cell->x_coord && current_cell->y_coord == goal_cell->y_coord)
  {
    // Set the parent
    goal_cell->parent = current_cell->parent;

    // Find the shortest path
    Cell* get_path;
    for(get_path = goal_cell; get_path != NULL;get_path = get_path->parent)
    {
        // Get shortest path from goal
        path_to_goal.push_back(new glm::vec3(get_path->x_coord, get_path->y_coord, 0));
        std::cout <<  "coords [" << get_path->x_coord <<  "," << get_path->y_coord <<  "]" << std::endl;
    }

    goal_found = true;
    return;
  }
  else
  {
    //if we have not found the goal yet check the adjacent cells

    //right cell
    path_opened(current_cell->x_coord + 1, current_cell->y_coord, current_cell->g +1, current_cell);
    //left cell
    path_opened(current_cell->x_coord - 1, current_cell->y_coord, current_cell->g +1, current_cell);
    //up cell
    path_opened(current_cell->x_coord, current_cell->y_coord + 1, current_cell->g +1, current_cell);
    //down cell
    path_opened(current_cell->x_coord, current_cell->y_coord -1, current_cell->g +1, current_cell);
    //left-up cell
    path_opened(current_cell->x_coord - 1, current_cell->y_coord +1, current_cell->g +1.41f, current_cell);
    //right-up cell
    path_opened(current_cell->x_coord + 1, current_cell->y_coord +1, current_cell->g +1.41f, current_cell);
    //left-down cell
    path_opened(current_cell->x_coord - 1, current_cell->y_coord -1, current_cell->g +1.41f, current_cell);
    //right-up cell
    path_opened(current_cell->x_coord - 1, current_cell->y_coord -1, current_cell->g +1.41f, current_cell);


    // Remove current cell from the open list now that it has been checked.
    for( int i=0; i<open_list.size(); i++)
    {
      if(current_cell->x_coord == open_list[i]->x_coord && current_cell->y_coord == open_list[i]->y_coord)
      {
        open_list.erase(open_list.begin() + i);
      }
    }

  }

}

// Get the next cell to evaluate.
// find the cell in open_list with the lowest F value.
Cell * Path_planning::get_next_cell()
{
  float bestF = 99999.9f;
  int cell_index = -1;
  Cell* next_cell = NULL;

  for(int i = 0; i < open_list.size(); i++)
  {
    if(open_list[i]->GetF() < bestF)
    {
      bestF = open_list[i] ->GetF();
      cell_index =i;
    }
  }
  if (cell_index >= 0)
  {
    next_cell = open_list[cell_index];
    visited_list.push_back(next_cell);
    open_list.erase(open_list.begin() + cell_index);
  }
  return next_cell;
}

void Path_planning::path_opened(int x, int y, float new_cost, Cell * parent)
{
  // Check if cell has obstacle in it
  if(maze.cells[x][y].obstacle)
  {
    return;
  }

  // Check if the node has already been visited
  for (int i=0; i< visited_list.size();i++)
  {
    if(x == visited_list[i]->x_coord && y == visited_list[i]->y_coord)
    {
      return;
    }
  }
  // If the cell has not already been visited
  // set it to temp variable new_child.
  // calculate its cost and heuristic.
  Cell* new_child = new Cell(x,y,parent);
  new_child->g = new_cost;
  new_child->h = parent->man_distance(goal_cell);

  // Look through open list
  for( int i = 0; i < open_list.size(); i++)
  {
    // Find cell in open list
    if(x == open_list[i]->x_coord && y == open_list[i]->y_coord)
    {
      float newF= new_child->g + new_cost + open_list[i]->h;

      // if newF is smaller than the one in the open_list, we want to replace it
      // with the better one.
      if(open_list[i]->GetF() > newF)
      {
        open_list[i]->g= new_child->g + new_cost;
        open_list[i]->parent= new_child;

      }
      else
      //if f is not better than the old one (parent) then it is not needed anymore.
      //It can be deleted from the open list.
      {
        delete new_child;
        return;
      }
    }
  }
  open_list.push_back(new_child);
}

/*
glm::vec3 Path_planning::next_path_pos()
{
    int index =1;

    glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f);
    float radius = 1;

    glm::vec3 next_pos;
    next_pos.x = path_to_goal[path_to_goal.size() - index]->x;
    next_pos.y = path_to_goal[path_to_goal.size() - index]->y;

    glm::vec3 distance = next_pos - pos;

    if (index < path_to_goal.size())
    {
      if(distance.Length() < radius)
      {
        path_to_goal.erase(path_to_goal.end() - index);
      }
    }

    return next_pos;
}
*/
