#pragma once

#include <vector>
#include "Defines.h"


class Cell;

typedef std::vector< std::vector<Cell *> > Grid;


class Cell {
private:
    int x;
    int y;
    Grid *grid;
    bool occupied;

public:

    Cell(int x, int y, Grid *grid);
    int GetEnergy();

    int GetX() {
        return x;
    }

    int GetY() {
        return y;
    }


    bool IsOccupied() {
        return occupied;
    }

    void SetOccupied(bool value) {
        this->occupied = value;
    }



};

