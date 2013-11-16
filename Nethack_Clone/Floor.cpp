#include <ostream>
#include <ctime>
#include <iostream>
#include "Floor.h"
#include "Tile.h"
#include "DungeonLevel.h"
using namespace std;

Floor::Floor(int floor, int numFloors, int floorWidth, int floorHeight)
{
	iFloor = floor;
	iNumFloors = numFloors;
	iWidth = floorWidth;
	iHeight = floorHeight;

	iSectorWide = 3;
	iSectorHigh = 2;
	iSectorHeight = iHeight/iSectorHigh;
	iSectorWidth = iWidth/iSectorWide;

	//Need at least 200 room tiles with 6 rooms. At minimum our rooms should be 200/6 tiles, or 7x5 at least.
	//Max room size will be 24 wide x 8 high (fills sector with room for one space on each side)
	iMinRoomWidth = 7;
	iMinRoomHeight = 5;
	iMaxRoomWidth = 24;
	iMaxRoomHeight = 8;

	drawBlank();
	drawTunnel();
	drawRooms();
	drawStairs();
}

Tile* Floor::getTile(int row, int col)
{
	return vMap[row][col];
}

vector<vector<Tile *>> Floor::getMap() const
{
	return vMap;
}

std::vector<std::vector<Tile *>> & Floor::getMapRef()
{
	return vMap;
}

int Floor::getFloor() const
{
	return iFloor;
}

int Floor::getWidth() const
{
	return iWidth;
}

int Floor::getHeight() const
{
	return iHeight;
}

vector<Creature *> & Floor::getCreatures()
{
	return vCreatures;
}
	
void Floor::printFloor(ostream & output)
{
	for (int row = 0; row < iHeight; row++)
	{
		for (int col = 0; col < iWidth; col++)
		{
			vMap[row][col]->printTile(output);
		}
		output << endl;
	}
}

void Floor::drawBlank()
{
	for (int row = 0; row < iHeight; row++)
	{
		vMap.push_back(vector<Tile *>());
		for (int col = 0; col < iWidth; col++)
		{
			vMap[row].push_back(new Tile(row, col));
		}
	}
}

void Floor::drawTunnel()
{
	//Easiest to draw then horizontal tunnel first, then the vertical one
	for (int row = 0; row < iHeight; row++)
	{
		if (row == iSectorHeight/2 || row == iHeight - iSectorHeight/2)
		{
			//Draw horizontal section of tunnel
			for (int col = iSectorWidth/2; col <= iWidth - iSectorWidth/2; col++)
			{
				vMap[row][col]->setSymbol('#');
			}
		}
	}

	//Now draw the vertical part of the tunnel
	for (int col = 0; col < iWidth; col++)
	{
		if (col == iSectorWidth/2 || col == iWidth - iSectorWidth/2)
		{
			//Draw the vertical line
			for (int row = iSectorHeight/2; row < iHeight - iSectorHeight/2; row++)
			{
				vMap[row][col]->setSymbol('#');
			}
		}
	}
}

void Floor::drawRooms()
{
	//Iterate over the sectors.
	for (int sector = 0; sector < (iSectorWide * iSectorHigh); sector++)
	{
		//First calculate the bounds of this sector
		if (sector == 0 || sector == 1 || sector == 2)
		{
			int iSectorRowMin = 0;
			int iSectorRowMax = iSectorHeight;
			int iSectorColMin = sector * iSectorWidth;
			int iSectorColMax = iSectorColMin + iSectorWidth;
		}
		else
		{
			int iSectorRowMin = iSectorHeight;
			int iSectorRowMax = iSectorHigh * iSectorHeight;
			int iSectorColMin = (sector - 3) * iSectorWidth;
			int iSectorColMax = iSectorColMin + iSectorWidth;
		}

		//Randomly choose the size of the room
		int iRoomW = DungeonLevel::randomNumber(iMaxRoomWidth + 1 - iMinRoomWidth) + iMinRoomWidth;
		int iRoomH = DungeonLevel::randomNumber(iMaxRoomHeight + 1 - iMinRoomHeight) + iMinRoomHeight;

		//We will use a brute force method here because it allows for more randomness in room placement
		//Randomly place the top left corner of the room into the sector, then check if it is on the path. We do
		//some simple calculations before placing the point to make sure that the room is placed where it will fit
		//in the sector. Will create vectors for the possible rows and possible cols it can start at.
		vector<int> vPossRow;
		int j = 0;
		while (j + iRoomH + 1 < iSectorHeight)		//+1 is to ensure rooms don't collide
		{
			if (sector - 3 < 0) {vPossRow.push_back(j);}
			else {vPossRow.push_back(j + iSectorHeight);}
			j++;
		}

		vector<int> vPossCol;
		int i = 0;
		while (i + iRoomW + 1 < iSectorWidth)	//+1 is to ensure rooms don't collide
		{
			if (sector - 3 < 0) {vPossCol.push_back(i + (sector * iSectorWidth));}
			else {vPossCol.push_back(i + ((sector - 3) * iSectorWidth));}
			i++;
		}

		//Now randomly select a coordinate from the two vectors and test if it is on the path
		bool valid = false;
		int iStartRow;
		int iStartCol;
		while(!valid)
		{
			iStartRow = vPossRow[DungeonLevel::randomNumber(vPossRow.size())];
			iStartCol = vPossCol[DungeonLevel::randomNumber(vPossCol.size())];

			//Test if intersects path
			for (int row = iStartRow; row < iStartRow + iRoomH; row++)
			{
				for (int col = iStartCol; col < iStartCol + iRoomW; col++)
				{
					if (vMap[row][col]->getSymbol() == '#') {valid = true;}
				}
			}
		}

		//At this point we have a starting position for the room that will be valid, draw the room
		for (int row = iStartRow; row < iStartRow + iRoomH; row++)
		{
			for (int col = iStartCol; col < iStartCol + iRoomW; col++)
			{
				vMap[row][col]->setSymbol('.');
			}
		}
	}
}

void Floor::drawStairs()
{
	//Find a tile that is a room tile and not touching a tunnel (to avoid a trap
	//scenario). Place it randomly of course
	bool uPlaced = false;	//How we know it was successfully placed

	while (!uPlaced)
	{
		//Place the stairs up
		int row = DungeonLevel::randomNumber(iHeight);
		int col = DungeonLevel::randomNumber(iWidth);

		//First check if it is a room tile
		if (vMap[row][col]->getSymbol() == '.')
		{
			//Now check the 8 surrounding tiles for tunnels
			bool bIsTunnel = false;

			//Use a counter so we can control the break and protect against out of bounds indices access
			int outCounter = 0;
			int j = row - 1;
			while (outCounter <= 3)
			{
				//Need to make sure we don't check out of bounds indices
				if (j < 0) {j = 0; outCounter++;}
				else if (j >= iHeight) {j = iHeight - 1; outCounter++;}

				//Use a counter so we can control the break and protect against out of bounds indices access
				int inCounter = 0;
				int i = col - 1;
				while (inCounter <= 3)
				{
					//Need to make sure we don't check out of bounds indices
					if (i < 0) {i = 0; inCounter++;}
					else if (i >= iWidth) {i = iWidth - 1; inCounter++;}

					if (vMap[j][i]->getSymbol() == '#') {bIsTunnel = true;}
					i++;
					inCounter++;
				}

				j++;
				outCounter++;
			}

			//Place the up stairs if there was not a tunnel
			if (!bIsTunnel) {vMap[row][col]->setSymbol('>'); uPlaced = true;}
		}

		
	}

	//Now see if downstairs are necessary, if so, place (for PA2 we always place them, so make bDown true)
	bool bDown = true;
	if (iFloor == iNumFloors - 1) {bDown = false;}

	if (bDown)
	{
		bool dPlaced = false;	//How we know it was successfully placed

		while (!dPlaced)
		{
			int row = DungeonLevel::randomNumber(iHeight);
			int col = DungeonLevel::randomNumber(iWidth);

			//First check if it is a room tile
			if (vMap[row][col]->getSymbol() == '.')
			{
				//Now check the 8 surrounding tiles for tunnels
				bool bIsTunnel = false;

				//Use a counter so we can control the break and protect against out of bounds indices access
				int outCounter = 0;
				int j = row - 1;
				while (outCounter <= 3)
				{
					//Need to make sure we don't check out of bounds indices
					if (j < 0) {j = 0; outCounter++;}
					else if (j >= iHeight) {j = iHeight - 1; outCounter++;}

					//Use a counter so we can control the break and protect against out of bounds indices access
					int inCounter = 0;
					int i = col - 1;
					while (inCounter <= 3)
					{
						//Need to make sure we don't check out of bounds indices
						if (i < 0) {i = 0; inCounter++;}
						else if (i >= iWidth) {i = iWidth - 1; inCounter++;}
						
						if (vMap[j][i]->getSymbol() == '#') {bIsTunnel = true;}

						i++;
						inCounter++;
					}

					j++;
					outCounter++;
				}

				//Make sure there isn't other stairs there
				bool bIsStairs = false;
				if (vMap[row][col]->getSymbol() == '>') {bIsStairs = true;}

				//Place the down stairs if there was not a tunnel
				if (!bIsTunnel && !bIsStairs) {vMap[row][col]->setSymbol('<'); dPlaced = true;}
			}
		}
	}
}