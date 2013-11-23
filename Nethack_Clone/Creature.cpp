#include "Creature.h"
#include <string>

using namespace std;

//Bad code reuse, this is in Creature and Player. Fix if time permits
bool Creature::canMove(int row, int col, Floor* fl)
{
	if (row < 0 || row >= fl->getHeight() || col < 0 || col >= fl->getWidth())
	{
		return false;
	}

	//Check to see if there is a creature
	if (fl->getTile(row, col)->getCharacter() != NULL) {return false;}

	char symbol = fl->getTile(row, col)->getSymbol();
	if (symbol == ' ') {return false;}
	return true;
}

//Move towards player
void Creature::move(Floor * fl, Player * pl)
{
	bool moveRow = false;
	bool moveCol = false;
	bool valid;
	int newRow;
	int newCol;

	int iRow = getRow();
	int iCol = getCol();
	int iPlayerRow = pl->getRow();
	int iPlayerCol = pl->getCol();

	//If player is in an adjacent tile then the creature attacks, can attack diagonal
	if (abs(iRow - iPlayerRow) <= 1 && abs(iCol - iPlayerCol) <= 1)
	{
		attack(pl);
	}

	if (iPlayerRow < iRow)
	{
		newRow = iRow - 1;
		newCol = iCol;
		valid = canMove(newRow, newCol, fl);
		if (valid) {moveRow = true;}
	}
	else if (iPlayerRow > iRow)
	{
		newRow = iRow + 1;
		newCol = iCol;
		valid = canMove(newRow, newCol, fl);
		if (valid) {moveRow = true;}
	}

	if (iPlayerCol < iCol && moveRow == false)
	{
		newRow = iRow;
		newCol = iCol - 1;
		valid = canMove(newRow, newCol, fl);
		if (valid) {moveCol = true;}
	}
	else if (iPlayerCol > iCol && moveRow == false)
	{
		newRow = iRow;
		newCol = iCol + 1;
		valid = canMove(newRow, newCol, fl);
		if (valid) {moveCol = true;}
	}

	//Move
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

void Creature::giveExp(Player * pl)
{
	pl->setExperience(pl->getExperience() + (getMaxHealth()/2));
	cout << "The " << getName() << " gives you " << (getMaxHealth()/2) << " exp!" << endl;
}

Creature::Creature()
{
	// Such a hostile world...
	m_bHostile = true;
	iAttackValue = 1;
}

bool Creature::isHostile()
{
	return m_bHostile;
}

void Creature::setHostile(bool bHostile)
{
	m_bHostile = bHostile;
}

int Creature::getAttackValue()
{
	return iAttackValue;
}

void Creature::setAttackValue(int attack)
{
	iAttackValue = attack;
}

void Creature::attack(Character * target)
{
	//Attack does damage based on the maxHealth of the creature
	Player * pl = dynamic_cast<Player*>(target);
	int attackValue = 0;
	if (getAttackValue() - pl->getArmor()->getDefenseBonus() < 0) {int attackValue = 0;}
	else {attackValue = getAttackValue() - pl->getArmor()->getDefenseBonus();}
	cout << "The " << getName() << " attacks and does " << attackValue << " damage!" << endl;
	int remHP = target->getHealth() - attackValue;
	if (remHP <= 0)
	{
		cout << "The vitality drains from your body, GAME OVER." << endl;
		target->setHealth(0);
	}
	else
	{
		cout << "You have " << remHP << " HP remaining!" << endl;
		target->setHealth(remHP);
	}
}

void Creature::dumpObject()
{
	cout << "Creature:" << endl;

	dumpObjectData();
}

void Creature::dumpObjectData()
{
	Character::dumpObjectData();

	cout <<  "   Hostile: ";
	if (isHostile())
	{
		cout << "true";
	}
	else
	{
		cout << "false";
	}
	cout << endl;
	
	cout << "    Attack: " << iAttackValue << endl;
}

void Creature::writeFragment(ostream & output)
{
	output << " <Creature>" << endl;

	writeDataAsFragment(output);

	output << " </Creature>" << endl;
}

void Creature::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);

	output << "	<hostile>";
	if (isHostile())
	{
		output << "true";
	}
	else
	{
		output << "false";
	}
	output	<< "</hostile>"
		<< endl;

	output << "	<attack>"
		<< getAttackValue()
		<< "</attack>"
		<<endl;
}

void Creature::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);
	
	if (sElementName == "hostile")
	{
		if (sValue == "false"){setHostile(false);}
		else {setHostile(true);}
	}
	else if (sElementName == "attack")
	{
		setAttackValue(atoi(sValue.c_str()));
	}

	//Test
	//cout << endl << endl << "Hostile: " << isHostile() << endl << endl << endl;
}

