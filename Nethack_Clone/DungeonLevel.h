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
	~DungeonLevel();

	void placePlayer(Player * pl, bool down);	//Places character for beginning of each floor
	void placeCreature(Creature * cr);	//Places a creature randomly into the dungeon
	void placeItem(Item * it);	//Place item in dungeon
	void printDungeon(std::ostream & output);
	static int randomNumber(int iMax);

	int getCurrentFloor();
	Floor * getCurrentFloorObj();
	void setCurrentFloor(int floor);
	std::vector<Floor *> getFloors() const;
	Floor * getFloor(int numFloor);
	int getNumFloors();

private:
	int currFloor;	//Current floor for player
	int iNumFloors;	//Number of floors in dungeon
	std::vector<Floor *> vFloors;	//Vector of floors in dungeon
	int iWidth;		//width of dungeon. We will not make getter setter because we want it to always be 79 for now
	int iHeight;	//height of dungeon, always 20 for now
};

#endif