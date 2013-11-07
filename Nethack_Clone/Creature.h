#ifndef _Creature_included_
#define _Creature_included_

#include "Character.h"

class Creature : public Character
{
public:
	Creature();
	virtual bool isHostile();
	virtual void setHostile(bool bHostile);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual void attack(Character & target);

private:
	bool m_bHostile;
};

#endif

