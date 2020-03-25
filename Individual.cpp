#include "Individual.h"
#include "Cell.h"
#include "Defines.h"
#include <cmath>
#include <algorithm>


Individual *FindMember(int x, int y) {

    auto member = std::find_if(allmembers.begin(), allmembers.end(), [&](const Individual &member) {

        return member.GetX() == x && member.GetY() == y;

    });

    return &(*member);
}


Individual::Individual(Grid *grid, int x, int y, char type) {

    this->grid = grid;
    this->x = x;
    this->y = y;
    this->type = type;
    this->age = STARTING_AGE;
    this->energy = rand() % MAX_ENERGY / 10 + 1;
    this->alive = true;


}

void Individual::Feed() {

    int sum = 0;

    for (int i = 0; i < 4; i++) {
        int x = this->x + directions_x[i];
        int y = this->y + directions_y[i];
        if (IsInGrid(x, y)) {
            Cell *cell = this->grid->at(y).at(x);
            if (!cell->IsOccupied()) {
                sum += cell->GetEnergy();
            }
        }
    }

    // parabola w/ vertex(x=50, y=10)
    // ( (-0.1 * x^2 + 10x) / 25 ) * sum
    this->energy += ((pow(this->age, 2) * (-0.1) + 10 * this->age) / 25) * sum;

    if (this->energy > MAX_ENERGY) {
        this->energy = MAX_ENERGY;
    }

}

void Individual::Multiply() {

    int sons = 0;

    if (this->energy < MAX_ENERGY / 4) {
        sons = 1;
    } else if (this->energy < MAX_ENERGY / 2) {
        sons = 2;
    } else if (this->energy < 3 * MAX_ENERGY / 4) {
        sons = 3;
    } else {
        sons = 4;
    }

    for (int i = 0; i < 4; i++) {
        int x = this->x + directions_x[i];
        int y = this->y + directions_y[i];
        if (IsInGrid(x, y)) {
            Cell *cell = this->grid->at(y).at(x);
            if (!cell->IsOccupied() and sons and this->energy > MULTIPLY_COST) {
                sons--;
                allmembers.emplace_back(grid, x, y, this->type);
                grid->at(y).at(x)->SetOccupied(true);
                this->energy -= MULTIPLY_COST;
            }
        }
    }
}


void Individual::Attack() {

    for (int i = 0; i < 4; i++) {
        int x = this->x + directions_x[i];
        int y = this->y + directions_y[i];
        if (IsInGrid(x, y)) {
            Cell *cell = this->grid->at(y).at(x);
            if (cell->IsOccupied()) {
                Individual *member = FindMember(x, y);

                if (member != nullptr and member->alive and member->type != this->type and
                    member->energy < this->energy) {
                    this->energy = this->energy - member->energy;
                    member->Die();
                }
            }
        }
    }

}

void Individual::Weaken() {

    this->age++;
    this->energy = this->energy - ENERGY_LOSS;
    if (this->age >= MAX_AGE or this->energy <= 0)
        this->Die();

}

void Individual::Die() {

    this->alive = false;
    grid->at(this->y).at(this->x)->SetOccupied(false);

    auto itr = std::remove_if(allmembers.begin(), allmembers.end(), [](const auto &i) {
        return !i.IsAlive();
    });

    allmembers.erase(itr, allmembers.end());
}

void Individual::Update() {

    if (this->alive) {
        this->Feed();
        this->Multiply();
        this->Attack();
        this->Weaken();
    }

}