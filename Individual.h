#pragma once

#include <iostream>
#include <random>
#include "Cell.h"

class Individual;

extern std::vector<Individual> allmembers;

class Individual {
private:
    int x, y;
    char type;
    int age;
    double energy;
    bool alive;
    Grid *grid;

    void Feed();
    void Multiply();
    void Attack();
    void Weaken();
    void Die();

public:
    Individual();
    Individual(Grid *grid, int x, int y, char type);
    void Update();

    int GetX() const{
        return this->x;
    }
    int GetY() const{
        return this->y;
    }
    int GetEnergy() const{
        return this->energy;
    }
    bool IsAlive() const {
        return this->alive;
    }
};