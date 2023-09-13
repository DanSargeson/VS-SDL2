#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

void Entity::InitVariables(){

//	this->attributeComponent = NULL;
//	this->skillComponent = NULL;
//	this->dialogueComponent = NULL;
	this->factionComponent = NULL;
}

Entity::Entity(){

	this->InitVariables();

}

Entity::~Entity(){

}


//Component Functions

void Entity::loseHP(int hp){

//	this->attributeComponent->loseHP(hp);
}

void Entity::gainHP(int hp){

//	this->attributeComponent->gainHP(hp);

}

void Entity::loseXP(float xp){

//	this->attributeComponent->loseEXP(xp);

}

void Entity::gainXP(float xp){

//	this->attributeComponent->gainEXP(xp);
}

void Entity::loseRep(int faction, int rep){

	this->factionComponent->loseRep(faction, rep);
}

void Entity::gainRep(int faction, int rep){


	this->factionComponent->gainRep(faction, rep);
}

int Entity::getSkill(int skill){

//	if (this->skillComponent) {
//
//		return this->skillComponent->getSkill(skill);
//	}

	return -1;
}

int Entity::getFaction(int faction) {

	if (this->factionComponent) {

		return this->factionComponent->getReputation(faction);
	}

	return -1;
}

int Entity::getAttribute(int attribute) {

//	if (this->attributeComponent) {
//
//		return this->attributeComponent->getAttribute(attribute);
//	}

	return -1;
}

int Entity::checkDurability() {

	//if (this->activeTool != NULL) {

	//	return this->activeTool->getDurability();
	//}
	//else {

		return -1;
	//}
}

void Entity::loseDurability(){

	//TODO - NEED TO ADD A CHECK TO WHICH ITEM IS BEING USED!!
	//if (this->activeWeapon != NULL) {

	//	this->activeWeapon->use();
	//}

	//if (this->activeTool != NULL) {

	//	this->activeTool->use();
	//}

	//if (this->activeArms != NULL) {

	//	this->activeArms->use();
	//}

	//if (this->activeHead != NULL) {

	//	this->activeHead->use();
	//}

	//if (this->activeLegs != NULL) {

	//	this->activeLegs->use();
	//}

	//if (this->activeChest != NULL) {

	//	this->activeChest->use();
	//}
}

//float Entity::getAttributeFloat(int attribute){
//
//	if (this->attributeComponent) {
//
//		return this->attributeComponent->getAttributeFloat(attribute);
//	}
//
//	return -1.f;
//}

std::string Entity::getFactionStr() {

	return this->factionComponent->getFactionsStr();
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

//	return this->attributeComponent->getHP() > 0;
}

void Entity::setMapID(int id){

//	this->mapID = id;
}


//void Entity::createAttributeComponent(const unsigned level, const bool reset, bool enemy){
//
//	this->attributeComponent =  std::make_shared<AttributeComponent>(this, level, reset, enemy);
//}
//
//void Entity::createSkillComponent(){
//
//	this->skillComponent = std::make_shared<SkillComponent>(this);
//}

void Entity::createFactionComponent(){

	this->factionComponent = std::make_shared<FactionComponent>(this);
}

//void Entity::createDialogueComponent(){
//
//	this->dialogueComponent = std::make_shared<DialogueComponent>(this);
//}
//
//void Entity::createAttackComponent(std::shared_ptr<SkillComponent> skillComp, std::shared_ptr<AttributeComponent> attriComp){
//
//	this->attackComponent =  std::make_shared<AttackComponent>(skillComp, attriComp);
//}

int Entity::getDamage(){

	//if (this->attackComponent) {


	//	//Calculate base damage
	//	this->attackComponent->calculateElementBonus();


	//	if (this->activeWeapon != NULL) {

	//		this->attackComponent->calculateWeaponModifier(dynamic_cast<Weapon&>(*this->activeWeapon));
	//	}
	//}

	//return this->attackComponent->getTotalDamage();
	return 0;
}

int Entity::getDefence()
{
	return 0;
}

float Entity::getPositionXSave() {

	return float();
}

float Entity::getPositionYSave() {

	return float();
}


//Functions

void Entity::setPosition(const float x, const float y){

	//if (this->hitboxComponent) {

	//	this->sprite.setPosition(x, y);
	//	this->hitboxComponent->SetPosition(x, y, this->sprite);
	//}
	//else {

	//	  this->sprite.setPosition(x, y);
	//}
}

float Entity::calculateDefence(){

	float total = 0.0f;

	//total += this->getSkill(SKILLS::DEFENCE);

	return 0.0f;
}

//std::shared_ptr<Item> Entity::getItem(int index){
//
//	return inv.findItemSmart(index);
//}

void Entity::removeItem(int index){

	//this->inv.removeItemVectorSmart(this->inv.findItemSmart(index));
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

		//auto iter = std::find(mComponents.begin(), mComponents.end(), comp);

		//if (iter != mComponents.end()) {

		//	mComponents.erase(iter);
		//}
	}
}

void Entity::updateComponents(){

	for (auto i : mComponents) {

		i->update();
	}
}

void Entity::update(){


}

void Entity::render(SDL_Renderer* target){

	//if (this->hitboxComponent)
	//	this->hitboxComponent->Render(target);
	//
	//target.draw(this->sprite);
}
