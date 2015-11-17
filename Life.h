#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <cstdlib>  // rand
#include <map>
#include <cstring>
#include <vector>

using namespace std;

class Cell;
class AbstractCell;
class ConwayCell;
class FredkinCell;
class Life<T>;



class AbstractCell
{
    public:
        AbstractCell();
        virtual void updateStatus(int neighbors) {};
        virtual std::ostream& operator<<(std::ostream& out);
        virtual operator int(); //going to access age for FredkinCell
        virtual void turn() = 0; //one turn for cell
        virtual const int numOfNeighbors() const = 0;
        virtual void checkNeighbors() = 0; //
        bool isValid();
    private:
        bool alive;
        //int age; //only need for Fredkin??
    protected: //childs can access protected members
        numberOfNeighbors;
};

class Cell
{
    public:
        Cell() : p(new AbstractCell()) {};
        Cell(char);
        AbstractCell* operator->() {return p;};

        void turn(); //one turn for a cell
        operator int();
    private:
        AbstractCell *p;
};

class ConwayCell : public AbstractCell
{
    public:
        ConwayCell():AbstractCell();
        ConwayCell(char); //construct ConwayCell as you read in input
        ConwayCell(int status);
        void updateStatus(int neighbors);
        friend std::ostream& operator<<(std::ostream& out)
        {
            if (alive)
            {
                return out << '*';
            }
            else
            {
                return out << '.';
            }
        };
};

class FredkinCell : public AbstractCell
{
    public:
        FredkinCell():AbstractCell();
        FredkinCell(char); //construct FredkinCell as you read in input
        FredkinCell(int status);
        void updateStatus(int neighbors);

        operator int();

        friend std::ostream& operator<<(std::ostream& out)
        {
            if (alive)
            {
                return out << age;
            }
            else
            {
                return out << '-';
            }
        };
    
    private:
        int age;

};

template<typename T>
class Life
{
    public:
        Life(int x, int y);
        void addCell(T t, int x, int y);
        T* begin(void);
        T* end(void);
        T& at(int x, int y);
        T& at(int i);
        // void executeTurn(void);
        // void removeCell(int x, int y);
        // void printBoard(void);
        // bool inBounds(int x, int y);
        // int getNeighbors(int i);
        void countNeighbors(T&);

    private:
        std::vector<T> grid;
        int x_size;
        int y_size;
        int generation;
        int population;
};


//Life constructor. Place cells in grid. Call like --> Life<ConwayCell> life(input);...then life(print), life(simulate)...
// template<typename T>
// Life<T>::Life(istream& in) {
//     population = 0;
//     generation = 0;
//     in >> x_size;
//     in >> y_size;

//     int total = x_size * y_size;
//     for(int i=0; i<total; i++) {
//         char c;
//         in >> c;
//         grid[i]. //put cell in grid --> T(c); 
//     }
// }


template <typename T>
void Life<T>::countNeighbors(T& cell) {
    int neighbors = 0;
    int n = cell.numOfNeighbors();
    //vector<NeighborAxis> n_axis = cell.neighborAxis();

    for(int i=0; i<n; i++) {
        //access grid, check if cell is alive and increment neighbors
        if(isAlive(n, i)) {
            neighbors++;
        }
    }

    cell.setNumberOfNeighbors(neighbors);
}
//determines if neighbor is alive depending on Conway/Fredkin and index
template<typename T>
bool Life<T>::isAlive(int n, int i) {
    //if ConwayCell
    if(n==8) {
        if(i==0) {
            if (inBounds(i-1) && (<< at(i-1)) == '*') {return true;}
        }
        else if(i==1){
            if (inBounds(i+1) && (<< at(i+1)) == '*') {return true;;}
        }
        else if(i==2){
            if (inBounds(i-x_size) && (<< at(i-x_size)) == '*') {return true;}
        }
        else if(i==3){
            if (inBounds(i-x_size-1) && (<< at(i-x_size-1)) == '*') {return true;}
        }
        else if(i==4){
            if (inBounds(i-x_size+1) && (<< at(i-x_size+1)) == '*') {return true;}
        }
        else if(i==5){
            if (inBounds(i+x_size) && (<< at(i+x_size)) == '*') {return true;}
        }
        else if(i==6){
            if (inBounds(i+x_size-1) && (<< at(i+x_size-1)) == '*') {return true;}
        }
        else if(i==7){
            if (inBounds(i+x_size+1) && (<< at(i+x_size+1)) == '*') {return true;}
        }
    }
    //if FredkinCell
    else if(n==4) {
        if(i==0){
            if (inBounds(i-1) && (<< at(i-1)) != '*' && (<< at(i-1)) != '.' && (<< at(i-1)) != '-') {return true;}
        }
        if(i==1){
            if (inBounds(i+1) && (<< at(i-1)) != '*' && (<< at(i-1)) != '.' && (<< at(i-1)) != '-') {return true;}
        }
        if(i==2){
            if (inBounds(i-x_size) && (<< at(i-1)) != '*' && (<< at(i-1)) != '.' && (<< at(i-1)) != '-') {return true;}
        }
        if(i==3){
            if (inBounds(i+x_size) && (<< at(i-1)) != '*' && (<< at(i-1)) != '.' && (<< at(i-1)) != '-') {return true;}
        }
    }
}









//set number of neighbors 
void AbstractCell::setNumberOfNeighbors(int n) {
    numberOfNeighbors = n;
}

AbstractCell::operator int() {
    return 0;
}







//constructor for Cell creates new ConwayCell or FredkinCell depending on input
Cell::Cell(char c) {
    if(c=='.' || c=='*')
        p = new ConwayCell(c);
    else
        p = new FredkinCell(c);
}

//modify state of Cell on a turn after neighbors have been set
void Cell::turn() {
    p->turn(); //after one turn
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
void ConwayCell::turn() {

}
//return number of neighbors for ConwayCell
const int ConwayCell::numOfNeighbors() const {
    //would have to determine if in corner, edge, or middle
    return 8;
}












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
void FredkinCell::turn() {

}
//FredkinCell returns age when converted to int. 
FredkinCell::operator int() {
    return age;
}
//return number of of neighbors for FredkinCell
const int FredkinCell::numOfNeighbors() const {
    //determine if in corner, edge, or middle
    return 4; 
}