#include "Creature.h"
#include <string>

using namespace std;

Creature::Creature()
{
	// Such a hostile world...
	m_bHostile = true;
}

bool Creature::isHostile()
{
	return m_bHostile;
}

void Creature::setHostile(bool bHostile)
{
	m_bHostile = bHostile;
}

void Creature::attack(Character & target)
{
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
}

void Creature::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);
	
	if (sElementName == "hostile")
	{
		if (sValue == "false"){setHostile(false);}
		else {setHostile(true);}
	}

	//Test
	//cout << endl << endl << "Hostile: " << isHostile() << endl << endl << endl;
}

