#include <iostream> // cout, endl
#include <sstream>
#include <string> 
#include <vector>

#include "gtest/gtest.h"

#include "Life.h"

using namespace std;


// ----
// ConwayCell
// ----

TEST(ConwayTest, constructor_0) {
	ConwayCell c = ConwayCell('*');
	ASSERT_EQ(c.alive, true);
}
TEST(ConwayTest, constructor_1) {
	ConwayCell c = ConwayCell('.');
	ASSERT_EQ(c.alive, false);
}


// ----
// FredkinCell
// ----
TEST(FredkinTest, constructor_0) {
	FredkinCell f = FredkinCell('-');
	ASSERT_EQ(f.alive, false);
}
TEST(FredkinTest, constructor_1) {
	FredkinCell f = FredkinCell('0');
	ASSERT_EQ(f.alive, true);
	ASSERT_EQ(f.age, 0);
}


// ----
// Cell
// ----
TEST(CellTest, constructor_0) {
	Cell c = Cell('.');
	bool result = false;
	if(!c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, constructor_1) {
	Cell c = Cell('*');
	bool result = false;
	if(c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, constructor_2) {
	Cell c = Cell('-');
	bool result = false;
	if(!c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, constructor_3) {
	Cell c = Cell('0');
	bool result = false;
	if(c && c==0) {
		result = true;
	}
	ASSERT_EQ(result, true);
}





// ----
// Life
// ----

// ----
// constructor
// ----
TEST(LifeTest, constructor_0) {
    istringstream r("..*...\n");
    ostringstream w;
    Life<ConwayCell> life(1, 6, r, w);

    ASSERT_EQ(life.grid[0].alive, false);
    ASSERT_EQ(life.grid[2].alive, true);
    ASSERT_EQ(life.grid[0].printCell(), '.');
    ASSERT_EQ(life.grid[2].printCell(), '*');
}
//do it for Fredkin and Cell too
TEST(LifeTest, constructor_1) {
	istringstream r("--01--\n");
	ostringstream w;
	Life<FredkinCell> life(1, 6, r, w);

	ASSERT_EQ(life.grid[0].alive, false);
	ASSERT_EQ(life.grid[2].alive, true);
	ASSERT_EQ(life.grid[3].alive, true);
	ASSERT_EQ(life.grid[2].age, 0);
	ASSERT_EQ(life.grid[0].printCell(), '-');
	ASSERT_EQ(life.grid[2].printCell(), '0');
	ASSERT_EQ(life.grid[3].printCell(), '1');
}
TEST(LifeTest, constructor_2) {
	istringstream r("--0*.-\n");
	ostringstream w;
	Life<Cell> life(1, 6, r, w);

	bool result = false;
	if(!life.grid[1]) {result = true;}
	ASSERT_EQ(result, true);
	result = false;
	if(life.grid[2]==0) {result = true;}
	ASSERT_EQ(result, true);
	result = false; 
	
	ASSERT_EQ(life.grid[3].printCell(), '*');
	// ASSERT_EQ(life.grid[4], false);
}
//countNeighbors test
TEST(LifeTest, countNeighbors_0) {
    istringstream r(".***..\n.***..\n.***..\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);

    int n = life.countNeighbors(life.at(8), 8);
    ASSERT_EQ(n, 8);
}


//inBounds test
TEST(LifeTest, inBounds_0) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);

    // for(int i=0;i<life.grid.size();i++) {
    // 	cout << life.grid[i].printCell();
    // }
    // ConwayCell& c = life.at(2);
    // bool b = false;
    // if(c){b=true;}
    // ASSERT_EQ(b, true);

    
    ASSERT_EQ(life.inBounds(15), true);
}


// TEST(LifeTest, constructor_1) {

// 	Darwin d = Darwin(1,5);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		ASSERT_TRUE(d.inBounds(0,i));
// 	}
// }

