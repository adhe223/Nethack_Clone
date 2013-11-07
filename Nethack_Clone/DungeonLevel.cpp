#include <ostream>
#include <ctime>
#include <random>
#include <vector>
#include "DungeonLevel.h"
#include "Tile.h"
using namespace std;

DungeonLevel::DungeonLevel(int numFloors)
{
	iNumFloors = numFloors;
	iWidth = 79;
	iHeight = 20;

	for (int floor = 0; floor < iNumFloors; floor++)
	{
		vFloors.push_back(new Floor(floor, iNumFloors, iWidth, iHeight));
	}
}

int DungeonLevel::randomNumber(int iMax)
{
	static mt19937 mt(time(NULL));
	return mt() % iMax;
}
	
void DungeonLevel::printDungeon(ostream & output)
{
	for (int floor = 0; floor < iNumFloors; floor++)
	{
		vFloors[floor]->printFloor(output);
		output << endl;
	}
}

vector<Floor *> DungeonLevel::getFloors() const
{
	return vFloors;
}
