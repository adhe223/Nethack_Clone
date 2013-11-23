#include "Tile.h"
#include "Consumable.h"
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

Tile::~Tile()
{
	delete character;

	for (int i = 0; i < vItems.size(); i++)
	{
		delete vItems[i];
	}
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

//Can only delete pointer if it is a consumable, otherwise it is part of the player
void Tile::removeItem(int i)
{
	if (dynamic_cast<Consumable*> (vItems[i]) != NULL)
	{
		Item * toDelete = vItems[i];
		vItems.erase(vItems.begin() + i);
		delete toDelete;
	}
	else
	{
		vItems.erase(vItems.begin() + i);
	}
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

char Tile::outputChar()
{
	if (character != NULL) {return character->getSymbol();}
	else if (vItems.size() != 0) {return vItems.back()->getSymbol();}
	else {return getSymbol();}
}