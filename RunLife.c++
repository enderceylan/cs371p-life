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

//used to read inputs 
int life_read_int (istream& r, ostream& w) {
    string s;
    getline(r, s);
    istringstream sin(s);
    int i; 
    sin >> i;

    return i;
}

// void runBoard(Life life)
// {
//     for (int i = 0; i < num_evols; i++)
//     {
//         life.executeTurn();
//         if (i % freq == 0)
//         {
//             life.printBoard();
//         }
//     }
// }

void life_parser(istream& r, ostream& w)
{
    string s;
    while (getline(r, s)) {
        string cellType = s;
        /*
        if (s == "ConwayCell")
        {
            Life<ConwayCell> life;
        }
        else if (s == "FredkinCell")
        {
            Life<FredkinCell> life;
        }
        else
        {
            Life<Cell> life; //Cell::Cell(char c) takes care of this case 
        }
        */

        num_rows = life_read_int(r, w);
        num_cols = life_read_int(r, w);
        num_evols = life_read_int(r, w);
        freq = life_read_int(r, w);

        // getline(r,s);
        // istringstream sin(s);
        // sin >> num_rows;
        // getline(r,s);
        // istringstream sin(s);
        // sin >> num_cols;
        // getline(r,s);
        // istringstream sin(s);
        // sin >> num_evols;
        // getline(r,s);
        // istringstream sin(s);
        // sin >> freq;

        //life = Life(num_rows,num_cols);
        
        //construct Life 
        if (cellType == "ConwayCell")
        {
            //Life<ConwayCell> life = Life<ConwayCell>(num_rows, num_cols);
            Life<ConwayCell> life(num_rows, num_cols);
            //add cells to grid
            life.addCellsToGrid(r, w, num_rows);
            //runBoard(life);
            life.runBoard(num_evols, freq);    
            getline(r,s);

        }
        else if (cellType == "FredkinCell")
        {
            //Life<FredkinCell> life = Life<FredkinCell>(num_rows, num_cols);
            //add cells to grid
            //life.addCellsToGrid(r, w, num_rows);
            //runBoard(life);
            //life.runBoard(num_evols, freq);
            getline(r,s);
        }
        else
        {
            //Life<Cell> life = Life<Cell>(num_rows, num_cols); //Cell::Cell(char c) takes care of this case 
            //add cells to grid 
            //life.addCellsToGrid(r, w, num_rows);
            //runBoard(life);
            //life.runBoard(num_evols, freq);
            getline(r,s);
        }


        // for (int i = 0; i < num_rows; i++)
        // {
        //     getline(r,s);
        //     //char* gridline = (char*) s;
        //     int j = 0;
        //     for (char& c : s)
        //     {
        //         if (c == '.')
        //         {
        //             life.addCell(ConwayCell(0),i,j);
        //         }
        //         if (c == '-')
        //         {
        //             life.addCell(FredkinCell(0),i,j);
        //         }
        //         if (c == '*')
        //         {
        //             life.addCell(ConwayCell(1)),i,j);
        //         }
        //         if (c == '0')
        //         {
        //             life.addCell(FredkinCell(1),i,j);
        //         }
        //         j += 1;
        //     }
        // }
        



        // runBoard(life);
        // getline(r,s);
    }
}

// ----
// main
// ----

int main () {
    using namespace std;
    life_parser(cin, cout);



    return 0;}
