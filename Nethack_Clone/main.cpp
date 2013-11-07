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

#include <map>
#include <vector>
#include <functional>

using namespace std;


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
		it.*/
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
	by reference to save memory.*/
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

	dumpObjects(vObjects);

	cout << "Input a filename to output the data to (inlcude .xml): ";
	string outputFile;
	cin >> outputFile;
	ofstream output;
	output.open(outputFile);

	outputXML(vObjects, output);*/
	DungeonLevel test(2);
	test.printDungeon(cout);
	
	cin.ignore(200, '\n');
	return 0;
}
