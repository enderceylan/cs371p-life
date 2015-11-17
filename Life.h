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

// class Cell;
// class AbstractCell;
// class ConwayCell;
// class FredkinCell;
// class Life;



class AbstractCell
{
    public:
        AbstractCell();
        virtual void updateStatus(int neighbors);
        virtual std::ostream& operator<<(std::ostream& out);
        virtual operator int(); //going to access age for FredkinCell
        virtual operator bool(); //going to access alive for Conway/Fredkin
        virtual const int numOfNeighbors() const = 0;
        //virtual void checkNeighbors() = 0; //
        //bool isValid();
    private:
        bool alive;
        int age; //only need for Fredkin??
};

class ConwayCell : public AbstractCell
{
    public:
        ConwayCell():AbstractCell(){};
        ConwayCell(char c); //construct ConwayCell as you read in input
        ConwayCell(int status);
        void updateStatus(int neighbors);
        const int numOfNeighbors() const;
        std::ostream& operator<<(std::ostream& out)
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
        operator bool();
    private:
        bool alive;
};

class FredkinCell : public AbstractCell
{
    public:
        FredkinCell():AbstractCell(){};
        FredkinCell(char c); //construct FredkinCell as you read in input
        FredkinCell(int status);
        void updateStatus(int neighbors);
        const int numOfNeighbors() const;

        operator int();
        operator bool();

        std::ostream& operator<<(std::ostream& out)
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
        bool alive;
        int age;
};

class Cell
{
    public:
        //Cell() : p(FredkinCell()) {};
        Cell(char c);
        //~Cell();
        AbstractCell* operator->() {return p;};
        void updateStatus(int neighbors); //one turn for a cell
        operator int();
        operator bool();
    private:
        AbstractCell *p;
};

template<typename T>
class Life
{
    public:
        Life(int x, int y);
        void addCell(T t, int x, int y);
        void addCellsToGrid(istream& r, ostream& w, int num_rows);
        T* begin(void);
        T* end(void);
        T& at(int x, int y);
        T& at(int i);
        void executeTurn(void);
        void removeCell(int x, int y);
        void runBoard(int num_evols, int freq);
        void printBoard(void);
        bool inBounds(int x, int y);
        int countNeighbors(T& cell);
        bool isAlive(int n, int i);

    private:
        std::vector<T> grid;
        int x_size;
        int y_size;
        int generation;
        int population;
};


