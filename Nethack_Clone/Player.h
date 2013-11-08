#ifndef _Player_included_
#define _Player_included_

#include "Character.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Floor.h"
#include <vector>

class Player : public Character
{
public:
	Player();

	virtual void move(Floor* fl, char dir);
	bool canMove(int row, int col, Floor* fl);	//Helper function to check if a tile can be moved into (no monster and passable)
	virtual void attack(Character & target);

	virtual int getExperience();
	virtual void setExperience(int iExperience);
	virtual int getLevel();
	virtual void setLevel(int iLevel);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	
private:
	int m_iExperience;
	int m_iLevel;
	
	//Have a inventory of item objects, then can equip a weapon and armor (still located in inventory)
	Weapon* weapon;
	Armor* armor;
	vector<Item*> vInventory;
};

#endif

