#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
//#include "dArray.h"

using namespace std;

enum rarity {
	COMMON = 0,
	UNCOMMON,
	RARE,
	LEGENDARY,
	MYTHIC
};

enum itemTypes {
	WEAPON,
	ARMOUR
};

class Item{

public:
	Item();
    Item(int itemType, string name, int level, int buyValue, int sellValue, int rarity);
    Item(string name);
	Item(int level, int rarity);
    virtual ~Item();

    inline string debugPrint() const { return this->name;}
    virtual Item* clone() const = 0;
	virtual string toString() = 0;
	virtual string toStringSave() = 0;

    //Accessors
    inline const string& getName() const { return this->name; }
    inline const int& getLevel() const { return this->level; }
    inline const int& getBuyValue() const { return this->buyValue; }
    inline const int& getSellValue() const { return this->sellValue; }
    inline const int& getRarity() const { return this->rarity; }
	inline const int& getItemType() { return this->itemType; }
	inline std::string getTypeStr() { return this->strType; }

    //Modifiers
	inline void setName(string name) { this->name = name; }
	inline void setItemType(int type) { this->itemType = type; }

	//static
	//static vector<string> vectorNames;
	//static void initVecNames();

private:
    string name;
    int buyValue;
    int sellValue;
    int level;
    int rarity;
	int itemType;

protected:
	std::string strType;
};
#endif // ITEM_H
