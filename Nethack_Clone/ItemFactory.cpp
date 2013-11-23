#include "ItemFactory.h"
#include "Item.h"
#include "XMLSerializable.h"
#include "parser.h"
#include "Armor.h"
#include "Weapon.h"
#include "Consumable.h"
#include "Potion.h"

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
	for (int i = 0; i < m_vItems.size(); i++)
	{
		delete m_vItems[i];
	}
}

Item * ItemFactory::generateItem()
{
	if (m_vItems.size() > 0)
	{
		int iRand = randomValue(m_vItems.size());
		Item * pItem = m_vItems[iRand];
		Item * pReturnValue = new Item(*pItem);

		//If armor, weapon, consumable, or potion we must specify
		if (dynamic_cast<Armor*>(pItem) != NULL)
		{
			Armor * ar = dynamic_cast<Armor*>(pItem);
			pReturnValue = new Armor(*ar);
		}
		else if (dynamic_cast<Weapon*>(pItem) != NULL)
		{
			Weapon * wp = dynamic_cast<Weapon*>(pItem);
			pReturnValue = new Weapon(*wp);
		}
		else if (dynamic_cast<Consumable*>(pItem) != NULL)
		{
			if (dynamic_cast<Potion*>(pItem) != NULL)
			{
				Potion * po = dynamic_cast<Potion*>(pItem);
				pReturnValue = new Potion(*po);
			}
			else
			{
				Consumable * cm = dynamic_cast<Consumable*>(pItem);
				pReturnValue = new Consumable(*cm);
			}
		}

		
		return pReturnValue;
	}

	cout << "No eligible Items!" << endl;
	return NULL;
}