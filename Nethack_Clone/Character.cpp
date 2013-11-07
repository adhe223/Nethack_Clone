#include "Character.h"
#include "Entity.h"
#include <string>
#include <vector>

Character::Character()
{
	m_iHealth = 10;
}

bool Character::canMove(int row, int col, Floor* fl)
{
	//Check to see if the tile to move to is out of range
	if (row < 0 || row >= fl->getHeight() || col < 0 || col >= fl->getWidth())
	{
		return false;
	}

	//Check to see if there is a creature
	if (fl->getTile(row, col)->getCharacter() != NULL) {return false;}

	char symbol = fl->getTile(row, col)->getSymbol();
	if (symbol != ' ') {return true;}
}

void Character::move(Floor* fl, int dir)
{
	if (dir == 8)
	{
		bool valid = canMove(iRow + 1, iCol, fl);

	}
}

int Character::getHealth()
{
	return m_iHealth;
}

void Character::setHealth(int iHealth)
{
	m_iHealth = iHealth;
}

void Character::attack(Character & target)
{
}

int Character::getRow() const
{
	return iRow;
}

void Character::setRow(int row)
{
	iRow = row;
}

int Character::getCol() const
{
	return iCol;
}

void Character::setCol(int col)
{
	iCol = col;
}

void Character::dumpObject()
{
	cout << "Character:" << endl;

	dumpObjectData();
}

void Character::dumpObjectData()
{
	Entity::dumpObjectData();

	cout << "    Health: " << getHealth() << endl;
}

void Character::writeFragment(ostream & output)
{
	output << " <Character>" << endl;

	writeDataAsFragment(output);

	output << " </Character>" << endl;
}

void Character::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);

	output << "	<health>"
		<< getHealth()
		<< "</health>"
		<< endl;
}

void Character::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);
	
	if (sElementName == "health")
	{
		setHealth(atoi(sValue.c_str()));
	}
}

