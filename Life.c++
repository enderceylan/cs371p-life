// ----------------------------
// projects/life/Life.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_std::pair, std::pair
#include <cstdlib>  // rand
#include <map>
#include <cstring>
#include <vector>

#include "Life.h"

using namespace std;


// IMPLEMENTATIONS FOR LIFE CLASS

/*
    Darwin::Darwin(int x, int y)
    Constructor for Darwin class. Initializes variables and full grid.
    Input: x is the height of the grid. y is the width of the grid.
    Output: n/a
*/
template<typename T>
Life::Life(int x, int y)
{
    x_size = x;
    y_size = y;
    generation = 0;
    population = 0;
    for (int i = 0; i < x_size*y_size; i++)
    {
        grid.push_back(new T());
    }
}

/*
    Darwin::addCreature(Creature c, int x, int y)
    Places a new Creature onto the grid.
    Input: c is the Creature to be placed on the grid. x and y are the coordinates
    where c will be placed.
    Output: n/a
*/
template<typename T>
void Life::addCell(T t, int x, int y)
{
    grid[x*x_size + y] = t;
}

/*
    Darwin::removeCreature(int x, int y)
    Removes a Creature from the grid.
    Input: x and y are the coordinates of the Creature that must be removed.
    Output: n/a
*/
template<typename T>
void Life::removeCell(int x, int y)
{
    grid[x*x_size + y] = T();
}

/*
    Darwin::begin()
    Outputs the first element of the grid.
    Input: n/a
    Output: Returns the first element of the grid.
*/
template<typename T>
T* Life::begin()
{
    return &grid[0];
}

/*
    Darwin::end()
    Outputs the end of the grid.
    Input: n/a
    Output: Returns the end of the grid.
*/
template<typename T>
T* Life::end()
{
    return &grid[x_size*y_size];
}

/*
    Darwin::executeTurn()
    Cycles through the entire grid and executes an instruction for each Creature in
    the grid, going from left to right, and from top to bottom.
    Input: n/a
    Output: n/a
*/
template<typename T>
void Life::executeTurn(void)
{
    for (int i = 0; i < x_size*y_size; i++)
    {
        if (!grid[i].acted_upon(turn)) {
            grid[i].updateStatus(getNeighbors(i));
        }
    }
    generation += 1;
}

int Life::getNeighbors(int i)
{
    int neighbors = 0;
    if (ConwayCell * p = dynamic_cast<ConwayCell*>(&at(i)))
    {
        if (inBounds(i-1) && (<< at(i-1)) == '*') {neighbors += 1;}
        if (inBounds(i+1) && (<< at(i+1)) == '*') {neighbors += 1;}
        if (inBounds(i-x_size) && (<< at(i-x_size)) == '*') {neighbors += 1;}
        if (inBounds(i-x_size-1) && (<< at(i-x_size-1)) == '*') {neighbors += 1;}
        if (inBounds(i-x_size+1) && (<< at(i-x_size+1)) == '*') {neighbors += 1;}
        if (inBounds(i+x_size) && (<< at(i+x_size)) == '*') {neighbors += 1;}
        if (inBounds(i+x_size-1) && (<< at(i+x_size-1)) == '*') {neighbors += 1;}
        if (inBounds(i+x_size+1) && (<< at(i+x_size+1)) == '*') {neighbors += 1;}
    }
    else if (FredkinCell * p = dynamic_cast<FredkinCell*>(&at(i)))
    {
        if (inBounds(i-1) && (<< at(i-1)) != '*' && (<< at(i-1)) != '.' && (<< at(i-1)) != '-') {neighbors += 1;}
        if (inBounds(i+1) && (<< at(i-1)) != '*' && (<< at(i-1)) != '.' && (<< at(i-1)) != '-') {neighbors += 1;}
        if (inBounds(i-x_size) && (<< at(i-1)) != '*' && (<< at(i-1)) != '.' && (<< at(i-1)) != '-') {neighbors += 1;}
        if (inBounds(i+x_size) && (<< at(i-1)) != '*' && (<< at(i-1)) != '.' && (<< at(i-1)) != '-') {neighbors += 1;}
    }
    return neighbors;
}

/*
    Darwin::at(int x, int y)
    Returns the element that is at a specified location in the grid.
    Input: x and y are the coordinates in the grid of the element we want to retrieve.
    Output: Returns the Creature at the specified location.
*/
Creature& Life::at(int x, int y)
{
    return grid[x_size*x + y];
}
Creature& Life::at(int i)
{
    return grid[i];
}

/*
    Darwin::printBoard()
    Prints the current status of the grid.
    Input: n/a
    Output: n/a
*/
void Life::printBoard(void)
{
    cout << "Generation = " << generation << ", Population = " << population << "." << endl;
    for (int k = 0; k < x_size; k++)
    {
        for (int j = 0; j < y_size; j++)
        {
            if (!grid[k][j].isValid())
            {
                cout << ".";
            }
            else
            {
                cout << grid[k*x_size + j];
            }
        }
        cout << endl;
    }
}

/*
    Darwin::inBounds(int x, int y)
    Checks to see whether the given location is within the bounds of the grid.
    Input: x and y are the coordinates of the location we want to check.
    Output: Returns true is location is valid, false otherwise.
*/
bool Life::inBounds(int x, int y)
{
    if (x >= x_size || x < 0 || y >= y_size || y < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


// IMPLEMENTATIONS FOR ABSTRACTCELL CLASS

/*
    Creature::Creature()
    Empty constructor for Creature class. Should be used to represent blank spaces.
    Input: n/a
    Output: n/a
*/
Creature::Creature(void)
{
    species = Species();
    direction = -1;
    program_counter = -1;
    turn_counter = -1;
}

/*
    Creature::Creature(Species s, int dir)
    Regular constructor for Creature that initializes variables.
    Input: s is the Creature's Species. dir is the Creature's direction.
    Output: n/a
*/
Creature::Creature(Species s, int dir)
{
    species = s;
    direction = dir;  //0:west, 1:north, 2:east, 3:south.
    program_counter = 0;
    turn_counter = 0;
}

/*
    Creature::acted_upon(int turn)
    Checks to see if the Creature has already fully executed its turn.
    Input: turn is the current turn on the grid.
    Output: Returns true if Creature has already acted on its turn, false otherwise.
*/
bool AbstractCell::acted_upon(int gen) {
    if (age <= gen) {
        return false;
    }
    else {
        return true;
    }
}

/*
    Creature::isValid()
    Checks to see if the Creature is not representing a blank space.
    Input: n/a
    Output: Returns true if Creature is not blank space, false otherwise.
*/
bool AbstractCell::isValid()
{
    if (alive){
        return true;
    }
    else {
        return false;
    }
}



// IMPLEMENTATIONS FOR SPECIES CLASS

/*
    Species::Species()
    Empty constructor for Species class. Should be used to represent blank spaces.
    Input: n/a
    Output: n/a
*/
Species::Species(void)
{
    symbol = '.';
    program = {};
}

/*
    Species::Species(const Species& s)
    Copy constructor for Species class. Should be used to peform a deep copy on Species.
    Input: s is the Species to be copied.
    Output: n/a
*/
Species::Species (const Species& s) {
    program = s.program;
    symbol = s.symbol;
}

/*
    Species::Species(char c)
    Regular constructor for Species that initializes variables.
    Input: c is the character that will represent the Species on the grid.
    Output: n/a
*/
Species::Species(char c)
{
    symbol = c;
    program = {};
}

/*
    Species::addInstruction(string inst)
    Adds an instruction to the program.
    Input: inst is the instruction to be added to the program.
    Output: n/a
*/
void Species::addInstruction(string inst)
{
    program.push_back(inst);
}

/*
    Species::operator[] (int x)
    Indexing operator for Species program.
    Input: x is the number of the instruction to be retrieved.
    Output: Returns the requested instruction from the program.
*/
string& Species::operator[] (int x)
{
    return program[x];
}

/*
    Species::is_equal(const Species& other)
    Checks to see if two instances of Species are of equal types.
    Input: other is the other instance of Species to be compared.
    Output: Returns true if they are of the same type, false
*/
bool Species::is_equal(const Species& other) const{
    return symbol == other.symbol;
}