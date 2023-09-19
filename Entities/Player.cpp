#include "Player.h"
#include "State.h"
#include "FactionComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include "AttackComponent.h"
#include "Entity.h"

Player::Player() : Entity(){
    distanceTravelled = 0;

//    gold = 0;
    name = "";
//    level = 0;
//    exp = 0;
//    expNext = 0;
//
//    strength = 0;
//    vitality = 0;
//    dexterity = 0;
//    intelligence = 0;
//
//    hp = 0;
//    hpMax = 0;
//    stamina = 0;
//    staminaMax = 0;
//    damageMin = 0;
//    damageMax = 0;
//    defence = 0;
//    accuracy = 0;
//    luck = 0;


    this->createAttributeComponent(0, true);
	this->createSkillComponent();
	this->createFactionComponent();

	/*
		DEBUG - delete later
	*/
	//for (int i = 0; i < 5; i++) {

	//	attributeComponent->increaseAttribute(ATTRIBUTE::STRENGTH);
	//	attributeComponent->increaseAttribute(ATTRIBUTE::AGILITY);
	//	attributeComponent->increaseAttribute(ATTRIBUTE::LUCK);
	//}

	this->skillComponent->calculateSkills(*this->attributeComponent);
	//this->createAttackComponent(skillComponent, attributeComponent);
	createAttackComponent(skillComponent, attributeComponent);


    //statPoints = 0;
    //skillPoints = 0;

    corruption = 0;
}

Player::Player(string n, int dt, int g, int lvl, int exp, int str, int vit, int dex,
                     int intel, int hp, int stam, int stPoint, int skPoint, int corr) : Entity(){
    this->name = n;
//    this->distanceTravelled = dt;
//    this->gold = g;
//    this->level = lvl;
//    this->exp = exp;
//    this->strength = str;
//    this->vitality = vit;
//    this->dexterity = dex;
//    this->intelligence = intel;
//    this->hp = hp;
//    this->stamina = stam;
//    this->statPoints = stPoint;
//    this->skillPoints = skPoint;
    corruption = corr;
    int agi, luck, charis = 0;

    this->updateStats();
   // this->hpMax = (this->vitality * 2) + (this->strength / 2);

   this->createAttributeComponent(0, true);

   attributeComponent->loadAttribute(lvl, exp, hp, vit, str, dex, agi, intel, charis, luck);
	this->createSkillComponent();
	this->createFactionComponent();
	createAttackComponent(skillComponent, attributeComponent);
}

Player::Player(string name, int dt) : Entity(){
//    this->name = name;
    this->distanceTravelled = dt;

    this->createAttributeComponent(0, true);
	this->createSkillComponent();
	this->createFactionComponent();
}

Player::~Player(){
}

void Player::initialise(string name){
//    this->name = name;
//    this->gold = 0;
//    this->distanceTravelled = 0;
//    this->level = 1;
//    this->exp = 0;
//    this->expNext = static_cast<int>((50/3)*((pow(level,3) - 6*pow(level,2)) + 17*level - 12)) + 100;
//
//    this->strength = 5;
//    this->vitality = 5;
//    this->dexterity = 5;
//    this->intelligence = 5;
//
//    //this->hpMax = (this->vitality * 2) + (this->strength / 2);
//    this->hpMax = (this->vitality * 2) + (this->strength / 2) + level;
//    this->hp = hpMax;
//    this->staminaMax = this->vitality + (this->strength / 2) + (this->dexterity / 3);
//    this->stamina = this->staminaMax;
//    this->damageMin = this->strength;
//    this->damageMax = this->strength + 2;
//    this->defence = this->dexterity + (this->intelligence / 2);
//    this->accuracy = (this->dexterity / 2) + intelligence;
//    this->luck = this->intelligence;


    corruption = 0;
    //this->statPoints = 0;
    //this->skillPoints = 0;
}

std::string Player::printPlayerDetails(){

    std::string msg = "";
//    msg += " = Player SHEET = \n\n";
//    msg += "Name: " + this->name + " ";
//    msg += "| Level: " + std::to_string(this->level) + " ";
//    msg += "| EXP: " + std::to_string(this->exp) + " ";
//    msg += "| Exp to next level: " + std::to_string(expNext) + " ";
//    msg += "| HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax) + "\n";
//    //cout + std::setw(10) + std::setfill("=") + endl;
//    msg += "Strength: " + std::to_string(strength) + " ";
//    msg += "| Vitality: " + std::to_string(this->vitality) + " ";
//    msg += "| Dexterity: " + std::to_string(this->dexterity) + " ";
//    msg += "| Intelligence: " + std::to_string(this->intelligence) + " ";
//    //cout + std::setw(10) + std::setfill("=") + endl;
//    msg += "| Accuracy: " + std::to_string(this->accuracy) + " ";
//    msg += "| Luck: " + std::to_string(this->luck) + "\n";
//    msg += "| Stamina: " + std::to_string(this->stamina) + "/" + std::to_string(this->staminaMax) + "\n";
//    msg += "Damage: " + std::to_string(this->damageMin) + " (" +
//        std::to_string(getMinDamageWithWeapon()) + ")" + " - " + std::to_string(this->damageMax) + " (" + std::to_string(getMaxDamageWithWeapon()) + ") ";
//    msg += "| Defence: " + std::to_string(this->defence) + " (" + std::to_string(getDefenceTotal()) + ")" + " ";
//    msg += "\n";
//	msg += "Distance Travelled: " + std::to_string(this->distanceTravelled) + " ";
//	msg += "| Gold: " + std::to_string(this->gold) + "\n\n";
//	msg += "Equipped Weapon: ";
//	if (this->activeWeapon != NULL) {
//
//        auto wv = std::dynamic_pointer_cast<Weapon>(activeWeapon);
//		msg += wv->getWeaponName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}
//	msg += "Equipped Armour Head: ";
//	if (this->activeHead != NULL) {
//
//        auto wv = std::dynamic_pointer_cast<Armour>(activeHead);
//        msg += wv->getArmourName() + "\n";
////		 msg += this->activeHead->getArmourName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}
//	msg += "Equipped Armour Chest: ";
//	if (this->activeChest != NULL) {
//        auto wv = std::dynamic_pointer_cast<Armour>(activeChest);
//        msg += wv->getArmourName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}
//	msg += "Equipped Armour Arms: ";
//	if (this->activeArms != NULL) {
//		auto wv = std::dynamic_pointer_cast<Armour>(activeArms);
//        msg += wv->getArmourName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}
//	msg += "Equipped Armour Legs: ";
//	if (this->activeLegs != NULL) {
//		auto wv = std::dynamic_pointer_cast<Armour>(activeLegs);
//        msg += wv->getArmourName() + "\n";
//	}
//	else {
//		msg += " Empty\n";
//	}

	//cout << "\n";

	msg += "Nothing to show, see other tab..";

	return msg;
}

string Player::getStatsAsString() const{

//	return name + " " +
//		to_string(distanceTravelled) + " " +
//		to_string(gold) + " " +
//		to_string(level) + " " +
//		to_string(exp) + " " +
//		to_string(strength) + " " +
//		to_string(vitality) + " " +
//		to_string(dexterity) + " " +
//		to_string(intelligence) + " " +
//		to_string(hp) + " " +
//		to_string(stamina) + " " +
//		to_string(statPoints) + " " +
//		to_string(skillPoints) + " " +
//		to_string(corruption);

    return "This is old statsAsString function....";
}

std::string Player::getStatsAsStringNEW(){

	std::string deets;

	int hp, hpMax;

	hp = static_cast<int>(this->attributeComponent->getHP());
	hpMax = static_cast<int>(this->attributeComponent->getHPMax());

	int xp = static_cast<int>(this->attributeComponent->getEXP());
	int xpNext = static_cast<int>(this->attributeComponent->getEXPNext());

	deets += "Name: " + this->name + "\n";
	deets += "Level: " + std::to_string(this->attributeComponent->getLevel()) + "\n";
	deets += "HP: " + std::to_string(hp) + " / " + std::to_string(hpMax) + "\n";
	deets += "XP: " + std::to_string(xp) + " / " + std::to_string(xpNext) + "\n";
	deets += "Gold: " + std::to_string(0) + "\n";

	//deets += " = EQUIPPED ITEMS = \n";

//	deets += "Tool: ";
//
//	if (this->activeTool != NULL) {
//
//		deets += this->activeTool->getTypeStr() + "\n";
//	}
//	else {
//
//		deets += "Empty\n";
//	}
//
//	deets += "Weapon: ";
//
//	if (this->activeWeapon != NULL) {
//
//		deets += this->activeWeapon->getTypeStr() + "\n";
//	}
//	else {
//
//		deets += "Empty\n";
//	}
//
//	deets += "Head Gear: ";
//	if (this->activeHead != NULL) {
//
//		deets += this->activeHead->getTypeStr() + "\n";
//	}
//	else {
//
//		deets += "Empty\n";
//	}
//
//	deets += "Arms Gear: ";
//	if (this->activeArms != NULL) {
//
//		deets += this->activeArms->getTypeStr() + "\n";
//	}
//	else {
//
//		deets += "Empty\n";
//	}
//
//	deets += "Chest Gear: ";
//	if (this->activeChest != NULL) {
//
//		deets += this->activeChest->getTypeStr() + "\n";
//	}
//	else {
//
//		deets += "Empty\n";
//	}
//
//	deets += "Legs Gear: ";
//	if (this->activeLegs != NULL) {
//
//		deets += this->activeLegs->getTypeStr() + "\n";
//	}
//	else {
//
//		deets += "Empty\n";
//	}

	int defence = this->skillComponent->getSkill(SKILLS::DEFENCE);
//	int armour = this->getArmourRating();


	int minAttack = this->attackComponent->getBaseMinDamage();
	int maxAttack = this->attackComponent->getBaseMaxDamage();


	deets += "\nArmour Rating: " + std::to_string(defence);

//	if (armour > 0) {
//
//	 deets += "  (+" + std::to_string(armour) + ")";
//	}
	deets += "\nAttack Rating: " +  std::to_string(minAttack) + " - " + std::to_string(maxAttack);

	if (this->getMinDamageWithWeapon() > 0) {

		deets += "  (+" + std::to_string(this->getMinDamageWithWeapon()) + " - " + std::to_string(this->getMaxDamageWithWeapon()) + ")";
	}

	return deets;
}

string Player::getInvAsString() {

	return this->inventory.getInvAsString();
}

std::vector<std::string> Player::getInvAsVec(){

    return this->inventory.getInvAsVecOps();
}


string Player::getInvAsStringSave() {

	return this->inventory.getInvAsStringSave();

}

void Player::levelUp(){

    bool levelled;

    attributeComponent->updateLevel();

//    if(this->exp >= this->expNext){
//        this->exp -= this->expNext;
//        this->level++;
//        this->expNext = static_cast<int>((50/3)*((pow(level,3) - 6*pow(level,2)) + 17*level - 12)) + 100;
//
//        this->statPoints++;
//        this->skillPoints++;
//
//        //return true;
//
//        std::string msg =  "You are now level " + std::to_string(this->level) + "!";
//        StateData::GetInstance()->mainText->setString(msg);
//
//        updateStats();
//        this->hp = this->hpMax;
//    }
//    else{
//        StateData::GetInstance()->mainText->setString("You do not have enough experience.");
//        //return false;
//    }
}

void Player::updateStats(){
//    this->expNext = static_cast<int>((50/3)*((pow(level,3) - 6*pow(level,2)) + 17*level - 12)) + 100;
//
//    this->hpMax = (this->vitality * 2) + (this->strength / 2) + this->level;
//    this->staminaMax = this->vitality + (this->strength / 2) + (this->dexterity / 3);
//	this->stamina = this->staminaMax;
//    this->damageMin = this->strength + this->level;
//    this->damageMax = this->strength + this->level * 2;
//    this->defence = this->dexterity + (this->intelligence / 2);
//    this->accuracy = (this->dexterity / 2) + intelligence;
//    this->luck = this->intelligence;

	//this->hp = this->hpMax;
}

void Player::addStat(int stat, int value) {



//	if (this->statPoints < value) {
//		//cout << "Error not enough stat points!" << "\n";
//	}
//	else {
//
//		switch (stat) {
//		case 0:
//			this->strength += value;
//			break;
//		case 1:
//			this->vitality += value;
//			break;
//		case 2:
//			this->dexterity += value;
//			break;
//		case 3:
//			this->intelligence += value;
//			break;
//		default:
//			cout << "Add Stat function failed." << "\n";
//			break;
//		}
//
//		this->statPoints -= value;
//		updateStats();
//	}
}

int Player::takeDamage(int damage) {
//	damage -= this->defence;
//	if (this->activeHead != NULL) {
//		//ADD HELM DEFENCE
//		int def = dynamic_cast<Armour&>(*activeHead).getDefence();
//		damage -= def;
//
//	}
//	else if (this->activeChest != NULL) {
//		//ADD CHEST DEFENCE
//		int def = dynamic_cast<Armour&>(*activeChest).getDefence();
//		damage -= def;
//	}
//	else if (this->activeArms != NULL) {
//		//ADD ARM DEFENCE
//		int def = dynamic_cast<Armour&>(*activeArms).getDefence();
//		damage -= def;
//	}
//	else if (this->activeLegs != NULL) {
//		//ADD LEG DEFENCE
//		int def = dynamic_cast<Armour&>(*activeLegs).getDefence();
//		damage -= def;
//	}
//	if (damage <= 0) {
//		damage = 1;
//	}
//	this->hp -= damage;
//
//	if (this->hp <= 0) {
//		this->hp = 0;
//	}
//
//
//	return damage;

	return 0;
}

void Player::equipItem(int index){
	index--;
	if (index < 0 || index >= this->inventory.smrtSize()) {
		cout << "Equip item out of bounds error!\n\n";
	}
	else {

		shared_ptr<Item> item = this->inventory.findItemSmart(index);
		//auto wv = std::dynamic_pointer_cast<Weapon>(item);
		Weapon* w = nullptr;
		//w = dynamic_cast<Weapon*>(&this->inventory[index]);
		//IS WEAPON
		if (item->getItemType() == WEAPON) {
            auto wv = std::dynamic_pointer_cast<Weapon>(item);
			if (wv != nullptr) {
				if (this->activeWeapon != NULL) {
					this->addItem(this->activeWeapon);
				}
				//this->addItem(wv);
				this->activeWeapon = wv;
				this->inventory.removeItemVectorSmart(wv);
			}
		}
		else if(item->getItemType() == ARMOUR) {

			//a = dynamic_cast<Armour*>(&this->inventory[index]);
            auto wv = std::dynamic_pointer_cast<Armour>(item);
			if (wv != nullptr) {
				wv->getItemType();
				int type = dynamic_cast<Armour&>(*wv).getType();
				switch (type) {
				case armourType::HEAD:
					//this->addItem(wv);
					if (this->activeHead != NULL) {
						this->addItem(this->activeHead);
					}
					this->activeHead = wv;
					this->inventory.removeItemVectorSmart(wv);
					break;

				case armourType::CHEST:
					//this->addItem(wv);
					if (this->activeChest != NULL) {
						this->addItem(this->activeChest);
					}
					this->activeChest = wv;
					this->inventory.removeItemVectorSmart(wv);
					break;

				case armourType::ARMS:
					//this->addItem(wv);
					if (this->activeArms != NULL) {
						this->addItem(this->activeArms);
					}
					this->activeArms = wv;
					this->inventory.removeItemVectorSmart(wv);
					break;

				case armourType::LEGS:
					//this->addItem(wv);
					if (this->activeLegs != NULL) {
						this->addItem(this->activeLegs);
					}
					this->activeLegs = wv;
					this->inventory.removeItemVectorSmart(wv);

					/*	this->inventory.addItem(this->armourLegs);
						this->armourLegs = *a;
						this->inventory.removeItem(index);*/
					break;

				default:
					cout << "ERROR IN ARMOUR TYPE!\n\n";
					break;
				}
			}
			else {
				cout << "Error Trying to equip Item!\n\n";
			}
		}
	}
}

int Player::getDamage() {
	int min = 0;
	int max = 0;

	if (this->activeWeapon != NULL) {
		min = dynamic_cast<Weapon&>(*activeWeapon).getDamageMin();
		max = dynamic_cast<Weapon&>(*activeWeapon).getDamageMax();
	}

//	int minTotal = this->damageMin + min;
//	int maxTotal = this->damageMax + max;

//	int calculatedDamage = minTotal + rand() % ((maxTotal + 1) - minTotal);
//
//	return calculatedDamage;

return 0;
}

int Player::getMinDamageWithWeapon(){
	int min = 0;
	if (this->activeWeapon != NULL) {
		min = dynamic_cast<Weapon&>(*activeWeapon).getDamageMin();
	}

	//min += this->damageMin;

	return min;
}

int Player::getMaxDamageWithWeapon() {
	int max = 0;
	if (this->activeWeapon != NULL) {
		max = dynamic_cast<Weapon&>(*activeWeapon).getDamageMax();
	}

	//max += this->damageMax;

	return max;
}

int Player::getDefenceTotal(){
	int total = 0;
	int def = 0;
	if (this->activeHead != NULL) {
		def += dynamic_cast<Armour&>(*activeHead).getDefence();
	}
	if (this->activeChest != NULL) {
		def += dynamic_cast<Armour&>(*activeChest).getDefence();
	}
	if (this->activeArms != NULL) {
		def += dynamic_cast<Armour&>(*activeArms).getDefence();
	}
	if (this->activeLegs != NULL) {
		def += dynamic_cast<Armour&>(*activeLegs).getDefence();
	}

//	total = def + this->defence;

	return total;
}

string Player::getEquippedWeapon() {
	string equipped = "";

	if (this->activeWeapon != NULL) {
		equipped += this->activeWeapon->toStringSave();
	}

	return equipped;
}
//
//const int& Player::getLevel() const{
//
//    return attributeComponent->getLevel();
//}

string Player::getEquippedArmour() {

	string equipped = "";

	if (this->activeHead != NULL) {
		equipped += this->activeHead->toStringSave();
	}
	if (this->activeChest != NULL) {
		equipped += this->activeChest->toStringSave();
	}
	if (this->activeArms != NULL) {

		equipped += this->activeArms->toStringSave();
	}
	if (this->activeLegs != NULL) {
		equipped += this->activeLegs->toStringSave();
	}

	return equipped;
}
