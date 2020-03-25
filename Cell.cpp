#include "Cell.h"
#include "Defines.h"

Cell::Cell(int x, int y, Grid *grid) {

    this->x = x;
    this->y = y;
    this->grid = grid;
    this->occupied = false;
}

int Cell::GetEnergy() {

    int sum = 1;

    for (int i = 0; i < 4; i++) {
        int x = this->x + directions_x[i];
        int y = this->y + directions_y[i];
        if (IsInGrid(x, y)) {
            Cell *cell = this->grid->at(y).at(x);
            if (!cell->IsOccupied()) {
                sum += 1;
            }
        }

    }

    return sum;
}