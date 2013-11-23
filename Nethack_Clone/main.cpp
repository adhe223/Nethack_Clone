#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

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

vector<vector<char>> buildOutputVector(Floor * fl)
{
	vector<vector<char>> result;

	for (int row = 0; row < fl->getHeight(); row++)
	{
		result.push_back(vector<char>());
		for (int col = 0; col < fl->getWidth(); col++)
		{
			result[row].push_back(fl->getTile(row, col)->outputChar());
		}
	}

	return result;
}

void printLevel(vector<vector<char>> toPrint, ostream & output)
{
	for (int row = 0; row < toPrint.size(); row++)
	{
		for (int col = 0; col < toPrint[row].size(); col++)
		{
			output << toPrint[row][col];
		}
		cout << endl;
	}
}

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

int calculateScore(Player * pl)
{
	int sum = 0;
	sum = sum + (pl->getExperience()) * 2;

	//3 points for each level
	sum = sum + pl->getLevel() * 2;

	//Loop through inventory and add together the values of all items (Holy Grail bonus implemented here)
	vector<Item*> invent = pl->getInventory();
	for (int i = 0; i < invent.size(); i++)
	{
		sum = sum + invent[i]->getValue();
	}
	sum = sum + pl->getArmor()->getValue();
	sum = sum + pl->getWeapon()->getValue();

	return sum;
}

int main(int argc, char * argv[])
{
	bool newFloor = true;
	DungeonLevel * dl = new DungeonLevel(50);
	CreatureFactory & cf = CreatureFactory::instance();
	ItemFactory & itemFact = ItemFactory::instance();
	Player * pl = new Player();

	//End conditions
	bool quit = false;
	bool playerQuit = false;
	bool dead = false;
	bool exit = false;
	bool bDown = true;
	int creatureGenCount = 1;

	cout << "Basic Controls:" << endl;
	cout << "w,a,s,d - Move player" << endl;
	cout << "i - Shows inventory, you can then pick an item to use (equip if equipment) or exit" << endl;
	cout << "u - Use item on floor, equips if item is equipment, consumes the item " <<
		"if it of a consumable type. Otherwise it adds the item to inventory." << endl;
	cout << "q - Quit game and display your score" << endl << endl;

	//Main driving logic
	while (!quit)
	{
		vector<Creature *> & vCreatures = dl->getCurrentFloorObj()->getCreatures();

		if (newFloor)
		{
			//Place player in dungeon
			dl->placePlayer(pl, bDown);

			//Create and place a number between 0 and 10 items for the dungeon and put into vector
			if (!dl->getCurrentFloorObj()->getItemsPlaced())
			{
				int iNumItems = ItemFactory::randomValue(11);
				for (int i = 0; i < iNumItems; i++)
				{
					Item * toPlace = itemFact.generateItem();
					dl->placeItem(toPlace);
				}

				dl->getCurrentFloorObj()->setItemsPlaced(true);

				//If last level place the Holy Grail
				if (dl->getCurrentFloor() == dl->getNumFloors() - 1)
				{
					Item * toPlace = new Item("The Holy Grail", 'H', 10, 1000);
					dl->placeItem(toPlace);
				}
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
		//dl->getFloor(dl->getCurrentFloor())->printFloor(cout);
		vector<vector<char>> vvToPrint = buildOutputVector(dl->getCurrentFloorObj());
		printLevel(vvToPrint, cout);

		//Allow the player to enter input
		char input;
		cout << endl << "Please enter the action you want to perform: ";
		cin >> input;
		
		//Control Handling
		if (input == 'w' || input == 'a' || input == 's' || input == 'd')
		{
			pl->move(dl->getFloor(dl->getCurrentFloor()), input);
		}

		if (input == 'i')
		{
			pl->displayInventory();
		}

		if (input == 'u')
		{
			pl->use(dl->getCurrentFloorObj());
		}

		if (input == 'q')
		{
			quit = true;
			playerQuit = true;
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

		//Move mosters
		for (int i = 0; i < vCreatures.size(); i++)
		{
			vCreatures[i]->move(dl->getFloor(dl->getCurrentFloor()), pl);
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

		if (pl->getHealth() <= 0) {quit = true; dead = true;}
		if (pl->getHealth() != pl->getMaxHealth()) {pl->regen();}
		pl->levelUp();
		creatureGenCount++;

		//Check if player moved onto stairwell and needs to go to different floor
		char cOn = dl->getFloor(dl->getCurrentFloor())->getTile(pl->getRow(), pl->getCol())->getSymbol();
		if (cOn == '>' && (input == 'w' || input == 'a' || input == 's' || input == 'd'))
		{
			//Check if leaving the dungeon
			if (dl->getCurrentFloor() == 0) {quit = true; exit = true;}
			else 
			{
				dl->getFloor(dl->getCurrentFloor())->getTile(pl->getRow(), pl->getCol())->clearCharacter();
				dl->setCurrentFloor(dl->getCurrentFloor() - 1);
				bDown = false;
			}
			
			newFloor = true;
		}
		else if (cOn == '<' && (input == 'w' || input == 'a' || input == 's' || input == 'd'))
		{
			dl->getFloor(dl->getCurrentFloor())->getTile(pl->getRow(), pl->getCol())->clearCharacter();
			dl->setCurrentFloor(dl->getCurrentFloor() + 1);
			newFloor = true;
			bDown = true;
		}

		cout << endl;
	}

	int playerScore = calculateScore(pl);

	if (playerQuit)
	{
		cout << endl << "You have quit the game with a final score of " << playerScore << "!" << endl;
	}
	else if (exit)
	{
		cout << endl << "You have escaped the dungeon with a final score of " << playerScore << "!" << endl;
	}
	else
	{
		cout << endl << "Your story ends here with a final score of " << playerScore << "!" << endl; 
	}

	cin.ignore(200, '\n');
	cin.ignore(200, '\n');
	return 0;
}
