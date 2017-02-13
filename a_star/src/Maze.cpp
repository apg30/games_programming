#include "Maze.h"
#include <iostream>

Maze::Maze(){
  generate_maze();
  print_maze();
};
Maze::~Maze(){};

void Maze::generate_maze()
{
  for (int i =0; i < ROWS; i++)
  {
    for (int j=0; j < COLUMNS; j++)
    {
      if((rand() % 100) > 80){
      cells[i][j].obstacle = true;
      }else
      {
        cells[i][j].obstacle = false;
      }
    }
  }
}

void Maze::print_maze()
{
  for (int i =0; i < ROWS; i++)
  {
    for (int j=0; j < COLUMNS; j++)
    {
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
