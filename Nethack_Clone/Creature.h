#ifndef _Creature_included_
#define _Creature_included_

#include "Character.h"
#include "Floor.h"
#include "Player.h"

class Creature : public Character
{
public:
	virtual void attack(Character * target);
	virtual void move(Floor * fl, Player * pl);
	virtual void giveExp(Player * pl);

	Creature();
	virtual bool isHostile();
	virtual void setHostile(bool bHostile);
	virtual int getAttackValue();
	virtual void setAttackValue(int attackV);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

private:
	bool canMove(int row, int col, Floor* fl);	//Helper function to check if a tile can be moved into (no monster and passable)
	bool m_bHostile;
	int iAttackValue;
};

#endif

