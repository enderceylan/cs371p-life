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
//constructor
TEST(ConwayTest, constructor_0) {
	ConwayCell c = ConwayCell('*');
	ASSERT_EQ(c.alive, true);
}
TEST(ConwayTest, constructor_1) {
	ConwayCell c = ConwayCell('.');
	ASSERT_EQ(c.alive, false);
}

TEST(ConwayTest, updateStatus_0) {
	ConwayCell c = ConwayCell('.');
	c.updateStatus(3);
	bool result = false;
	if(c) {result = true;}
	ASSERT_EQ(result, true);
}
TEST(ConwayTest, updateStatus_1) {
	ConwayCell c = ConwayCell('.');
	c.updateStatus(0);
	bool result = false;
	if(!c) {result = true;}
	ASSERT_EQ(result, true);
}
TEST(ConwayTest, updateStatus_2) {
	ConwayCell c = ConwayCell('*');
	c.updateStatus(1);
	bool result = false;
	if(!c) {result = true;}
	ASSERT_EQ(result, true);
}
TEST(ConwayTest, updateStatus_3) {
	ConwayCell c = ConwayCell('*');
	c.updateStatus(5);
	bool result = false;
	if(!c) {result = true;}
	ASSERT_EQ(result, true);
}

// ----
// FredkinCell
// ----
//constructor
TEST(FredkinTest, constructor_0) {
	FredkinCell f = FredkinCell('-');
	ASSERT_EQ(f.alive, false);
}
TEST(FredkinTest, constructor_1) {
	FredkinCell f = FredkinCell('0');
	ASSERT_EQ(f.alive, true);
	ASSERT_EQ(f.age, 0);
}
//updateStatus
TEST(FredkinTest, udpateStatus_0) {
	FredkinCell f = FredkinCell('-');
	f.updateStatus(1);
	bool result = false;
	if(f) {result = true;}
	ASSERT_EQ(result, true);
}
TEST(FredkinTest, udpateStatus_1) {
	FredkinCell f = FredkinCell('-');
	f.updateStatus(3);
	bool result = false;
	if(f) {result = true;}
	ASSERT_EQ(result, true);
}
TEST(FredkinTest, udpateStatus_3) {
	FredkinCell f = FredkinCell('0');
	f.updateStatus(0);
	bool result = false;
	if(!f) {result = true;}
	ASSERT_EQ(result, true);
}
TEST(FredkinTest, udpateStatus_4) {
	FredkinCell f = FredkinCell('0');
	f.updateStatus(2);
	bool result = false;
	if(!f) {result = true;}
	ASSERT_EQ(result, true);
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
TEST(CellTest, updateStatus_0) {
	Cell c = Cell('.');
	c.updateStatus(3);
	bool result = false;
	if(c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, updateStatus_1) {
	Cell c = Cell('.');
	c.updateStatus(1);
	bool result = false;
	if(!c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, updateStatus_2) {
	Cell c = Cell('*');
	c.updateStatus(5);
	bool result = false;
	if(!c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, updateStatus_3) {
	Cell c = Cell('*');
	c.updateStatus(2);
	bool result = false;
	if(c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, updateStatus_4) {
	Cell c = Cell('0');
	c.updateStatus(2);
	bool result = false;
	if(!c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, updateStatus_5) {
	Cell c = Cell('0');
	c.updateStatus(1);
	bool result = false;
	if(c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, updateStatus_6) {
	Cell c = Cell('-');
	c.updateStatus(2);
	bool result = false;
	if(!c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, updateStatus_7) {
	Cell c = Cell('-');
	c.updateStatus(3);
	bool result = false;
	if(c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}
TEST(CellTest, updateStatus_8) {
	Cell c = Cell('-');
	c.updateStatus(1);
	bool result = false;
	if(c) {
		result = true;
	}
	ASSERT_EQ(result, true);
}

//numOfNeighbors
TEST(CellTest, numOfNeighbors_0) {
	Cell c = Cell('-');
	int n = c.numOfNeighbors();
	ASSERT_EQ(n, 4);
}
TEST(CellTest, numOfNeighbors_1) {
	Cell c = Cell('.');
	int n = c.numOfNeighbors();
	ASSERT_EQ(n, 8);
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
}
//countNeighbors test
TEST(LifeTest, countNeighbors_0) {
    istringstream r(".***..\n.***..\n.***..\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);

    int n = life.countNeighbors(life.at(8), 8);
    ASSERT_EQ(n, 8);
}
TEST(LifeTest, countNeighbors_1) {
	istringstream r("-0-\n000\n-0-");
	ostringstream w;
	Life<FredkinCell> life(3, 3, r, w);

	int n = life.countNeighbors(life.at(4), 4);
	ASSERT_EQ(n, 4);
}
TEST(LifeTest, countNeighbors_2) {
	istringstream r("-0-\n-00\n-0-");
	ostringstream w;
	Life<Cell> life(3, 3, r, w);

	int n = life.countNeighbors(life.at(4), 4);
	ASSERT_EQ(n, 3);
}
TEST(LifeTest, countNeighbors_3) {
    istringstream r(".***..\n.***..\n.**...\n");
    ostringstream w;
    Life<Cell> life(3, 6, r, w);

    int n = life.countNeighbors(life.at(8), 8);
    ASSERT_EQ(n, 7);
}


//inBounds test
TEST(LifeTest, inBounds_0) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    
    ASSERT_EQ(life.inBounds(15), true);
}
TEST(LifeTest, inBounds_1) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    
    ASSERT_EQ(life.inBounds(20), false);
}
TEST(LifeTest, inBounds_2) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    
    ASSERT_EQ(life.inBounds(-2), false);
}

//at test
TEST(LifeTest, at_0) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    bool result = false;
    if(life.at(2)) {result = true;}
    ASSERT_EQ(result, true);
}
TEST(LifeTest, at_1) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    bool result = false;
    if(!life.at(3)) {result = true;}
    ASSERT_EQ(result, true);
}
TEST(LifeTest, at_2) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    bool result = false;
    if(life.at(8)) {result = true;}
    ASSERT_EQ(result, true);
}
//at test2
TEST(LifeTest, at2_0) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    bool result = false;
    if(life.at(0,2)) {result = true;}
    ASSERT_EQ(result, true);
}
TEST(LifeTest, at2_1) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    bool result = false;
    if(!life.at(1,1)) {result = true;}
    ASSERT_EQ(result, true);
}
TEST(LifeTest, at2_2) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    bool result = false;
    if(life.at(2,2)) {result = true;}
    ASSERT_EQ(result, true);
}

//printBoard test
TEST(LifeTest, printBoard_0) {
    istringstream r("..*...\n..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(3, 6, r, w);
    life.printBoard(true);
}
TEST(LifeTest, printBoard_1) {
    istringstream r("..*...\n..*...\n");
    ostringstream w;
    Life<ConwayCell> life(2, 6, r, w);
    life.printBoard(true);
}
TEST(LifeTest, printBoard_2) {
    istringstream r("..*\n..*\n..*\n");
    ostringstream w;
    Life<ConwayCell> life(3, 3, r, w);
    life.printBoard(true);
}

//iteration
TEST(LifeTest, iteration_0) {
    istringstream r("*....\n..*..\n..*..\n");
    ostringstream w;
    Life<ConwayCell> life(3, 5, r, w);

    int check = 0;
    //iteration
    for(int i=0; i<15; i++) {
    	if(life.grid[i] == life.at(i) ) {
    		++check;
    	}
    }
    ASSERT_EQ(check, 15);
}
TEST(LifeTest, iteration_1) {
    istringstream r("*.*..\n..*.*\n..*..\n");
    ostringstream w;
    Life<ConwayCell> life(3, 5, r, w);

    int check = 0;
    //iteration
    for(int i=0; i<15; i++) {
    	if(life.at(i)) {
    		++check;
    	}
    }
    ASSERT_EQ(check, 5);
}
TEST(LifeTest, iteration_2) {
    istringstream r("*....\n");
    ostringstream w;
    Life<ConwayCell> life(1, 5, r, w);

    int check = 0;
    //iteration
    for(int i=0; i<5; i++) {
    	if(life.grid[i] == life.at(i) ) {
    		++check;
    	}
    }
    ASSERT_EQ(check, 5);
}

//begin
TEST(LifeTest, begin_0) {
	istringstream r("*....\n..*..\n..*..\n");
    ostringstream w;
    Life<ConwayCell> life(3, 5, r, w);
    ConwayCell* c_begin = life.begin();

    //test begin
    bool beginBool = false;
    if(c_begin && life.at(0)) {beginBool = true;}
    ASSERT_EQ(beginBool, true);
}
TEST(LifeTest, begin_1) {
	istringstream r(".....\n..*..\n..*..\n");
    ostringstream w;
    Life<ConwayCell> life(3, 5, r, w);
    ConwayCell* c_begin = life.begin();

    //test begin
    bool beginBool = false;
    if(!(*c_begin)) {beginBool = true;}
    ASSERT_EQ(beginBool, true);
}
TEST(LifeTest, begin_2) {
	istringstream r("*.\n");
    ostringstream w;
    Life<ConwayCell> life(1, 2, r, w);
    ConwayCell* c_begin = life.begin();

    bool beginBool = false;
    if((*c_begin)) {beginBool = true;}
    ASSERT_EQ(beginBool, true);
}

//end
TEST(LifeTest, end_0) {
	istringstream r("*....\n..*..\n..*..\n");
    ostringstream w;
    Life<ConwayCell> life(3, 5, r, w);
    ConwayCell* c_end = life.end();

    //test begin
    bool endBool = false;
    if(!(*c_end) ) {endBool = true;}
    ASSERT_EQ(endBool, true);
}
TEST(LifeTest, end_1) {
	istringstream r("*....\n..*..\n..*.*\n");
    ostringstream w;
    Life<ConwayCell> life(3, 5, r, w);
    ConwayCell* c_end = life.end();

    //test begin
    bool endBool = false;
    if((*c_end) ) {endBool = true;}
    ASSERT_EQ(endBool, true);
}
TEST(LifeTest, end_2) {
	istringstream r("*....\n");
    ostringstream w;
    Life<ConwayCell> life(1, 5, r, w);
    ConwayCell* c_end = life.end();

    //test begin
    bool endBool = false;
    if(!(*c_end) ) {endBool = true;}
    ASSERT_EQ(endBool, true);
}


