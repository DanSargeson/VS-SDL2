#include "Weapon.h"

//dArray<string> Weapon::names;
//
//void Weapon::initNames() {
//	Weapon::names.push("Rusty-Sword");
//	Weapon::names.push("Iron-Sword");
//	Weapon::names.push("Titanium-Sword");
//	Weapon::names.push("Rusty-Axe");
//	Weapon::names.push("Iron-Axe");
//	Weapon::names.push("Titanium-Axe");
//}

vector<string> Weapon::vecNames;

void Weapon::initVecNames() {
	Weapon::vecNames.push_back("Rusty");
	Weapon::vecNames.push_back("Iron");
	Weapon::vecNames.push_back("Titanium");
	Weapon::vecNames.push_back("Mythril");
	Weapon::vecNames.push_back("Glass");
	Weapon::vecNames.push_back("Diamond");
}

Weapon::Weapon() : Item() {
	this->damageMax = 0;
	this->damageMin = 0;

	initVecNames();
}

Weapon::Weapon(int type, int damageMin, int damageMax, string name, int level, int buyValue, int sellValue, int rarity)
              : Item(itemTypes::WEAPON, name, level, buyValue, sellValue, rarity){
	this->type = type;
	this->damageMin = damageMin;
    this->damageMax = damageMax;

	switch (this->type) {
	case SWORD:
		this->strType = "Sword";
		break;
	case AXE:
		this->strType = "Axe";
		break;
	case DAGGER:
		this->strType = "Dagger";
		break;
	default:
		this->strType = "Type Error";
		break;
	}
}

Weapon::Weapon(int level, int rarity): Item(level, rarity) {

	this->setItemType(WEAPON);
	this->damageMax = rand() % level * (this->getRarity()+1);
	this->damageMax += (this->getRarity()+1) * 5;
	//string newName = Weapon::names[1];
	this->setName(Weapon::vecNames[rand() % Weapon::vecNames.size()]);
	//this->setName(Weapon::names[rand() % s]);
	if (this->getRarity() == 3) {
		this->damageMax += level * 5;
	}
	else if (this->getRarity() == 4) {
		this->damageMax += level * 10;
	}

	this->damageMin = damageMax / 2;
	this->type = rand() % 3;
	switch (this->type) {
	case SWORD:
		this->strType = "Sword";
		break;
	case AXE:
		this->strType = "Axe";
		break;
	case DAGGER:
		this->strType = "Dagger";
		break;

	default:
		break;
	}
	this->setName(Weapon::vecNames[this->getRarity()]);
}


Weapon::~Weapon(){

}

string Weapon::toString(){
	string str = this->getName() + " " + this->strType
		+ " | Level: " + to_string(this->getLevel()) + " "
		+ "| Rarity: " + to_string(this->getRarity()) + " "
		+ "| Damage: " + to_string(this->damageMin) + " - "
		+ to_string(this->damageMax) + " " +
		+ "| Buy Value: " + to_string(this->getBuyValue()) + " "
		+ "| Sell Value: " + to_string(this->getSellValue());

    return str;
}

string Weapon::toStringSave() {
	string str =
		to_string(this->getItemType()) + " " +
		this->getName() + " " +
		to_string(this->getLevel()) + " " +
		to_string(this->getRarity()) + " " +
		to_string(this->damageMin) + " " +
		to_string(this->damageMax) + " " +
		to_string(this->type) + " ";

	return str;
}

Weapon* Weapon::clone()const{

    return new Weapon(*this);
}
