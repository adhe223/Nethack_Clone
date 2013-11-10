#include "Consumable.h"
#include <string>

using namespace std;

Consumable::Consumable()
{
	m_iQuantity = 1;
}

int Consumable::getQuantity()
{
	return m_iQuantity;
}

void Consumable::setQuantity(int iQuantity)
{
	m_iQuantity = iQuantity;
}

void Consumable::use(Character * user)
{
}

void Consumable::dumpObject()
{
	cout << "Consumable:" << endl;

	dumpObjectData();
}

void Consumable::dumpObjectData()
{
	Item::dumpObjectData();

	cout << "  Quantity: " << getQuantity() << endl;
}

void Consumable::writeFragment(ostream & output)
{
	output << " <Consumable>" << endl;

	writeDataAsFragment(output);

	output << " </Consumable>" << endl;
}

void Consumable::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);

	output << "	<quantity>"
		<< getQuantity()
		<< "</quantity>"
		<< endl;
}

void Consumable::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	
	if (sElementName == "quantity")
	{
		setQuantity(atoi(sValue.c_str()));
	}
}
