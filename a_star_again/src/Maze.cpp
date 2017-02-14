#include "Maze.h"
#include <iostream>

Maze::Maze(){

};
Maze::~Maze(){};

void Maze::generate_maze()
{
  int no_of_obstacles = 0;

  for (int i =0; i < ROWS; i++)
  {
    for (int j=0; j < COLUMNS; j++)
    {
    //  if(!cells[i][j].start && !cells[i][j].end)
  //    {
        if((rand() % 100) > 80){
        cells[i][j].obstacle = true;
        no_of_obstacles++;
        }else
        {
          cells[i][j].obstacle = false;
        }
  //    }
    }
  }
  if (no_of_obstacles < 80)
  {
    generate_maze();
  }
  std::cout << "There are " << no_of_obstacles << " obstacles in this 20x20 grid"<<std::endl;
}

void Maze::print_maze()
{
  for (int i =0; i < ROWS; i++)
  {
    for (int j=0; j < COLUMNS; j++)
    {
/*      if (cells[i][j].start){
        std::cout << " S ";
      }
      else if (cells[i][j].end){
        std::cout << " E ";
      }   else*/
     if (cells[i][j].obstacle)
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
  int start_row;
  int start_column;
  std::cout << "Select the start position" << std::endl;
  std::cout << "Please select the x axis" << std::endl;
  std::cin >> start_column;
  std::cout << "Please select the y axis" << std::endl;
  std::cin >> start_row;

  reset_properties(cells[start_row -1][start_column -1]);
//  cells[start_row -1][start_column -1].start = true;

  return std::make_pair(start_row, start_column);
}

std::pair<int,int> Maze::select_end_position()
{
  // Select end position
  // Select start position
  int end_row;
  int end_column;
  std::cout << "Select the end position" << std::endl;
  std::cout << "Please select the x axis" << std::endl;
  std::cin >> end_column;
  std::cout << "Please select the y axis" << std::endl;
  std::cin >> end_row;
  reset_properties(cells[end_row -1][end_column -1]);
//  cells[end_row -1][end_column -1].end = true;
  std::cout << std::endl;

//  return cells[end_row][end_column];
  return std::make_pair(end_row, end_column);
}

void Maze::reset_properties(Cell cell_to_reset)
{
//  cell_to_reset.start =false;
//  cell_to_reset.end = false;
  cell_to_reset.obstacle = false;
}
