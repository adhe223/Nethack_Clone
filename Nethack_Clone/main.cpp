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
	bool newFloor = true;
	DungeonLevel * dl = new DungeonLevel(5);
	CreatureFactory & cf = CreatureFactory::instance();
	ItemFactory & itemFact = ItemFactory::instance();
	Player * pl = new Player();
	bool quit = false;
	bool bDown = true;
	int creatureGenCount = 1;

	//Main driving logic
	while (!quit)
	{
		vector<Creature *> & vCreatures = dl->getCurrentFloorObj()->getCreatures();

		if (newFloor)
		{
			//Place player in dungeon
			dl->placePlayer(pl, bDown);

			//Create and place a number between 0 and 10 items for the dungeon and put into vector
			int iNumItems = ItemFactory::randomValue(11);
			for (int i = 0; i < iNumItems; i++)
			{
				dl->placeItem(itemFact.generateItem());
			}

			//Place an initial creature if none are on floor
			if (vCreatures.size() == 0)
			{
				int levelReq = 10;
				if (dl->getCurrentFloor() > 5)
				{
					levelReq = dl->getCurrentFloor() * 2;
				}

				vCreatures.push_back(cf.generateCreature(levelReq));
				dl->placeCreature(vCreatures.back());
			}

			newFloor = false;
			creatureGenCount = 1;
		}
	
		cout << "Floor: " << dl->getCurrentFloor() << endl;
		dl->getFloor(dl->getCurrentFloor())->printFloor(cout);
		
		//Allow the player to enter input
		char input;
		cout << endl << "Please enter the action you want to perform: ";
		cin >> input;
		
		//Control Handling
		if (input == 'w' || input == 'a' || input == 's' || input == 'd')
		{
			pl->move(dl->getFloor(dl->getCurrentFloor()), input);
		}

		if (input == 'u')
		{
			pl->use(dl->getCurrentFloorObj());
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
				//remove from the map and delete the creature. Only one will die each turn so we can return
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
				bDown = false;
			}
			
			newFloor = true;
		}
		else if (cOn == '<')
		{
			dl->getFloor(dl->getCurrentFloor())->getTile(pl->getRow(), pl->getCol())->clearCharacter();
			dl->setCurrentFloor(dl->getCurrentFloor() + 1);
			newFloor = true;
			bDown = true;
		}

		cout << endl;
	}
	cout << endl << "You have escaped the dungeon with a final score of " << pl->getExperience() * 2 << "!" << endl;

	cin.ignore(200, '\n');
	cin.ignore(200, '\n');
	return 0;
}
