#include "Armour.h"

std::vector<string> Armour::names;

void Armour::initNames() {
	Armour::names.push_back("Rusty");
	Armour::names.push_back("Iron");
	Armour::names.push_back("Glass");
	Armour::names.push_back("Titanium");
	Armour::names.push_back("Mythril");
	Armour::names.push_back("Diamond");
}

Armour::Armour() : Item() {
	this->defence = 0;

	initNames();
}

Armour::Armour(int type, int defence, string name, int level, int buyValue, int sellValue, int rarity)
              : Item(itemTypes::ARMOUR, name, level, buyValue, sellValue, rarity){
    this->type = type;
    this->defence = defence;

	switch (this->type) {
	case armourType::HEAD:
		this->strType = "Helm";
		break;

	case armourType::CHEST:
		this->strType = "Cuirass";
		break;

	case armourType::ARMS:
		this->strType = "Gauntlets";
		break;

	case armourType::LEGS:
		this->strType = "Greaves";
		break;

	default:
		this->strType = "ERROR INVALID TYPE";
	}
}

Armour::Armour(int level, int rarity): Item(level, rarity) {

	this->setItemType(itemTypes::ARMOUR);

	this->defence = rand() % (level * (this->getRarity()+1)) + (level);
	this->defence += (this->getRarity()+1) * 2;
	this->type = rand() % 4;

	switch (this->type) {
	case armourType::HEAD:
		this->strType = "Helm";
		break;

	case armourType::CHEST:
		this->strType = "Cuirass";
		break;

	case armourType::ARMS:
		this->strType = "Gauntlets";
		break;

	case armourType::LEGS:
		this->strType = "Greaves";
		break;

	default:
		this->strType = "ERROR INVALID TYPE";
	}

	//this->setName(Armour::names[rand() % Armour::names.size()]);
	this->setName(Armour::names[this->getRarity()]);
	if (rarity == 3) {
		this->defence += level * 5;
	}
	else if (rarity == 4) {
		this->defence += level * 10;
	}
}


Armour::~Armour(){

}

Armour* Armour::clone()const{
    return new Armour(*this);
}


string Armour::toString(){
    string str = this->getName() + " " + this->strType
		+ " | Level: " + to_string(this->getLevel()) + " "
		+ "| Rarity: " + to_string(this->getRarity()) + " "
		+ "| Defence: " + to_string(this->defence) + " " +
		+"| Buy Value: " + to_string(this->getBuyValue()) + " "
		+ "| Sell Value: " + to_string(this->getSellValue());

    return str;
}

string Armour::toStringSave() {
	string str =
		to_string(this->getItemType()) + " " +
		this->getName() + " " +
		to_string(this->getLevel()) + " " +
		to_string(this->getRarity()) + " " +
		to_string(this->defence) + " " +
		to_string(this->type) + " ";

	return str;
}
