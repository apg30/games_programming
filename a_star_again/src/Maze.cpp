#include "Maze.h"
#include <iostream>

Maze::Maze(){

};
Maze::~Maze(){};

/*
void Maze::generate_maze(int obstacles[20][20])
{
  int no_of_obstacles = 0;

  for (int i =0; i < ROWS; i++)
  {
    for (int j=0; j < COLUMNS; j++)
    {
    //  if(!cells[i][j].start && !cells[i][j].end)
  //    {
        if((rand() % 100) > 80)
        {
          cells[j][i].obstacle = true;
          std::cout << "created obstacle at x:" << j << "y:" << j << std::endl;
          no_of_obstacles++;
          obstacles[j][i] = 1;

        }
        else
        {
          cells[j][i].obstacle = false;
        }
  //    }
    }
  }
  if (no_of_obstacles < 80)
  {
    generate_maze(obstacles);
  }
  std::cout << "There are " << no_of_obstacles << " obstacles in this 20x20 grid"<<std::endl;
}
*/

void Maze::print_maze(int obstacles[20][20],std::pair<int,int> start_position,std::pair<int,int> end_position)
{
  //Setup writing
  for (int j=0; j < COLUMNS; j++)
  {
    if (j ==0){
      std::cout << " ";
    }
    std::cout << " " << (j % 10) << " ";
    if (j ==19){
      std::cout << std::endl;
    }
  }

  for (int i =0; i < ROWS; i++)
  {
    std::cout <<  (i % 10);
    for (int j=0; j < COLUMNS; j++)
    {
      if (i == start_position.first && j==start_position.second){
        std::cout << " S ";
      }
      else if (i == end_position.first && j==end_position.second){
        std::cout << " E ";
      }   else

     if (obstacles[i][j] == 1)
      {
        std::cout << " X ";
      }
      else
      {
        std::cout << " . ";
      }
    }
    std::cout << std::endl;
  }
}

std::pair<int,int> Maze::select_start_position()
{
  // Select start position
  int start_x;
  int start_y;
  std::cout << "Select the start position" << std::endl;
  std::cout << "Please select the x axis" << std::endl;
  std::cin >> start_x;
  std::cout << "Please select the y axis" << std::endl;
  std::cin >> start_y;

//  reset_properties(cells[start_row -1][start_column -1]);
//  cells[start_row -1][start_column -1].start = true;

  return std::make_pair(start_x, start_y);
}

std::pair<int,int> Maze::select_end_position()
{
  // Select end position
  // Select start position
  int end_x;
  int end_y;
  std::cout << "Select the end position" << std::endl;
  std::cout << "Please select the x axis" << std::endl;
  std::cin >> end_x;
  std::cout << "Please select the y axis" << std::endl;
  std::cin >> end_y;
//  reset_properties(cells[end_row -1][end_column -1]);
//  cells[end_row -1][end_column -1].end = true;
  std::cout << std::endl;

//  return cells[end_row][end_column];
  return std::make_pair(end_x, end_y);
}

void Maze::reset_properties(Cell cell_to_reset)
{
//  cell_to_reset.start =false;
//  cell_to_reset.end = false;
  cell_to_reset.obstacle = false;
}
