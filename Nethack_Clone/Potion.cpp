#include "Potion.h"

using namespace std;

Potion::Potion()
{
	iHealthMod = 5;
}

Potion::Potion(string name, int iHealth)
{
	setName(name);
	iHealthMod = iHealth;
}

Potion::Potion(Potion * po)
{
	setName(po->getName());
	setSymbol(po->getSymbol());
	setValue(po->getValue());
	setWeight(po->getWeight());
	setQuantity(po->getQuantity());
	iHealthMod = po->getHealthMod();
}

int Potion::getHealthMod()
{
	return iHealthMod;
}

void Potion::setHealthMod(int iHealth)
{
	iHealthMod = iHealth;
}

void Potion::use(Character * user)
{
	user->setHealth(user->getHealth() + iHealthMod);
	cout << "Health potion applied!" << endl;
	cout << "You know have " << user->getHealth() << " hp!" << endl;
}

void Potion::dumpObject()
{
	cout << "Consumable:" << endl;

	dumpObjectData();
}

void Potion::dumpObjectData()
{
	Consumable::dumpObjectData();

	cout << "Health Mod: " << getHealthMod() << endl;
}

void Potion::writeFragment(ostream & output)
{
	output << " <Potion>" << endl;

	writeDataAsFragment(output);

	output << " </Potion>" << endl;
}

void Potion::writeDataAsFragment(ostream & output)
{
	Consumable::writeDataAsFragment(output);

	output << "	<healthmod>"
		<< getHealthMod()
		<< "</healthmod>"
		<< endl;
}

void Potion::setElementData(string sElementName, string sValue)
{
	Consumable::setElementData(sElementName, sValue);
	
	if (sElementName == "healthmod")
	{
		setHealthMod(atoi(sValue.c_str()));
	}
}



