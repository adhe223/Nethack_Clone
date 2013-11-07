#ifndef _Consumable_included_
#define _Consumable_included_

#include "Item.h"
#include "Character.h"

class Consumable : public Item
{
public:
	Consumable();
	
	virtual int getQuantity();
	virtual void setQuantity(int iQuantity);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual void use(Character & user);

private:
	int m_iQuantity;
};

#endif
