#include <iostream>
#include <string>
#include <vector>

#include "DungeonLevel.h"
#include "Tile.h"
#include "Floor.h"

using namespace std;

int main()
{
	DungeonLevel test(2);
	test.printDungeon(cout);
	
	return 0;
}