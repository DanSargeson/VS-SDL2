#include "Item.h"



//vector<string> Item::vectorNames;
//
//void Item::initVecNames() {
//	Item::vectorNames.push_back("Rusty Sword");
//	Item::vectorNames.push_back("Iron Sword");
//	Item::vectorNames.push_back("Titanium Sword");
//	Item::vectorNames.push_back("Rusty Axe");
//	Item::vectorNames.push_back("Iron Axe");
//	Item::vectorNames.push_back("Titanium Axe");
//}

Item::Item() {
	this->itemType = -1;
	this->name = "NONE";
	this->level = 0;
	this->rarity = -1;
	this->sellValue = 0;
	this->buyValue = 0;
}

Item::Item(int level, int rarity) {
	this->name = "RANDOM ITEM";
	this->level = rand() % (level+2) + 1;
	if (rarity < 0) {
		rarity = 0;
	}
	this->rarity = rarity;
	this->buyValue = level * (this->rarity+1)*10;
	this->sellValue = this->buyValue / 2;
}

Item::Item(int itemType, string name, int level, int buyValue, int sellValue, int rarity){
	this->itemType = itemType;
	this->name = name;
    this->level = level;
    this->buyValue = buyValue;
    this->sellValue = sellValue;
    this->rarity = rarity;

	this->buyValue = level * (this->rarity + 1) * 10;
	this->sellValue = this->buyValue / 2;
}

Item::Item(string name){
    this->name = name;
}

//void Item::initVecNames() {
//
//}
//
//void Item::initNames() {
//
//}

Item::~Item(){
}
