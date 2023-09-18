#include "stdafx.h"
#include "AttackComponent.h"

AttackComponent::AttackComponent(std::shared_ptr<SkillComponent> skillComp, std::shared_ptr<AttributeComponent> attriComp){

	this->skillComponent = skillComp;
	this->attributeComponent = attriComp;

	this->baseDmg = this->skillComponent->getSkill(SKILLS::MELEE) + this->attributeComponent->getAttribute(ATTRIBUTE::STRENGTH);

	this->magicTable["NORMAL"] = 5;
	this->magicTable["FIRE"] = 5;
	this->magicTable["ICE"] = 5;
	this->magicTable["GRASS"] = 5;
	this->magicTable["EARTH"] = 5;
	this->magicTable["WATER"] = 5;
	this->magicTable["AIR"] = 5;

	this->magicMod = 0;
	this->totalAttack = 0;
	this->weaponMod = 0;
}

AttackComponent::~AttackComponent(){

}

int AttackComponent::getTotalAttack(){

	return this->totalAttack;
}

void AttackComponent::calculateElementBonus(int type) {

	switch (type) {

	case ELEMENT_TYPE::NORMAL:
		break;

	case ELEMENT_TYPE::FIRE:
		this->magicMod = magicTable["FIRE"];
		break;

	case ELEMENT_TYPE::ICE:
		this->magicMod = magicTable["ICE"];
		break;

	case ELEMENT_TYPE::GRASS:
		this->magicMod = magicTable["GRASS"];
		break;

	case ELEMENT_TYPE::WATER:
		this->magicMod = magicTable["WATER"];
		break;

	case ELEMENT_TYPE::EARTH:
		this->magicMod = magicTable["EARTH"];
		break;

	case ELEMENT_TYPE::AIR:
		this->magicMod = magicTable["AIR"];
		break;

	default:
		break;
	}
}

int AttackComponent::getMagicDamage(int type) {

	switch (type) {

	case ELEMENT_TYPE::AIR:
		return this->magicTable["AIR"];
		break;

	case ELEMENT_TYPE::EARTH:
		return this->magicTable["EARTH"];
		break;

	case ELEMENT_TYPE::FIRE:
		return this->magicTable["FIRE"];
		break;

	case ELEMENT_TYPE::GRASS:
		return this->magicTable["GRASS"];
		break;

	case ELEMENT_TYPE::ICE:
		return this->magicTable["ICE"];
		break;

	case ELEMENT_TYPE::NORMAL:
		return this->magicTable["NORMAL"];
		break;

	case ELEMENT_TYPE::WATER:
		return this->magicTable["WATER"];
		break;

	default:
		return this->magicTable["NORMAL"];
		break;
	}
}


void AttackComponent::calculateWeaponModifier(Weapon& weaponMod) {
	
	//USED TO  DETERMINE WETHER THE WEAPON HITS WITH MIN - MAX DAMAGE..
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(static_cast<unsigned>(seed));


	int minWeapon = weaponMod.getDamageMin();
	int maxWeapon = weaponMod.getDamageMax();

		//Randomly pick min or max value..

		//add to attackTotal
	std::uniform_int_distribution<int> dmgDist(minWeapon, maxWeapon);

	//dmgDist.operator();

	this->weaponMod = dmgDist(generator);
	//this->totalAttack += dmgDist(generator);

	//int attack = this->baseDmg + this->attributeComponent->getAttribute(ATTRIBUTE::STRENGTH) + this->skillComponent->getSkill(SKILLS::MELEE);

	//this->totalAttack = this->baseDmg;
}

int AttackComponent::getBaseMinDamage(){

	int minDamage = this->attributeComponent->getAttribute(ATTRIBUTE::STRENGTH * 2) + this->attributeComponent->getLevel();

	minDamage += this->skillComponent->getSkill(SKILLS::MELEE);

	return minDamage;
}

int AttackComponent::getBaseMaxDamage(){

	int maxDamage = this->attributeComponent->getAttribute(ATTRIBUTE::STRENGTH * 3) + this->attributeComponent->getLevel();

	maxDamage += this->skillComponent->getSkill(SKILLS::MELEE);

	return maxDamage;
}

int AttackComponent::getTotalDamage() {


	this->totalAttack = this->magicMod + this->baseDmg + this->weaponMod;

	return this->totalAttack;
}
