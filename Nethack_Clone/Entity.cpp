#include "Entity.h"
#include <string>

using namespace std;

Entity::Entity()
{
	m_cSymbol = 'X';
}

void Entity::setName(string sName)
{
	m_sName = sName;
}

string Entity::getName()
{
	return m_sName;
}

void Entity::setSymbol(char cSymbol)
{
	m_cSymbol = cSymbol;
}

char Entity::getSymbol()
{
	return m_cSymbol;
}

void Entity::dumpObject()
{
	cout << "Entity:" << endl;

	dumpObjectData();
}

void Entity::dumpObjectData()
{
	cout << "      Name: " <<  getName() << endl;
	cout << "    Symbol: " << getSymbol() << endl; 
}

void Entity::writeFragment(ostream & output)
{
	output << " <Entity>" << endl;

	writeDataAsFragment(output);

	output << " </Entity>" << endl;
}

void Entity::writeDataAsFragment(ostream & output)
{
	output << "	<name>"
		<< getName()
		<< "</name>"
		<< endl
		<< "	<symbol>"
		<< getSymbol()
		<< "</symbol>"
		<< endl;
}

void Entity::setElementData(string sElementName, string sValue)
{
	if (sElementName == "name")
	{
		setName(sValue);
	}
	else if (sElementName == "symbol")
	{
		setSymbol(sValue[0]);
	}
}
