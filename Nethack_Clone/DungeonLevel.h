#ifndef _DungeonLevel_included_
#define _DungeonLevel_included_

#include <vector>
#include "Floor.h"
#include "Player.h"
#include "Creature.h"

class DungeonLevel
{
public:
	DungeonLevel(int numFloors);		//Constructs map

	void placePlayer(Player * pl);	//Places character for beginning of each floor
	void placeCreature(Creature * cr);	//Places a creature randomly into the dungeon
	void printDungeon(std::ostream & output);
	static int randomNumber(int iMax);

	int getCurrentFloor();
	std::vector<Floor *> getFloors() const;
	Floor * getFloor(int numFloor);

private:
	int currFloor;	//Current floor for player
	int iNumFloors;	//Number of floors in dungeon
	std::vector<Floor *> vFloors;	//Vector of floors in dungeon
	int iWidth;		//width of dungeon. We will not make getter setter because we want it to always be 79 for now
	int iHeight;	//height of dungeon, always 20 for now
};

#endif