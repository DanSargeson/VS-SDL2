#ifndef ARMOUR_H
#define ARMOUR_H

#include "Item.h"

const int factionWeight = 25;   ///USED TO SORT THE COLOUR

enum armourType {
	HEAD = 0,
	CHEST,
	ARMS,
	LEGS
};

class Armour : public Item{

private:
    int type;
	//string strType;
    int defence;

public:
	Armour();
    Armour(int type, int defence, string name, int level, int buyValue, int sellValue, int rarity);
	Armour(int level, int rarity);
	virtual ~Armour();

    virtual Armour* clone() const;

    string toString();
	string toStringSave();

	//ACCESSORS
	inline int getDefence() const { return this->defence; }
	inline int getType() const { return this->type; }
//	inline string getTypeStr() { return this->strType; }
	inline string getArmourName() { string n = this->getName(); n += " " + getTypeStr(); return n; }

	//static
	///static dArray<string> names;
	static vector<string> names;
	static void initNames();
};

#endif // ARMOUR_H
