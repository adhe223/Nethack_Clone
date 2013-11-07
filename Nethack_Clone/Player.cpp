#include "Player.h"
#include <string>

using namespace std;

Player::Player()
{
	m_iExperience = 0;
	m_iLevel = 1;
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

void Player::attack(Character & target)
{
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

