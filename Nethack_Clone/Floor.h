#ifndef _Floor_included_
#define _Floor_included_

#include <vector>
#include "Tile.h"

class Creature;
class Item;

class Floor
{
public:
	Floor(int floor, int numFloors, int floorWidth, int floorHeight);		//Constructs floor
	
	void printFloor(std::ostream & output);

	Tile * getTile(int row, int col);
	int getFloor() const;
	std::vector<std::vector<Tile *>> getMap() const;
	std::vector<std::vector<Tile *>> & getMapRef();
	int getHeight() const;
	int getWidth() const;
	vector<Creature *> & getCreatures();
	void addCreature(Creature * cr);
	void removeDeadCreatures();

private:
	void drawBlank();	//Helper function that fills vector with blank spaces
	void drawTunnel();	//Helper function that adds the tunnel to the vector
	void drawRooms();	//Helper function that adds the rooms to the vector
	void drawStairs();	//Helper function that adds the stairs into the vector

	int iFloor;		//Which floor this is
	int iNumFloors;	//Number of floors in dungeon (need to draw stairs)
	std::vector<std::vector<Tile *>> vMap;	//2D vector of tile objects that is our map
	int iWidth;		//width of floor. We will not make getter setter because we want it to always be 79 for now
	int iHeight;	//height of floor, always 20 for now

	int iSectorWide;	//Number of sectors our dungeon has widthwise
	int iSectorHigh;	//Number of sectors our dungeon has heightwise
	int iSectorHeight;	//Height of sectors
	int iSectorWidth;	//Width of sectors

	int iMinRoomWidth; //Smallest Room width
	int iMinRoomHeight; //Smallest Room height
	int iMaxRoomWidth;	//Largest width a room can have
	int iMaxRoomHeight;	//Largest height a room can have

	vector<Creature *> vCreatures;
	//vector<Item *> vItems;
};

#endif