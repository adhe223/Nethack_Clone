#include "Equipment.h"
#include <string>

using namespace std;

string Equipment::getSlot()
{
	return m_sSlot;
}

void Equipment::setSlot(string sSlot)
{
	m_sSlot = sSlot;
}

void Equipment::dumpObject()
{
	cout << "Equipment:" << endl;

	dumpObjectData();
}

void Equipment::dumpObjectData()
{
	Item::dumpObjectData();

	cout << "      Slot: " << getSlot() << endl;
}

void Equipment::writeFragment(ostream & output)
{
	output << " <Equipment>" << endl;

	writeDataAsFragment(output);

	output << " </Equipment>" << endl;
}

void Equipment::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);

	output << "	<slot>"
		<< getSlot()
		<< "</slot>"
		<< endl;
}

void Equipment::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	
	if (sElementName == "slot")
	{
		setSlot(sValue);
	}
}
