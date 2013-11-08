#ifndef _Tile_included_
#define _Tile_included_

#include "Character.h"
#include <ostream>
#include <vector>

class Tile
{
public:
	Tile(int row, int col);
	Tile(int row, int col, char symbol, bool pass);

	void setCharacter(Character* ch);
	Character* getCharacter();
	void clearCharacter();
	
	int getRow() const;
	int getCol() const;
	vector<Entity*> getContent() const;
	char getSymbol() const;
	void setSymbol(char symbol);
	bool isPassable() const;
	void setPassable(bool pass);

	void printTile(std::ostream & output);

private:
	char cSymbol;
	bool bPassable;
	int iRow;
	int iCol;
	Character* character;
	vector<Entity*> vContents;
};

#endif