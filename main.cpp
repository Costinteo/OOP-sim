#include <vector>
#include "Individual.h"
#include "Cell.h"
#include <iostream>
#include <algorithm>

std::vector<Individual> allmembers;

int main() {
    Grid grid;

    for (int y = 0; y < GRID_HEIGHT; y++) {
        std::vector<Cell *> row;
        grid.push_back(row);
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid.at(y).push_back(new Cell(x, y, &grid));
        }
    }


    int placed = 0;
    while (placed < INDIVIDUALS_NUMBER) {
        int x = rand() % GRID_WIDTH;
        int y = rand() % GRID_HEIGHT;

        auto cell = grid.at(y).at(x);
        if (cell->IsOccupied()) {
            continue;
        }

        allmembers.emplace_back(&grid, x, y, placed % 2 == 0 ? '+' : '0');
        grid.at(y).at(x)->SetOccupied(true);
        placed++;
    }

    // Update the individuals
    for (int i = 0; i < CYCLES; i++) {
        for (auto &member : allmembers) {
            member.Update();
        }
        std::cout << allmembers.size() << " alive" << std::endl;
    }

    std::cout << "Simulation Over";
}
