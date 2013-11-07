#ifndef _Entity_included_
#define _Entity_included_

#include <string>
#include <ostream>

#include "XMLSerializable.h"

using namespace std;

class Entity : public XMLSerializable
{
public:
	Entity();
	std::string getName();
	virtual void setName(std::string sString);
	virtual char getSymbol();
	virtual void setSymbol(char cSymbol);


	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	
private:
	std::string m_sName;
	char m_cSymbol;
};

#endif

