#include "Maze.h"
#include <iostream>

Maze::Maze(){
  for (int i =0; i < ROWS; i++)
  {
    for (int j=0; j < COLUMNS; j++)
    {
      cells[i][j].start =false;
      cells[i][j].end = false;
      cells[i][j].obstacle = false;
      cells[i][j].visited = false;
    }
  }
};
Maze::~Maze(){};

void Maze::generate_maze()
{
  for (int i =0; i < ROWS; i++)
  {
    for (int j=0; j < COLUMNS; j++)
    {
      if(!cells[i][j].start && !cells[i][j].end)
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
}

void Maze::print_maze()
{
  for (int i =0; i < ROWS; i++)
  {
    for (int j=0; j < COLUMNS; j++)
    {
      if (cells[i][j].start){
        std::cout << " S ";
      }
      else if (cells[i][j].end){
        std::cout << " E ";
      }
      else if (cells[i][j].obstacle)
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

void Maze::select_positions()
{
  // Select start position
  int start_row;
  int start_column;
  std::cout << "Select the start position" << std::endl;
  std::cout << "x axis" << std::endl;
  std::cin >> start_column;
  std::cout << "y axis" << std::endl;
  std::cin >> start_row;
  reset_properties(cells[start_row -1][start_column -1]);
  cells[start_row -1][start_column -1].start = true;

  // Select end position
  // Select start position
  int end_row;
  int end_column;
  std::cout << "Select the end position" << std::endl;
  std::cout << "x axis" << std::endl;
  std::cin >> end_column;
  std::cout << "y axis" << std::endl;
  std::cin >> end_row;
  reset_properties(cells[end_row -1][end_column -1]);
  cells[end_row -1][end_column -1].end = true;
}

void Maze::reset_properties(Cell cell_to_reset)
{
  cell_to_reset.start =false;
  cell_to_reset.end = false;
  cell_to_reset.obstacle = false;
  cell_to_reset.visited = false;
}
