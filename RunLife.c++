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

using namespace std;

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


void life_parser(istream& r, ostream& w)
{
    string s;
    int first = 0;
    while (getline(r, s)) {
        string cellType = s;

        num_rows = life_read_int(r, w);
        num_cols = life_read_int(r, w);
        num_evols = life_read_int(r, w);
        freq = life_read_int(r, w);

        bool start = true;
        
        //construct Life 
        if (cellType == "ConwayCell")
        {
            if(first==0) {
                cout << "*** Life<ConwayCell> " << num_rows << "x" << num_cols << " ***" << endl;

            }
            else {
                cout<<endl << "*** Life<ConwayCell> " << num_rows << "x" << num_cols << " ***" << endl;
            }
            //cout << "*** Life<ConwayCell> " << num_rows << "x" << num_cols << " ***" << endl;
            Life<ConwayCell> life(num_rows, num_cols, r, w);

            life.runBoard(num_evols, freq, start);    
            getline(r,s);
            first++;

        }
        else if (cellType == "FredkinCell")
        {
            if(first==0) {
                cout << "*** Life<FredkinCell> " << num_rows << "x" << num_cols << " ***" << endl;

            }
            else {
                cout<<endl << "*** Life<FredkinCell> " << num_rows << "x" << num_cols << " ***" << endl;
            }
            first++;
            //cout << "*** Life<FredkinCell> " << num_rows << "x" << num_cols << " ***" << endl;
            Life<FredkinCell> life(num_rows, num_cols, r, w);

            life.runBoard(num_evols, freq, start);
            getline(r,s);
            first++;
        }
        else
        {
            if(first==0) {
                cout << "*** Life<Cell> " << num_rows << "x" << num_cols << " ***" << endl;

            }
            else {
                cout<<endl << "*** Life<Cell> " << num_rows << "x" << num_cols << " ***" << endl;
            }
            first++;
            //cout << "*** Life<Cell> " << num_rows << "x" << num_cols << " ***" << endl;
            Life<Cell> life(num_rows, num_cols, r, w);
 
            life.runBoard(num_evols, freq, start);
            getline(r,s);
            first++;
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
