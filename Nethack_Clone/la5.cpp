include <iostream>
#include <map>
#include <string>
#include <functional>
#include "Armor.h"
#include "Weapon.h"
#include "Item.h"
#include "Creature.h"
#include "XMLSerializable.h"
using namespace std;

XMLSerializable* constructItem() {
	return new Item;
}
  
int main() {
string sLookup;
map<string, function<XMLSerializable*()>> mapConstructor;

mapConstructor["Item"] = constructItem;
mapConstructor["Creature"] = []() {return new Creature;};
mapConstructor["Armor"] = []() {return new Armor;};
mapConstructor["Weapon"] = []() {return new Weapon;};

cout << "What class would you like to lookup?: ";
cin >> sLookup;

function<XMLSerializable*()> pFunc = mapConstructor[sLookup];

if (pFunc == NULL) {
	cout << "No class exists!";
} else {
	pFunc();
	cout << "Non Null came back from the value!";
}

cin.ignore(200, '\n');
cin.ignore(200, '\n');
return 0;
}
