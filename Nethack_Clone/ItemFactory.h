#ifndef _ItemFactory_included_
#define _ItemFactory_included_

#include "Item.h"

#include <vector>

class ItemFactory
{
public:	
	static ItemFactory & instance();
	virtual ~ItemFactory();
	Item * generateItem();
	static int randomValue(int iMax);

private:
	ItemFactory();
	std::vector<Item*> m_vItems;
};

#endif