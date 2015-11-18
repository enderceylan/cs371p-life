#ifndef Life_h
#define Life_h

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <cstdlib>  // rand
#include <map>
#include <cstring>
#include <vector>
#include "gtest/gtest_prod.h"
using namespace std;

// class Cell;
// class AbstractCell;
// class ConwayCell;
// class FredkinCell;
// class Life;



class AbstractCell
{
    public:
        //AbstractCell();

        virtual void updateStatus(int neighbors) = 0;
        //virtual std::ostream& operator<<(std::ostream& out) = 0;
        virtual operator int(); //going to access age for FredkinCell
        virtual operator bool(); //going to access alive for Conway/Fredkin
        virtual const int numOfNeighbors() const = 0;
        virtual char printCell() = 0;

        virtual AbstractCell* clone() const = 0;
        virtual ~AbstractCell() {};
        //virtual void checkNeighbors() = 0; //
        //bool isValid();
    private:
        bool alive;
        int age; //only need for Fredkin??
        
};

class ConwayCell : public AbstractCell
{
    public:
        //ConwayCell():AbstractCell(){};
        ConwayCell(char c); //construct ConwayCell as you read in input
        ConwayCell(int status);
        void updateStatus(int neighbors);
        const int numOfNeighbors() const;
        char printCell()
        {
            if (alive)
            {
                return '*';
            }
            else
            {
                return '.';
            }
        };
        operator bool();
        AbstractCell* clone() const;
    private:
        bool alive;
        FRIEND_TEST(ConwayTest, constructor_0);
        FRIEND_TEST(ConwayTest, constructor_1);
        FRIEND_TEST(LifeTest, constructor_0);
        FRIEND_TEST(LifeTest, constructor_2);
};

class FredkinCell : public AbstractCell
{
    public:
        //FredkinCell():AbstractCell(){};
        FredkinCell(char c); //construct FredkinCell as you read in input
        FredkinCell(int status);
        void updateStatus(int neighbors);
        const int numOfNeighbors() const;

        operator int();
        operator bool();

        char printCell()
        {
            if (alive)
            {
                if (age < 10)
                {
                    return (char)age + '0';
                }
                else
                {
                    return '+';
                }
            }
            else
            {
                return '-';
            }
        };
        AbstractCell* clone() const;
    private:
        bool alive;
        int age;
        FRIEND_TEST(FredkinTest, constructor_0);
        FRIEND_TEST(FredkinTest, constructor_1);
        FRIEND_TEST(LifeTest, constructor_1);
        FRIEND_TEST(LifeTest, constructor_2);
};

class Cell
{
    private:
        AbstractCell *p;
        FRIEND_TEST(CellTest, constructor_0);
        FRIEND_TEST(CellTest, constructor_1);
        FRIEND_TEST(CellTest, constructor_2);
        FRIEND_TEST(CellTest, constructor_3);
        FRIEND_TEST(LifeTest, constructor_2);
    public:
        //Cell() : p(FredkinCell()) {};
        Cell(char c);
        
        Cell(const Cell&);
        Cell& operator = (Cell);
        ~Cell();

        //AbstractCell* operator->() {return p;};
        void updateStatus(int neighbors); //one turn for a cell
        operator int();
        operator bool();

        char printCell() {
            return p->printCell();
        }


};

template<typename T>
class Life
{
    public:
        //Life(int x, int y);
        Life(int num_rows, int num_cols, istream& r, ostream& w);
        //void addCell(T t, int x, int y);
        //void addCellsToGrid(istream& r, ostream& w, int num_rows);
        T* begin(void);
        T* end(void);
        T& at(int x, int y);
        T& at(int i);
        void executeTurn(void);
        void removeCell(int x, int y);
        void runBoard(int num_evols, int freq);
        void printBoard(void);
        bool inBounds(int x);
        int countNeighbors(T& cell);
        bool isAlive(int n, int i);

    private:
        std::vector<T> grid;
        int x_size;
        int y_size;
        int generation;
        int population;
        FRIEND_TEST(LifeTest, constructor_0);
        FRIEND_TEST(LifeTest, constructor_1);
        FRIEND_TEST(LifeTest, constructor_2);
};

template<typename T>
Life<T>::Life(int num_rows, int num_cols, istream& r, ostream& w)
{
    string s;
    x_size = num_rows;
    y_size = num_cols;
    generation = 0;
    population = 0;

    for (int i = 0; i < num_rows; i++)
    {
        getline(r,s);
        //char* gridline = (char*) s;
        //int j = 0;
        for (char& c : s)
        {
            if(c != '.' && c != '-') {
                population++;
            }
            grid.push_back(T(c));
            //j += 1;
        }
    }
}

template<typename T>
void Life<T>::removeCell(int x, int y)
{
    grid[x*x_size + y] = T();
}

template<typename T>
T* Life<T>::begin()
{
    return &grid[0];
}

template<typename T>
T* Life<T>::end()
{
    return &grid[x_size*y_size];
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

template<typename T>
void Life<T>::executeTurn(void)
{
    int popcount = 0;
    for (int i = 0; i < x_size*y_size; i++)
    {
        grid[i].updateStatus(countNeighbors(at(i)));
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

template<typename T>
void Life<T>::printBoard(void)
{
    cout << "Generation = " << generation << ", Population = " << population << "." << endl;
    for (int k = 0; k < x_size; k++)
    {
        for (int j = 0; j < y_size; j++)
        {
            cout << at(k,j).printCell();
        }
        cout << endl;
    }
    cout << endl;
}

template<typename T>
bool Life<T>::inBounds(int i)
{
    int x = i / x_size;
    int y = i % x_size;
    if (x >= x_size || x < 0 || y >= y_size || y < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}



#endif