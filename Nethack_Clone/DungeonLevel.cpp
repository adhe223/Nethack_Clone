#include <ostream>
#include <ctime>
#include <random>
#include <vector>
#include "DungeonLevel.h"
#include "Tile.h"
#include "Player.h"
#include "Item.h"
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

DungeonLevel::~DungeonLevel()
{
	for (int i = 0; i < vFloors.size(); i++)
	{
		delete vFloors[i];
	}
}

void DungeonLevel::placePlayer(Player * pl, bool down)
{
	Floor* fl = getFloor(currFloor);
	vector<vector<Tile *>> map = fl->getMap();
	
	for (int row = 0; row < fl->getHeight(); row++)
	{
		for (int col = 0; col < fl->getWidth(); col++)
		{
			if (map[row][col]->getSymbol() == '>' && down == true)
			{
				map[row][col]->setCharacter(pl);
				pl->setRow(row);
				pl->setCol(col);
			}
			else if (map[row][col]->getSymbol() == '<' && down == false)
			{
				map[row][col]->setCharacter(pl);
				pl->setRow(row);
				pl->setCol(col);
			}
		}
	}
}

void DungeonLevel::placeCreature(Creature * cr)
{
	Floor* fl = getFloor(currFloor);
	vector<vector<Tile *>> map = fl->getMap();

	bool placed = false;
	while (!placed)
	{
		int iRandRow = randomNumber(iHeight);
		int iRandCol = randomNumber(iWidth);

		//Check if creature or player is already there
		Tile * tl = map[iRandRow][iRandCol];
		if (tl->getCharacter() == NULL)
		{
			//Empty room tile (may have item, but that's fine
			if (tl->getSymbol() == '.')
			{
				//Place the creature
				tl->setCharacter(cr);
				cr->setRow(iRandRow);
				cr->setCol(iRandCol);
				placed = true;
			}
		}
	}
}

void DungeonLevel::placeItem(Item * it)
{
	Floor* fl = getFloor(currFloor);
	vector<vector<Tile *>> map = fl->getMap();

	bool placed = false;
	while (!placed)
	{
		int iRandRow = randomNumber(iHeight);
		int iRandCol = randomNumber(iWidth);
		Tile * tl = map[iRandRow][iRandCol];

		//Empty room tile (may have item, but that's fine
		if (tl->getSymbol() == '.')
		{
			//Place the item
			tl->addItem(it);
			placed = true;
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

void DungeonLevel::setCurrentFloor(int floor)
{
	currFloor = floor;
}

Floor * DungeonLevel::getCurrentFloorObj()
{
	return vFloors[currFloor];
}

int DungeonLevel::getNumFloors()
{
	return iNumFloors;
}
