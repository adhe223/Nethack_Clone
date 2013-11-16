#include "Tile.h"
using namespace std;

Tile::Tile(int row, int col)
{
	iRow = row;
	iCol = col;
	//default value is impassable tile
	cSymbol = ' ';
	bPassable = false;
	character = NULL;
}

Tile::Tile(int row, int col, char symbol, bool pass)
{
	iRow = row;
	iCol = col;
	cSymbol = symbol;
	bPassable = pass;
	character = NULL;
}

void Tile::setCharacter(Character* ch)
{
	character = ch;
}

Character* Tile::getCharacter()
{
	return character;
}

void Tile::clearCharacter()
{
	character = NULL;
}

int Tile::getRow() const
{
	return iRow;
}

int Tile::getCol() const
{
	return iCol;
}

vector<Item*> & Tile::getItems()
{
	return vItems;
}

void Tile::addItem(Item * item)
{
	vItems.push_back(item);
}

void Tile::removeItem(int i)
{
	Item * toDelete = vItems[i];
	vItems.erase(vItems.begin() + i);
	delete toDelete;
}

char Tile::getSymbol() const
{
	return cSymbol;
}

void Tile::setSymbol(char symbol)
{
	cSymbol = symbol;
}

bool Tile::isPassable() const
{
	return bPassable;
}

void Tile::setPassable(bool pass)
{
	bPassable = pass;
}

void Tile::printTile(std::ostream & output)
{
	//Check if there is a character
	if (character != NULL) {output << character->getSymbol();}
	else if (vItems.size() != 0) {output << vItems.back()->getSymbol();}
	else {output << getSymbol();}
}