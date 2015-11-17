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
Life<T>::Life(int x, int y)
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
void Life<T>::addCell(T t, int x, int y)
{
    grid[x*x_size + y] = t;
}
//add individual cells to grid
template<typename T>
void Life<T>::addCellsToGrid(istream& r, ostream& w, int num_rows) {
    string s;
    for (int i = 0; i < num_rows; i++)
    {
        getline(r,s);
        //char* gridline = (char*) s;
        int j = 0;
        for (char& c : s)
        {
            if (c == '.')
            {
                addCell(T(c),i,j);
            }
            if (c == '-')
            {
                addCell(T(c),i,j);
            }
            if (c == '*')
            {
                addCell(T(c),i,j);
            }
            if (c == '0')
            {
                addCell(T(c),i,j);
            }
            j += 1;
        }
    }
}
template<typename T>
void Life<T>::runBoard(int num_evols, int freq) {
    for (int i = 0; i < num_evols; i++)
    {
        executeTurn();
        if (i % freq == 0)
        {
            printBoard();
        }
    }
}

/*
    Darwin::removeCreature(int x, int y)
    Removes a Creature from the grid.
    Input: x and y are the coordinates of the Creature that must be removed.
    Output: n/a
*/
template<typename T>
void Life<T>::removeCell(int x, int y)
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
T* Life<T>::begin()
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
T* Life<T>::end()
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
void Life<T>::executeTurn(void)
{
    int popcount = 0;
    for (int i = 0; i < x_size*y_size; i++)
    {
        grid[i].updateStatus(countNeighbors(i));
        if (isAlive(grid[i].numOfNeighbors(),i))
        {
            popcount += 1;
        }
    }
    generation += 1;
    population = popcount;
}

template <typename T>
int Life<T>::countNeighbors(T& cell) {
    int neighbors = 0;
    int n = cell.numOfNeighbors();
    //vector<NeighborAxis> n_axis = cell.neighborAxis();

    for(int i=0; i<n; i++) {
        //access grid, check if cell is alive and increment neighbors
        if(isAlive(n, i)) {
            neighbors++;
        }
    }

    return neighbors;
}
//determines if neighbor is alive depending on Conway/Fredkin and index
template<typename T>
bool Life<T>::isAlive(int n, int i) {
    //if ConwayCell
    if(n==8) {
        if(i==0) {
            if (inBounds(i-1) && (at(i-1)) == true) {return true;}
        }
        else if(i==1){
            if (inBounds(i+1) && (at(i+1)) == true) {return true;}
        }
        else if(i==2){
            if (inBounds(i-x_size) && (at(i-x_size)) == true) {return true;}
        }
        else if(i==3){
            if (inBounds(i-x_size-1) && (at(i-x_size-1)) == true) {return true;}
        }
        else if(i==4){
            if (inBounds(i-x_size+1) && (at(i-x_size+1)) == true) {return true;}
        }
        else if(i==5){
            if (inBounds(i+x_size) && (at(i+x_size)) == true) {return true;}
        }
        else if(i==6){
            if (inBounds(i+x_size-1) && (at(i+x_size-1)) == true) {return true;}
        }
        else if(i==7){
            if (inBounds(i+x_size+1) && (at(i+x_size+1)) == true) {return true;}
        }
    }
    //if FredkinCell
    else if(n==4) {
        if(i==0){
            if (inBounds(i-1) && (at(i-1)) == true) {return true;}
        }
        if(i==1){
            if (inBounds(i+1) && (at(i+1)) == true) {return true;}
        }
        if(i==2){
            if (inBounds(i-x_size) && (at(i-x_size)) == true) {return true;}
        }
        if(i==3){
            if (inBounds(i+x_size) && (at(i+x_size)) == true) {return true;}
        }
    }
    return false;
}



/*
    Darwin::at(int x, int y)
    Returns the element that is at a specified location in the grid.
    Input: x and y are the coordinates in the grid of the element we want to retrieve.
    Output: Returns the Creature at the specified location.
*/
template<typename T>
T& Life<T>::at(int x, int y)
{
    return grid[x_size*x + y];
}
template<typename T>
T& Life<T>::at(int i)
{
    return grid[i];
}

/*
    Darwin::printBoard()
    Prints the current status of the grid.
    Input: n/a
    Output: n/a
*/
template<typename T>
void Life<T>::printBoard(void)
{
    cout << "Generation = " << generation << ", Population = " << population << "." << endl;
    for (int k = 0; k < x_size; k++)
    {
        for (int j = 0; j < y_size; j++)
        {
            cout << at(k,j);
        }
        cout << endl;
    }
    cout << endl;
}

/*
    Darwin::inBounds(int x, int y)
    Checks to see whether the given location is within the bounds of the grid.
    Input: x and y are the coordinates of the location we want to check.
    Output: Returns true is location is valid, false otherwise.
*/
template<typename T>
bool Life<T>::inBounds(int x, int y)
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


AbstractCell::operator int() {
    return 0;
}
AbstractCell::operator bool() {
    return false;
}







//constructor for Cell creates new ConwayCell or FredkinCell depending on input
Cell::Cell(char c) {
    if(c=='.' || c=='*')
        p = new ConwayCell(c);
    else
        p = new FredkinCell(c);
}
// //copy constructor
// Cell::Cell(const Cell& c) {
//     if(!c.p)
//         p = 0;
//     else
//         p = c.p->clone();
// }
// //copy assignment
// Cell& Cell::operator = (Cell c) {
//     swap(p, c.p);
//     return *this;
// }
// //destructor
// Cell::~Cell() {
//     delete p;
// }

//modify state of Cell on a turn after neighbors have been set
void Cell::updateStatus(int neighbors) {
    //p->updateStatus();
    //set to ConwayCell if age is 2
    if(*p == 2) {
        delete p; 
        p = new ConwayCell('*');
    }
}


//convert Cell to int. (returns age for Fredkin)
Cell::operator int() {
    return *p;
}
//convert Cell to bool. (returns alive for Fredkin/Conway)
Cell::operator bool() {
    return *p;
}









//construct ConwayCell depending on input
ConwayCell::ConwayCell(char c) {
    if(c=='.') {
        alive = false;
    }
    else if(c=='*') {
        alive = true;
    }
}

//ConwayCell turn(). sets alive after counting neigbhors
void ConwayCell::updateStatus(int neighbors) {
    if (alive == false && neighbors == 3)
    {
        alive = true;
    }
    if (alive == true && (neighbors < 2 || neighbors > 3))
    {
        alive = false;
    }
}
//return number of neighbors for ConwayCell
const int ConwayCell::numOfNeighbors() const {
    //would have to determine if in corner, edge, or middle
    return 8;
}
//ConwayCell returns alive when converted to bool
ConwayCell::operator bool() {
    return alive;
}

// AbstractCell* ConwayCell::clone() const {
//     return new ConwayCell(*this);
// }



//construct FredkinCell depending on input
FredkinCell::FredkinCell(char c) {
    if(c=='-')
        alive = false;
    else {
        alive = true;
        age = c - '0';
    }
}
//FredkinCell turn(). sets alive and age after counting neighbors
void FredkinCell::updateStatus(int neighbors) {
    if (alive == false && neighbors % 2 == 1)
    {
        alive = true;
    }
    if (alive == true && neighbors % 2 == 0)
    {
        alive = false;
    }
    if (alive == true)
    {
        age += 1;
    }
}
//FredkinCell returns age when converted to int. 
FredkinCell::operator int() {
    return age;
}
//FredkinCell returns alive when converted to bool
FredkinCell::operator bool() {
    return alive;
}
//return number of of neighbors for FredkinCell
const int FredkinCell::numOfNeighbors() const {
    //determine if in corner, edge, or middle
    return 4; 
}

// AbstractCell* FredkinCell::clone() const {
//     return new FredkinCell(*this);
// }