#include "Player.h"
#include <string>

using namespace std;

Player::Player()
{
	m_iExperience = 0;
	m_iLevel = 1;
}

bool Player::canMove(int row, int col, Floor* fl)
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

void Player::move(Floor* fl, char dir)
{
	//Check if valid position
	bool valid;
	int newRow;
	int newCol;

	int iRow = getRow();
	int iCol = getCol();
	if (dir == '8')
	{
		newRow = iRow - 1;
		newCol = iCol;
		valid = canMove(newRow, newCol, fl);
	}
	else if (dir == '4') 
	{
		newRow = iRow;
		newCol = iCol - 1;
		valid = canMove(newRow, newCol, fl);
	}
	else if (dir == '2')
	{
		newRow = iRow + 1;
		newCol = iCol;
		valid = canMove(newRow, newCol, fl);
	}
	else if (dir == '6')
	{
		newRow = iRow;
		newCol = iCol + 1;
		valid = canMove(newRow, newCol, fl);
	}

	//Move op
	if (valid)
	{
		//Change the map of the dungeon floor
		vector<std::vector<Tile *>> levelMap = fl->getMap();
		levelMap[iRow][iCol]->clearCharacter();

		setRow(newRow);
		setCol(newCol);
		levelMap[newRow][newCol]->setCharacter(this);
	}
}

void Player::attack(Character & target)
{
	target.setHealth(target.getHealth() - weapon->getAttackBonus());
}

int Player::getExperience()
{
	return m_iExperience;
}

void Player::setExperience(int iExperience)
{
	m_iExperience = iExperience;
}

int Player::getLevel()
{
	return m_iLevel;
}

void Player::setLevel(int iLevel)
{
	m_iLevel = iLevel;
}



void Player::dumpObject()
{
	cout << "Player:" << endl;

	dumpObjectData();
}

void Player::dumpObjectData()
{
	Character::dumpObjectData();

	cout << "Experience: " << getExperience() << endl;
	cout << "     Level: " << getLevel() << endl;
}

void Player::writeFragment(ostream & output)
{
	output << " <Player>" << endl;

	writeDataAsFragment(output);

	output << " </Player>" << endl;
}

void Player::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);

	output << "	<experience>"
		<< getExperience()
		<< "</experience>"
		<< endl
		<< "	<level>"
		<< getLevel()
		<< "</level>"
		<< endl;
}

void Player::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);
	
	if (sElementName == "experience")
	{
		setExperience(atoi(sValue.c_str()));
	}
	else if (sElementName == "level")
	{
		setLevel(atoi(sValue.c_str()));
	}
}

