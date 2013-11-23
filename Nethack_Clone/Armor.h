#ifndef _Armor_included_
#define _Armor_included_

#include "Equipment.h"

class Armor : public Equipment
{
public:
	Armor();
	Armor(std::string name, char symbol, int value, int weight, int iDefenseBonus);
	Armor(Armor * ar);

	virtual int getDefenseBonus();
	virtual void setDefenseBonus(int iDefenseBonus);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	
private:
	int m_iDefenseBonus;
};

#endif

