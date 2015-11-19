
// --------
// includes
// --------
#include "Life.h"

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_std::pair, std::pair
#include <cstdlib>  // rand
#include <map>
#include <cstring>
#include <vector>

using namespace std;



AbstractCell::operator int() {
    return 0;
}
AbstractCell::operator bool() {
    return alive;
}





//constructor for Cell creates new ConwayCell or FredkinCell depending on input
Cell::Cell(char c) {
    if(c=='.' || c=='*')
        p = new ConwayCell(c);
    else
        p = new FredkinCell(c);
}
//copy constructor
Cell::Cell(const Cell& c) {
    if(!c.p)
        p = 0;
    else
        p = c.p->clone();
}
//copy assignment
Cell& Cell::operator = (Cell c) {
    swap(p, c.p);
    return *this;
}
//destructor
Cell::~Cell() {
    delete p;
}

//modify state of Cell on a turn after neighbors have been set
void Cell::updateStatus(int neighbors) {
    p->updateStatus(neighbors);
    //set to ConwayCell if age is 2
    if(*p == 2) {
        delete p; 
        p = new ConwayCell('*');
    }
}
const int Cell::numOfNeighbors() const {
    return p->numOfNeighbors();
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

AbstractCell* ConwayCell::clone() const {
    return new ConwayCell(*this);
}



//construct FredkinCell depending on input
FredkinCell::FredkinCell(char c) {
    if(c=='-') {
        alive = false;
        age = 0;
    }
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
        //age = 0;
    }
    else if (alive == true && neighbors % 2 == 0)
    {
        alive = false;
    }
    else if (alive == true)
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

AbstractCell* FredkinCell::clone() const {
    return new FredkinCell(*this);
}