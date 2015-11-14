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
    private:
        bool alive;
};

class Cell
{
    public:
        Cell() : p(new AbstractCell()) {};
        AbstractCell* operator->() {return p;};
    private:
        AbstractCell *p;
};

class ConwayCell : public AbstractCell
{
    public:
        ConwayCell():AbstractCell();
        void updateStatus(int neighbors);
        friend std::ostream& operator<<(std::ostream& out)
        {
            return out << '*';
        };
};

class FredkinCell : public AbstractCell
{
    public:
        FredkinCell():AbstractCell();
        void updateStatus(int neighbors);
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
        void executeTurn(void);
        void removeCell(int x, int y);
        void printBoard(void);
        bool inBounds(int x, int y);
        int getNeighbors(int i);
    private:
        std::vector<T> grid;
        int x_size;
        int y_size;
        int generation;
};

