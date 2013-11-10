#include "Character.h"
#include "Entity.h"
#include <string>
#include <vector>

Character::Character()
{
	m_iHealth = 10;
	iMaxHealth = 10;
}

void Character::attack(Character & target)
{
}

int Character::getHealth()
{
	return m_iHealth;
}

int Character::getMaxHealth()
{
	return iMaxHealth;
}

void Character::setMaxHealth(int iMaxHP)
{
	iMaxHealth = iMaxHP;
}

void Character::setHealth(int iHealth)
{
	m_iHealth = iHealth;
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

