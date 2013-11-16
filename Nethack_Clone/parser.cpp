#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <functional>
#include <vector>

#include "parser.h"
#include "XMLSerializable.h"
#include "Armor.h"
#include "Character.h"
#include "Consumable.h"
#include "Creature.h"
#include "Item.h"
#include "Player.h"
#include "Weapon.h"
#include "Potion.h"

using namespace std;

//David's Implementation
/*void parseElement(map<string, function<XMLSerializable * ()>> & mConstructors, istream & input, string sPrefix, XMLSerializable * pObject, vector<XMLSerializable*> & vWorld)
{
	string sElementName;
	getline(input, sElementName, '>');

	if( sElementName.back() == '/' )
	{
		return;
	}
	else
	{
		function<XMLSerializable * ()> pFunc = mConstructors[sElementName];

		if( pFunc != NULL )
		{
			pObject = pFunc();
			vWorld.push_back(pObject);
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


			if( pObject )
			{
				pObject->setElementData(sElementName, sContent);
			}

			return;
		}
		else
		{
			parseElement(mConstructors, input, sPrefix + " > " + sElementName, pObject, vWorld);
		}

	}

}

void parseXML(map<string, function<XMLSerializable * ()>> & mConstructors, string sFilename, vector<XMLSerializable*> & vWorld)
{
	ifstream input;
	input.open(sFilename);

	while( input.get() != '?' );
	while( input.get() != '?' );
	
	if( input.get() != '>' )
	{
		cout << "Bad XML detected" << endl;
		return;
	}

	while( input.get() != '<' );

	
	parseElement(mConstructors, input, "> ", NULL, vWorld);
	
}*/

//My implementation

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
		mapConstructor["Potion"] = []() {return new Potion;};
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
