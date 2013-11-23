#ifndef _Weapon_included_
#define _Weapon_included_

#include "Equipment.h"

class Weapon : public Equipment
{
public:
	Weapon();
	Weapon(string name, char symbol, int value, int weight, int attackBonus, int weaponType);
	Weapon(Weapon * wp);

	virtual int getAttackBonus();
	virtual void setAttackBonus(int iAttackBonus);
	virtual int getWeaponType();
	virtual void setWeaponType(int iWeaponType);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

private:
	int m_iAttackBonus;
	int m_iWeaponType;
};

#endif

