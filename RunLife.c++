// -----------------------------
// projects/life/RunLife.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <sstream>  // istringstream
#include <string>   // getline, string

#include "Life.h"

string type;
int num_rows;
int num_cols;
int num_evols;
int freq;

void life_parser(istream& r, ostream& w)
{
    while (getline(r, s)) {
        if (s.equals("ConwayCell"))
        {
            Life<ConwayCell> life;
        }
        else if (s.equals("FredkinCell"))
        {
            Life<FredkinCell> life;
        }
        else
        {
            Life<Cell> life; //Cell::Cell(char c) takes care of this case 
        }

        getline(r,s);
        istringstream sin(s);
        sin >> num_rows;
        getline(r,s);
        istringstream sin(s);
        sin >> num_cols;
        getline(r,s);
        istringstream sin(s);
        sin >> num_evols;
        getline(r,s);
        istringstream sin(s);
        sin >> freq;

        life = Life(num_rows,num_cols);

        for (int i = 0; i < num_rows; i++)
        {
            getline(r,s);
            char* gridline = (char*) s;
            int j = 0;
            for (char c : gridline)
            {
                if (c == '.')
                {
                    life.addCell(ConwayCell(0),i,j);
                }
                if (c == '-')
                {
                    life.addCell(FredkinCell(0),i,j);
                }
                if (c == '*')
                {
                    life.addCell(ConwayCell(1)),i,j);
                }
                if (c == '0')
                {
                    life.addCell(FredkinCell(1),i,j);
                }
                j += 1;
            }
        }
        runBoard(life);
        getline(r,s);
    }
}

void runBoard(Life life)
{
    for (int i = 0; i < num_evols; i++)
    {
        life.executeTurn();
        if (i % freq == 0)
        {
            life.printBoard();
        }
    }
}

// ----
// main
// ----

int main () {
    using namespace std;
    life_parser(cin, cout);
    return 0;}
