#ifndef _Character_included_
#define _Character_included_

#include "Entity.h"
#include "Floor.h"

class Character : public Entity
{
public:
	Character();

	virtual void move(Floor* fl, int dir);
	virtual void attack(Character & target);

	virtual int getHealth();
	virtual void setHealth(int iHealth);
	virtual int getRow() const;
	virtual void setRow(int row);
	virtual int getCol() const;
	virtual void setCol(int col);

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

private:
	bool canMove(int row, int col, Floor* fl);	//Helper function to check if a tile can be moved into (no monster and passable)

	int m_iHealth;
	int iRow;
	int iCol;
};

#endif
