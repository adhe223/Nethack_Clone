#ifndef _parser_included_
#define _parser_included_

#include <vector>
#include <map>
#include <functional>

#include "XMLSerializable.h"

void parseXML(std::string sFilename, std::vector<XMLSerializable*> & vObjects);

#endif
