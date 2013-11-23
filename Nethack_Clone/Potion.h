#ifndef _DungeonLevel_included_
#define _DungeonLevel_included_

#include "Consumable.h"

class Potion : public Consumable
{
public:
	Potion();
	Potion(std::string name, int iHealth); 
	Potion(Potion * po);

	virtual void use(Character * user);
	virtual int getHealthMod();
	virtual void setHealthMod(int iHealth);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

private:
	int iHealthMod;
};

#endif