#ifndef _CreatureFactory_included_
#define _CreatureFactory_included_

#include "Creature.h"

#include <vector>

class CreatureFactory
{
public:	
	static CreatureFactory & instance();
	virtual ~CreatureFactory();
	Creature * generateCreature(int iMaxLevel);
	static int randomValue(int iMax);

private:
	CreatureFactory();
	std::vector<Creature*> m_vCreatures;
};

#endif
