#include "Armor.h"
#include <string>

using namespace std;

Armor::Armor()
{
	m_iDefenseBonus = 0;
}

Armor::Armor(string name, char symbol, int value, int weight, int iDefenseBonus)
{
	setName(name);
	setSymbol(symbol);
	setValue(value);
	setWeight(weight);
	m_iDefenseBonus = iDefenseBonus;
}

Armor::Armor(Armor * ar)
{
	setName(ar->getName());
	setSymbol(ar->getSymbol());
	setValue(ar->getValue());
	setWeight(ar->getWeight());
	setSlot(ar->getSlot());
	m_iDefenseBonus = ar->getDefenseBonus();
}

int Armor::getDefenseBonus()
{
	return m_iDefenseBonus;
}

void Armor::setDefenseBonus(int iDefenseBonus)
{
	m_iDefenseBonus = iDefenseBonus;
}

void Armor::dumpObject()
{
	cout << "Armor:" << endl;

	dumpObjectData();
}

void Armor::dumpObjectData()
{
	Equipment::dumpObjectData();

	cout << "Defense Bonus: " << getDefenseBonus() << endl;
}

void Armor::writeFragment(ostream & output)
{
	output << " <Armor>" << endl;

	writeDataAsFragment(output);

	output << " </Armor>" << endl;
}

void Armor::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);

	output << "	<defenseBonus>"
		<< getDefenseBonus()
		<< "</defenseBonus>"
		<< endl;
}

void Armor::setElementData(string sElementName, string sValue)
{
	Equipment::setElementData(sElementName, sValue);
	
	if (sElementName == "defenseBonus")
	{
		setDefenseBonus(atoi(sValue.c_str()));
	}
}