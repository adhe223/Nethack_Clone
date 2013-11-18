#include "ItemFactory.h"
#include "Item.h"
#include "XMLSerializable.h"
#include "parser.h"

#include <map>
#include <random>
#include <ctime>
#include <functional>

using namespace std;

ItemFactory & ItemFactory::instance()
{
	// Dummy, just to make this compile -- won't work.
//	return * static_cast<ItemFactory*>(NULL);
	static ItemFactory itemFact;
	return itemFact;
}

int ItemFactory::randomValue(int iMax)
{
	static mt19937 mt(time(NULL));
	return mt() % iMax;
}

ItemFactory::ItemFactory()
{
	vector<XMLSerializable *> vXML;
	//map<string, function<XMLSerializable*()>> mConstructors;
	//mConstructors["Item"] = []() {return new Item;};
	string filename = "world.xml";

	parseXML(filename, vXML);

	for (int i = 0; i < vXML.size(); i++)
	{
		if (dynamic_cast<Item*> (vXML[i]) != NULL)
		{
			m_vItems.push_back(dynamic_cast<Item*>(vXML[i]));
		}
	}
}

ItemFactory::~ItemFactory()
{
}

Item * ItemFactory::generateItem()
{
	if (m_vItems.size() > 0)
	{
		int iRand = randomValue(m_vItems.size());
		Item * pItem = m_vItems[iRand];
		Item * pReturnValue = new Item(*pItem);
		return pReturnValue;
	}

	cout << "No eligible Items!" << endl;
	return NULL;
}