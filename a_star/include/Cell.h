#ifndef CELL_H
#define CELL_H

#include <stdlib.h>

struct Cell{
public:
    // Variables
    int x_coord;
    int y_coord;
  //  int id;
    Cell *parent;
    float g;
    float h;

    bool obstacle;

    Cell() : parent(0){}
    Cell(int x, int y, Cell *_parent =0) : x_coord(x), y_coord(y), parent(_parent),g(0), h(0) {};

    float GetF() { return g + h;}
    float man_distance(Cell *cell){

      float diff_x = (float)(abs(this->x_coord - cell->x_coord));
      float diff_y = (float)(abs(this->y_coord - cell->y_coord));

    		return diff_x + diff_y;
    }
};

#endif
