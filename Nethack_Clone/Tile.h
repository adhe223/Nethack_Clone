#ifndef _Tile_included_
#define _Tile_included_

#include "Character.h"
#include "Item.h"
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
	vector<Item*> & getItems();
	void addItem(Item * item);
	void removeItem(int i);
	char getSymbol() const;
	void setSymbol(char symbol);
	bool isPassable() const;
	void setPassable(bool pass);

	void printTile(std::ostream & output);
	char outputChar();

private:
	char cSymbol;
	bool bPassable;
	int iRow;
	int iCol;
	Character* character;
	vector<Item *> vItems;
};

#endif