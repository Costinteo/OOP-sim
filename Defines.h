#pragma once

#define MAX_AGE 100
#define STARTING_AGE 1
#define MAX_ENERGY 300
#define GRID_WIDTH 20
#define GRID_HEIGHT 70
#define ENERGY_LOSS 5
#define MULTIPLY_COST 25
#define INDIVIDUALS_NUMBER 100
#define CYCLES 100

static int directions_x[4] = {0, 1, 0, -1};
static int directions_y[4] = {-1, 0, 1, 0};

inline bool IsInGrid(int x, int y) {

    if (x < 0 || y < 0) {
        return false;
    }

    if (y >= GRID_HEIGHT) {
        return false;
    }

    if (x >= GRID_WIDTH) {
        return false;
    }

    return true;
}

