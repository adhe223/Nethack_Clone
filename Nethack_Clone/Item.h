#ifndef _Item_included_
#define _Item_included_

#include "Entity.h"

class Item : public Entity
{
public:
	Item();
	virtual int getWeight();
	virtual void setWeight(int iWeight);
	virtual int getValue();
	virtual void setValue(int iValue);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	

private:
	int m_iWeight;
	int m_iValue;
};

#endif
