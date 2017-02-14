#ifndef CELL_H
#define CELL_H

class Cell{
public:
    // Variables
    int x_coord, y_coord;
    Cell *parent;
    float g;
    float h;

    Cell() : parent(0){}
    Cell(int x, int z, Cell *_parent =0 : x_coord(x), y_coord(y), parent(_parent),g(0), h(0) {};

    float GetF() { return g + h;}
    float man_distance(Cell cell);

    bool start = false;
    bool end = false;
    bool visited = false;
    bool obstacle= false;

    // Functions
    int calculate_g();
    int calculate_h();
    int calculate_f();

    bool operator!=(Cell cell);
};

#endif
