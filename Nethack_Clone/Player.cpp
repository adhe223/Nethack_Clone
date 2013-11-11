#include "Player.h"
#include "Consumable.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player()
{
	m_iExperience = 0;
	m_iLevel = 1;
	regenCount = 0;
	score = 0;
	weapon = new Weapon("Bare Hands", 1, 0);
}

bool Player::canMove(int row, int col, Floor* fl)
{
	//Check to see if the tile to move to is out of range
	if (row < 0 || row >= fl->getHeight() || col < 0 || col >= fl->getWidth())
	{
		return false;
	}

	//Check to see if there is a character
	Character * ch = fl->getTile(row, col)->getCharacter();
	if (ch != NULL)
	{
		attack(ch);
		return false;
	}

	char symbol = fl->getTile(row, col)->getSymbol();
	if (symbol == ' ') {return false;}
	return true;
}

//If the desired tile to move to has another character then we attack (called in the canMove function)
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

void Player::attack(Character * target)
{
	target->setHealth(target->getHealth() - 1);
	cout << "Attacked a " << target->getName() << " with your " << weapon->getName() << "!" << endl;

	if (target->getHealth() > 0)
	{
		cout << "The " << target->getName() << " has " << target->getHealth() << "HP left." << endl;
	}
	else
	{
		cout << "The " << target->getName() << " has been killed!" << endl;
	}
}

//Regenerate 1 HP every 4 turns
void Player::regen()
{
	regenCount++;
	if (regenCount % 4 == 0)
	{
		setHealth(getHealth() + 1);
		regenCount = 0;
	}
}

//Sets level after every turn. Level up after every 10 exp points. Also sets the players max health based
//on the level
void Player::levelUp()
{
	setLevel(getExperience() / 10);
	setMaxHealth(10 + 3 * (getLevel() - 1));
}

void Player::use(Floor * fl)
{
	//Fetch the vector of items that is currently on the ground and attempt to use all of them
	vector<Item *> items = fl->getMap()[getRow()][getCol()]->getContent();

	for (int i = 0; i < items.size(); i++)
	{
		//Is consumable
		Consumable * cons = dynamic_cast<Consumable *>(items[i]);
		if (cons != NULL)
		{
			cons->use(static_cast<Character*>(this));
		}
	}
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

int Player::getScore()
{
	return 4 * getExperience();
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

