#ifndef MAZE_H
#define MAZE_H

#define ROWS 20
#define COLUMNS ROWS

struct Cell{
    // Variables
    bool visited;
    bool obstacle;
    bool start;
    bool end;
};

class Maze{
public:

  // Functions
  Maze();
  ~Maze();
  void generate_maze();
  void print_maze();
  void select_positions();
  void reset_properties(Cell cell_to_reset);
  // Variables
  Cell cells[20][20];
};
#endif
