#include <ostream>
#include <ctime>
#include <random>
#include <vector>
#include "DungeonLevel.h"
#include "Tile.h"
#include "Player.h"
using namespace std;

DungeonLevel::DungeonLevel(int numFloors)
{
	iNumFloors = numFloors;
	iWidth = 79;
	iHeight = 20;
	currFloor = 0;

	for (int floor = 0; floor < iNumFloors; floor++)
	{
		vFloors.push_back(new Floor(floor, iNumFloors, iWidth, iHeight));
	}
}

void DungeonLevel::placePlayer(Player * pl)
{
	Floor* fl = getFloor(0);
	vector<vector<Tile *>> map = fl->getMap();
	
	for (int row = 0; row < fl->getHeight(); row++)
	{
		for (int col = 0; col < fl->getWidth(); col++)
		{
			if (map[row][col]->getSymbol() == '>')
			{
				map[row][col]->setCharacter(pl);
				pl->setRow(row);
				pl->setCol(col);
			}
		}
	}
}

int DungeonLevel::randomNumber(int iMax)
{
	static mt19937 mt(time(NULL));
	return mt() % iMax;
}

int DungeonLevel::getCurrentFloor()
{
	return currFloor;
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

Floor * DungeonLevel::getFloor(int numFloor)
{
	return vFloors[numFloor];
}
