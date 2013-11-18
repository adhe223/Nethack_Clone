#ifndef _Player_included_
#define _Player_included_

#include "Equipment.h"
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
	virtual void attack(Floor * fl, Character * target);
	virtual void regen();
	virtual void levelUp();
	virtual void use(Floor * fl);
	
	virtual int getExperience();
	virtual void setExperience(int iExperience);
	virtual int getLevel();
	virtual void setLevel(int iLevel);
	virtual int getScore();
	virtual Weapon * getWeapon();
	virtual Armor * getArmor();
	virtual void setWeapon(Weapon * wp);
	virtual void setArmor(Armor * ar);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	
private:
	virtual void equip(Equipment * eq);	//Helper function to equip object
	bool canMove(int row, int col, Floor* fl);	//Helper function to check if a tile can be moved into (no monster and passable)
	int m_iExperience;
	int m_iLevel;
	int regenCount;
	int score;
	
	//Have a inventory of item objects, then can equip a weapon and armor (still located in inventory)
	Weapon* weapon;
	Armor* armor;
	vector<Item*> vInventory;
};

#endif

