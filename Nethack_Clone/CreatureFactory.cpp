#include "CreatureFactory.h"
#include "Creature.h"
#include "XMLSerializable.h"
#include "parser.h"

#include <random>
#include <ctime>
#include <map>
#include <functional>

using namespace std;


CreatureFactory & CreatureFactory::instance()
{
	// Dummy, just to make this compile -- won't work.
//	return * static_cast<CreatureFactory*>(NULL);
	static CreatureFactory cf;
	return cf;
}

CreatureFactory::CreatureFactory()
{
	vector<XMLSerializable *> vXML;
	//map<string, function<XMLSerializable*()>> mConstructors;
	//mConstructors["Creature"] = []() {return new Creature;};
	string filename = "critters.xml";

	parseXML(filename, vXML);

	for (int i = 0; i < vXML.size(); i++)
	{
		m_vCreatures.push_back(dynamic_cast<Creature*>(vXML[i]));
	}
}

CreatureFactory::~CreatureFactory()
{
}

int CreatureFactory::randomValue(int iMax)
{
	static mt19937 mt(time(NULL));
	return mt() % iMax;
}

Creature * CreatureFactory::generateCreature(int iMaxLevel)
{
	//Create new vector of creatures with specified health
	vector<Creature*> vElig;
	for (int i = 0; i < m_vCreatures.size(); i++)
	{
		if (m_vCreatures[i]->getHealth() <= iMaxLevel) {vElig.push_back(m_vCreatures[i]);}
	}

	if (vElig.size() > 0)
	{
		int iRand = randomValue(vElig.size() - 1);
		Creature * pCreature = vElig[iRand];
		Creature * pReturnValue = new Creature(*pCreature);
		return pReturnValue;
	}

	cout << "No eligible creatures!" << endl;
	return NULL;
}
