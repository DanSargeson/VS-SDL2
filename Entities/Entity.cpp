#include "stdafx.h"
#include "Entity.h"
#include "Component.h"
#include "FactionComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include "AttackComponent.h"
#include "DialogueComponent.h"

vector<string> Entity::entityNames;

void Entity::initNames() {
	Entity::entityNames.push_back("Goblin");
	Entity::entityNames.push_back("Warlock");
	Entity::entityNames.push_back("Wolf");
	Entity::entityNames.push_back("Ghost");
	Entity::entityNames.push_back("Skeleton");
	Entity::entityNames.push_back("Rat");
	Entity::entityNames.push_back("Harpy");
	Entity::entityNames.push_back("Gremlin");
	Entity::entityNames.push_back("Berserker");
}


void Entity::InitVariables(){

	this->attributeComponent = NULL;
	this->skillComponent = NULL;
	this->dialogueComponent = NULL;
	this->factionComponent = NULL;
}

Entity::Entity(){

    initNames();
	this->InitVariables();
	this->m_name = Entity::entityNames[rand() % Entity::entityNames.size()];
}

Entity::~Entity(){

}


//Component Functions

int Entity::getLevel(){

    int a = attributeComponent->getLevel();
    return a;
}

int Entity::getHP(){

    return attributeComponent->getHP();
}

int Entity::getHPMax(){

    return attributeComponent->getHPMax();
}

void Entity::loseHP(int hp){

	this->attributeComponent->loseHP(hp);
}

void Entity::gainHP(int hp){

	this->attributeComponent->gainHP(hp);

}

void Entity::loseXP(float xp){

	this->attributeComponent->loseEXP(xp);
}

void Entity::gainXP(float xp){

	this->attributeComponent->gainEXP(xp);
}

void Entity::loseRep(int faction, int rep){

	this->factionComponent->loseRep(faction, rep);
}

void Entity::gainRep(int faction, int rep){


	this->factionComponent->gainRep(faction, rep);
}

int Entity::getSkill(int skill){

	if (this->skillComponent) {

		return this->skillComponent->getSkill(skill);
	}

	return -1;
}

int Entity::getFaction(int faction) {

	if (this->factionComponent) {

		return this->factionComponent->getReputation(faction);
	}

	return -1;
}

int Entity::getAttribute(int attribute) {

	if (this->attributeComponent) {

		return this->attributeComponent->getAttribute(attribute);
	}

	return -1;
}

int Entity::checkDurability() {

//	if (this->activeTool != NULL) {
//
//		return this->activeTool->getDurability();
//	}
//	else {

		return -1;
	//}
}

void Entity::loseDurability(){

	//TODO - NEED TO ADD A CHECK TO WHICH ITEM IS BEING USED!!
//	if (this->activeWeapon != NULL) {
//
//		this->activeWeapon->use();
//	}
//
//	if (this->activeTool != NULL) {
//
//		this->activeTool->use();
//	}
//
//	if (this->activeArms != NULL) {
//
//		this->activeArms->use();
//	}
//
//	if (this->activeHead != NULL) {
//
//		this->activeHead->use();
//	}
//
//	if (this->activeLegs != NULL) {
//
//		this->activeLegs->use();
//	}
//
//	if (this->activeChest != NULL) {
//
//		this->activeChest->use();
//	}
}

std::shared_ptr<Weapon> Entity::getActiveWeapon(){

    if(this->activeWeapon != nullptr){

        return activeWeapon;
    }
    else{

        return nullptr;
    }
}

std::shared_ptr<Armour> Entity::getActiveHead(){

    if(this->activeHead != nullptr){

        return activeHead;
    }
    else{

        return nullptr;
    }
}

std::shared_ptr<Armour> Entity::getActiveChest(){

    if(this->activeChest != nullptr){

        return activeChest;
    }
    else{

        return nullptr;
    }
}

std::shared_ptr<Armour> Entity::getActiveArms(){

    if(this->activeArms != nullptr){

        return activeArms;
    }
    else{

        return nullptr;
    }
}

std::shared_ptr<Armour> Entity::getActiveLegs(){

    if(this->activeLegs != nullptr){

        return activeLegs;
    }
    else{

        return nullptr;
    }
}

int Entity::getExp(){

    return attributeComponent->getEXP();
}

int Entity::getExpNext(){

    return attributeComponent->getEXPNext();
}

float Entity::getAttributeFloat(int attribute){

	if (this->attributeComponent) {

		return this->attributeComponent->getAttribute(attribute);
	}
	else{

        return -1.f;
	}

}


bool Entity::skillCheck(std::shared_ptr<Entity> checkAgainst, int skill1, int skill2){

    bool success = false;

    int tot1 = skill1;
    int tot2 = skill2;

    if(skillComponent && checkAgainst->getSkillComponent()){

            ///tot1 = skillComponent->getSkill(mySkill);
            tot1 += attributeComponent->getAttribute(ATTRIBUTE::LUCK);
            ///tot2 = checkAgainst->getSkill(testAgainst);
           /// tot2 += checkAgainst->getAttribute(ATTRIBUTE::LUCK);

            if(tot1 >= tot2){

                success = true;
            }
    }

    return success;
}

void Entity::calculateSkills(){

    if(attributeComponent){

        if(skillComponent){

            skillComponent->calculateSkills(attributeComponent);
        }
    }
}

void Entity::updateStats(bool s){

    if(attributeComponent){

        attributeComponent->updateStats(s);
    }
}

std::string Entity::getFactionStr() {

	return this->factionComponent->getFactionsStr();
}

int Entity::getRep(int faction){

    if(factionComponent != nullptr){

        return factionComponent->getReputation(faction);
    }
}

std::string Entity::getFactionStrSave(){

    return this->factionComponent->getFactionsStrSave();
}

std::string Entity::getFactionName(int faction){

	return factionComponent->getFactionName(faction);
}

//std::vector<std::string> Entity::getDialogueOptions(){
//
//	return this->dialogueComponent->getDialogueOptions();
//}

std::string Entity::getItemString(int index){

	std::shared_ptr<Item> item = this->inv.findItemSmart(index);

	return item->getName();
	//return item->getTypeStr();
}

bool Entity::isAlive(){

	return this->attributeComponent->getHP() > 0;
}



void Entity::createAttributeComponent(const unsigned level, const bool reset, bool enemy){

	this->attributeComponent =  std::make_shared<AttributeComponent>(this, level, reset, enemy);
}

void Entity::createSkillComponent(){

	this->skillComponent = std::make_shared<SkillComponent>(this);

	skillComponent->calculateSkills(attributeComponent);
}

void Entity::setHP(int hp){

    attributeComponent->setHP(hp);
}

void Entity::createFactionComponent(){

	this->factionComponent = std::make_shared<FactionComponent>(this);
}

void Entity::createDialogueComponent(){

	this->dialogueComponent = std::make_shared<DialogueComponent>(this);
}

void Entity::createAttackComponent(){

	this->attackComponent =  std::make_shared<AttackComponent>(this);
}

int Entity::getDamage(){

	if (this->attackComponent) {


		//Calculate base damage
		this->attackComponent->calculateElementBonus();


		if (this->activeWeapon != NULL) {

			this->attackComponent->calculateWeaponModifier(dynamic_cast<Weapon&>(*this->activeWeapon));
		}
        return this->attackComponent->getTotalDamage();
	}

	return 0;
}

void Entity::equipWeapon(int index){

    shared_ptr<Item> item = this->inv.findWeaponSmart(index);
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
				this->inv.removeItemVectorSmart(wv);
			}
		}
}

void Entity::equipArmour(int index){

     //a = dynamic_cast<Armour*>(&this->inventory[index]);
   shared_ptr<Item> item = this->inv.findArmourSmart(index);
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
					this->inv.removeItemVectorSmart(wv);
					break;

				case armourType::CHEST:
					//this->addItem(wv);
					if (this->activeChest != NULL) {
						this->addItem(this->activeChest);
					}
					this->activeChest = wv;
					this->inv.removeItemVectorSmart(wv);
					break;

				case armourType::ARMS:
					//this->addItem(wv);
					if (this->activeArms != NULL) {
						this->addItem(this->activeArms);
					}
					this->activeArms = wv;
					this->inv.removeItemVectorSmart(wv);
					break;

				case armourType::LEGS:
					//this->addItem(wv);
					if (this->activeLegs != NULL) {
						this->addItem(this->activeLegs);
					}
					this->activeLegs = wv;
					this->inv.removeItemVectorSmart(wv);

					/*	this->inventory.addItem(this->armourLegs);
						this->armourLegs = *a;
						this->inventory.removeItem(index);*/
					break;

				default:
					cout << "ERROR IN ARMOUR TYPE!\n\n";
					break;
				}
}
}

void Entity::resetHP(){

    attributeComponent->updateStats(true);
}

int Entity::getMaxDamageWithWeapon() {
	int max = 0;
	if (this->activeWeapon != NULL) {
		max = dynamic_cast<Weapon&>(*activeWeapon).getDamageMax();
	}

	//max += this->damageMax;

	return max;
}

int Entity::getMinDamageWithWeapon(){
	int min = 0;
	if (this->activeWeapon != NULL) {
		min = dynamic_cast<Weapon&>(*activeWeapon).getDamageMin();
	}

	//min += this->damageMin;

	return min;
}

int Entity::getDefence(){

    int defence = 0;
    defence += attackComponent->getTotalDefence();

    if(activeHead != nullptr){

        attackComponent->calculateArmourModifier(dynamic_cast<Armour &>(*activeHead));

        defence += attackComponent->getTotalDefence();
    }
    if(activeChest != nullptr){

        attackComponent->calculateArmourModifier(dynamic_cast<Armour &>(*activeChest));
        defence += attackComponent->getTotalDefence();
    }
    if(activeArms != nullptr){

        attackComponent->calculateArmourModifier(dynamic_cast<Armour &>(*activeArms));
        defence += attackComponent->getTotalDefence();
    }
    if(activeLegs != nullptr){

        attackComponent->calculateArmourModifier(dynamic_cast<Armour &>(*activeLegs));
        defence += attackComponent->getTotalDefence();
    }

    return defence;
}

float Entity::getPositionXSave() {

	return float();
}

float Entity::getPositionYSave() {

	return float();
}


//Functions

float Entity::calculateDefence(){

	float total = 0.0f;

	total += this->getSkill(SKILLS::DEFENCE);

	return total;
}

std::shared_ptr<Item> Entity::getItem(int index){

	return inv.findItemSmart(index);
}

void Entity::removeItem(int index){

	this->inv.removeItemVectorSmart(this->inv.findItemSmart(index));
}

void Entity::addComponent(Component * comp){

	int myOrder = comp->getUpdateOrder();

	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {

		if (myOrder < (*iter)->getUpdateOrder()) {

			break;
		}
	}

	mComponents.insert(iter, comp);
}

void Entity::removeComponent(Component * comp){

	if (!mComponents.empty()) {

		auto iter = std::find(mComponents.begin(), mComponents.end(), comp);

		if (iter != mComponents.end()) {

			mComponents.erase(iter);
		}
	}
}

void Entity::updateComponents(){

	for (auto i : mComponents) {

		i->update();
	}
}

void Entity::update(){


}

bool Entity::getDialogueActive(){

    if(dialogueComponent != nullptr){

        return dialogueComponent->getTextBoxActive();
    }
    else{

        return false;
    }
}

void Entity::setDialogueActive(bool n){

    if(dialogueComponent){

        dialogueComponent->setTextBoxActive(n);
    }
}

void Entity::setDialogueText(std::string txt){

    dialogueComponent->setDialogueText(txt);
}

void Entity::setCharacterName(std::string name){

    m_name = name;

    if(dialogueComponent != nullptr){

        dialogueComponent->setHeader(m_name);
    }
}



void Entity::renderDialogue(){

    if(dialogueComponent->getTextBoxActive()){

        dialogueComponent->render();
    }
}


void Entity::render(){

	//if (this->hitboxComponent)
	//	this->hitboxComponent->Render(target);
	//
	//target.draw(this->sprite);
}

std::string Entity::displaySkills(){

    return skillComponent->displaySkills();
}
