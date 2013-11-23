#include "Item.h"
#include <string>

using namespace std;

Item::Item()
{
	m_iWeight = 0;
	m_iValue = 0;
}

Item::Item(string name, char symbol, int weight, int value)
{
	setName(name);
	setSymbol(symbol);
	m_iWeight = weight;
	m_iValue = value;
}

void Item::setWeight(int iWeight)
{
	m_iWeight = iWeight;
}

int Item::getWeight()
{
	return m_iWeight;
}

void Item::setValue(int iValue)
{
	m_iValue = iValue;
}

int Item::getValue()
{
	return m_iValue;
}

void Item::dumpObject()
{
	cout << "Item:" << endl;

	dumpObjectData();
}

void Item::dumpObjectData()
{
	Entity::dumpObjectData();

	cout << "    Weight: " << getWeight() << endl;
	cout << "     Value: " << getValue() << endl;
}

void Item::writeFragment(ostream & output)
{
	output << " <Item>" << endl;

	writeDataAsFragment(output);

	output << " </Item>" << endl;
}

void Item::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);

	output << "	<weight>"
		<< getWeight()
		<< "</weight>"
		<< endl
		<< "	<value>"
		<< getValue()
		<< "</value>"
		<< endl;
}

void Item::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);
	
	if (sElementName == "value")
	{
		setValue(atoi(sValue.c_str()));
	}
	else if (sElementName == "weight")
	{
		setWeight(atoi(sValue.c_str()));
	}
}
