#ifndef _Armor_included_
#define _Armor_included_

#include "Equipment.h"

class Armor : public Equipment
{
public:
	Armor();
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

