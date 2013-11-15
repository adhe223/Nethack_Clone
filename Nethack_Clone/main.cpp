#include <iostream>
#include <string>
#include <fstream>

#include "Entity.h"
#include "Item.h"
#include "Consumable.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Armor.h"
#include "Character.h"
#include "Creature.h"
#include "Player.h"
#include "DungeonLevel.h"
#include "Tile.h"
#include "Floor.h"
#include "XMLSerializable.h"
#include "parser.h"
#include "CreatureFactory.h"
#include "ItemFactory.h"

#include <map>
#include <vector>
#include <functional>

using namespace std;

/* Moved to parser.cpp
//input file, prefix is spacing organizer, map of constructors, vector of objects we have
void parseElement(istream & input, string sPrefix,
		map<string, function<XMLSerializable*()>> & mConstructors, vector<XMLSerializable*> & vObjects,
			XMLSerializable * pObject)
{
	string sElementName;
	getline(input, sElementName, '>');
	function<XMLSerializable*()> pFunc = mConstructors[sElementName];


	if( sElementName.back() == '/' )
	{
		cout << sPrefix << "Empty element: " << sElementName << endl;
		return;
	}
	else
	{
		//cout << sPrefix << "Element - " << sElementName << endl;
		
		/*Now that we have the name of the tag, we try to construct a class. We will attempt
		to find the name in our dictionary of constructors and if it is found we will create
		it.
		//We must pass the object into the recursive calls

		if (pFunc != NULL)
		{
			pObject = NULL;	//Do this to reset (so we don't have a leftover pointer
			pObject = pFunc(); //Constructs our new vector
		}
	}

	string sContent = "";


	while( true )
	{

		char c = input.get();

		while( c != '<' )
		{
			if( c != '\n' )
				sContent.push_back(c);

			c = input.get();
		}

		if( input.peek() == '/' )
		{
			input.get();
			string sEndElement;
			getline(input, sEndElement, '>');

			if( sEndElement != sElementName )
				cout << "Bad XML found" << endl;


			//cout << sPrefix << "Content - " << sContent << endl;

			if (pObject != NULL)
			{
				pObject->setElementData(sElementName, sContent); //Sets the data of our new object
			}

			//Make sure the objectis one of our main classes before storing in vector
			if (pFunc != NULL)
			{
				vObjects.push_back(pObject);
			}

			return;
		}
		else
		{
			parseElement(input, sPrefix + "  ", mConstructors, vObjects, pObject);
		}

	}

}

void parseXML(string sFilename, vector<XMLSerializable*> & vObjects)
{
	ifstream input;
	input.open(sFilename);
	
	/*Initialize the map for our constructors here, then we'll pass it to parseElement
	by reference to save memory.
	map<string, function<XMLSerializable*()>> mapConstructor;

	mapConstructor["Item"] = []() {return new Item;};
	mapConstructor["Creature"] = []() {return new Creature;};
	mapConstructor["Armor"] = []() {return new Armor;};
	mapConstructor["Weapon"] = []() {return new Weapon;};
	mapConstructor["Entity"] = []() {return new Entity;};
	mapConstructor["Character"] = []() {return new Character;};
	mapConstructor["Consumable"] = []() {return new Consumable;};
	mapConstructor["Equipment"] = []() {return new Equipment;};
	mapConstructor["Character"] = []() {return new Character;};
	mapConstructor["Player"] = []() {return new Player;};

	while( input.get() != '?' );
	while( input.get() != '?' );
	
	if( input.get() != '>' )
	{
		cout << "Bad XML detected" << endl;
		return;
	}

	while( input.get() != '<' );

	XMLSerializable* pNull = NULL;
	parseElement(input, "", mapConstructor, vObjects, pNull);
	
	return;
}
*/

void dumpObjects(vector <XMLSerializable*> vObjects) {
	for (auto pObject : vObjects) {
		pObject->dumpObject();
		cout << endl;
	}	
}

void outputXML(vector<XMLSerializable*> & vObjects, ostream & output)
{
	output << "<?xml version=\"1.0\" encoding = \"utf-8\"?>"
		<< endl
		<< "<World>"
		<< endl;

	for (auto it = vObjects.begin(); it != vObjects.end(); it++)
	{
		(*it)->writeFragment(output);
	}

	output << "</World>" << endl;
}

int main(int argc, char * argv[])
{
	/*cout << "What file should we parse? ";
	string sFilename;
	cin >> sFilename;

	vector<XMLSerializable*> vObjects;
	parseXML(sFilename, vObjects);

	//dumpObjects(vObjects);

	cout << "Input a filename to output the data to (inlcude .xml): ";
	string outputFile;
	cin >> outputFile;
	ofstream output;
	output.open(outputFile);

	outputXML(vObjects, output);
	*/
	bool newFloor = true;
	DungeonLevel * dl = new DungeonLevel(5);
	CreatureFactory & cf = CreatureFactory::instance();
	ItemFactory & itemFact = ItemFactory::instance();
	Player * pl = new Player();
	bool quit = false;
	int creatureGenCount = 1;

	vector<Creature *> vCreatures;

	//Main driving logic
	while (!quit)
	{
		if (newFloor)
		{
			//Place player in dungeon
			dl->placePlayer(pl);

			vCreatures = dl->getFloor(dl->getCurrentFloor())->getCreatures();

			//Create and place a number between 0 and 10 items for the dungeon and put into vector
			int iNumItems = ItemFactory::randomValue(11);
			for (int i = 0; i < iNumItems; i++)
			{
				dl->placeItem(itemFact.generateItem());
			}

			//Place an initial creature
			int levelReq = 10;
			if (dl->getCurrentFloor() > 5)
			{
				levelReq = dl->getCurrentFloor() * 2;
			}

			vCreatures.push_back(cf.generateCreature(levelReq));
			dl->placeCreature(vCreatures.back());

			newFloor = false;
			creatureGenCount = 1;
		}
	
		cout << "Floor: " << dl->getCurrentFloor() << endl;
		dl->getFloor(dl->getCurrentFloor())->printFloor(cout);
		
		//Allow the player to enter input
		char input;
		cout << endl << "Please enter the action you want to perform: ";
		cin >> input;
		
		if (input == 'w' || input == 'a' || input == 's' || input == 'd')
		{
			pl->move(dl->getFloor(dl->getCurrentFloor()), input);
		}

		//Move mosters
		for (int i = 0; i < vCreatures.size(); i++)
		{
			vCreatures[i]->move(dl->getFloor(dl->getCurrentFloor()), pl);
		}

		//Delete dead monsters
		int size = vCreatures.size();
		for (int i = 0; i < size; i++)
		{
			if (vCreatures[i]->getHealth() <= 0)
			{
				//remove from the map and delete the create. Only one will die each turn so we can return
				//after handling the death of a creature
				Creature * toDelete = vCreatures[i];
				vCreatures.erase(vCreatures.begin() + i);	//Remove from creature vector
				dl->getFloor(dl->getCurrentFloor())->getTile(toDelete->getRow(), toDelete->getCol())->clearCharacter();	//Clear tile
				delete toDelete;	//delete object
				size = size - 1;
			}
		}

		//Add more creatures every nth turn
		if (creatureGenCount % 17 == 0)
		{
			creatureGenCount = 1;
			int levelReq = 10;
			if (dl->getCurrentFloor() > 5)
			{
				levelReq = dl->getCurrentFloor() * 2;
			}
			vCreatures.push_back(cf.generateCreature(levelReq));
			dl->placeCreature(vCreatures.back());
		}

		if (pl->getHealth() <= 0) {quit = true;}
		if (pl->getHealth() != pl->getMaxHealth()) {pl->regen();}
		pl->levelUp();
		creatureGenCount++;

		//Check if player moved onto stairwell and needs to go to different floor
		char cOn = dl->getFloor(dl->getCurrentFloor())->getTile(pl->getRow(), pl->getCol())->getSymbol();
		if (cOn == '>')
		{
			//Check if leaving the dungeon
			if (dl->getCurrentFloor() == 0) {quit = true;}
			else 
			{
				dl->getFloor(dl->getCurrentFloor())->getTile(pl->getRow(), pl->getCol())->clearCharacter();
				dl->setCurrentFloor(dl->getCurrentFloor() - 1);
			}
			
			newFloor = true;
		}
		else if (cOn == '<')
		{
			dl->getFloor(dl->getCurrentFloor())->getTile(pl->getRow(), pl->getCol())->clearCharacter();
			dl->setCurrentFloor(dl->getCurrentFloor() + 1);
			newFloor = true;
		}

		cout << endl;
	}
	cout << endl << "You have escaped the dungeon with a final score of " << pl->getExperience() * 2 << "!" << endl;

	cin.ignore(200, '\n');
	cin.ignore(200, '\n');
	return 0;
}
