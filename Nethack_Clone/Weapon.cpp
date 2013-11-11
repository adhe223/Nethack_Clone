#include "Weapon.h"

Weapon::Weapon()
{
	m_iAttackBonus = 0;
	m_iWeaponType = 0;
}

Weapon::Weapon(string name, int attackBonus, int weaponType)
{
	setName(name);
	setAttackBonus(attackBonus);
	setWeaponType(weaponType);
}

int Weapon::getAttackBonus()
{
	return m_iAttackBonus;
}

void Weapon::setAttackBonus(int iAttackBonus)
{
	m_iAttackBonus = iAttackBonus;
}

int Weapon::getWeaponType()
{
	return m_iWeaponType;
}

void Weapon::setWeaponType(int iWeaponType)
{
	m_iWeaponType = iWeaponType;
}

void Weapon::dumpObject()
{
	cout << "Weapon:" << endl;

	dumpObjectData();
}

void Weapon::dumpObjectData()
{
	Equipment::dumpObjectData();

	cout << "Attack Bonus: " << getAttackBonus() << endl;
	cout << "Weapon Type: " << getWeaponType() << endl;
}

void Weapon::writeFragment(ostream & output)
{
	output << " <Weapon>" << endl;

	writeDataAsFragment(output);

	output << " </Weapon>" << endl;
}

void Weapon::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);

	output << "	<attackBonus>"
		<< getAttackBonus()
		<< "</attackBonus>"
		<< endl
		<< "	<weaponType>"
		<< getWeaponType()
		<< "</weaponType>"
		<< endl;
}

void Weapon::setElementData(string sElementName, string sValue)
{
	Equipment::setElementData(sElementName, sValue);
	
	if (sElementName == "attackBonus")
	{
		setAttackBonus(atoi(sValue.c_str()));
	}
	else if (sElementName == "weaponType")
	{
		setWeaponType(atoi(sValue.c_str()));
	}
}
