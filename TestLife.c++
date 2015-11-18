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



// TEST(LifeTest, constructor_1) {

// 	Darwin d = Darwin(1,5);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		ASSERT_TRUE(d.inBounds(0,i));
// 	}
// }

