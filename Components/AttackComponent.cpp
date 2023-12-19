#include "stdafx.h"
#include "AttackComponent.h"

AttackComponent::AttackComponent(std::shared_ptr<SkillComponent> skillComp, std::shared_ptr<AttributeComponent> attriComp){

	this->skillComponent = skillComp;
	this->attributeComponent = attriComp;

	this->baseDmg = 5; ///(this->skillComponent->getSkill(SKILLS::MELEE));

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
	defMod = 0;
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

int AttackComponent::getMinDefence(){

    int minDefence = (this->skillComponent->getSkill(SKILLS::DEFENCE) * 0.10);

	///minDamage += this->skillComponent->getSkill(SKILLS::MELEE);

	return minDefence;

}

void AttackComponent::calculateArmourModifier(Armour& armourMod) {

	//USED TO  DETERMINE WETHER THE WEAPON HITS WITH MIN - MAX DAMAGE..
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(static_cast<unsigned>(seed));


	int minWeapon = armourMod.getDefence();
	int maxWeapon = armourMod.getDefence() * skillComponent->getSkill(SKILLS::DEFENCE * 0.25);

	std::uniform_int_distribution<int> dmgDist(minWeapon, maxWeapon);
	this->weaponMod = dmgDist(generator);
}

int AttackComponent::getMaxDefence(){

    int maxDef = 0;

	maxDef += (this->skillComponent->getSkill(SKILLS::DEFENCE) * 0.25);

	return maxDef;
}

///TODO POssibly bring back
void AttackComponent::calculateWeaponModifier(Weapon& weaponMod) {

	//USED TO  DETERMINE WETHER THE WEAPON HITS WITH MIN - MAX DAMAGE..
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(static_cast<unsigned>(seed));


	int minWeapon = weaponMod.getDamageMin();
	int maxWeapon = weaponMod.getDamageMax();

	std::uniform_int_distribution<int> dmgDist(minWeapon, maxWeapon);
	this->weaponMod = dmgDist(generator);
}

int AttackComponent::getBaseMinDamage(){

	int minDamage = (this->skillComponent->getSkill(SKILLS::MELEE) * 0.10);

	///minDamage += this->skillComponent->getSkill(SKILLS::MELEE);

	return minDamage;
}

int AttackComponent::getBaseMaxDamage(){

	int maxDamage = 0;

	maxDamage += (this->skillComponent->getSkill(SKILLS::MELEE) * 0.25);

	return maxDamage;
}

int AttackComponent::getTotalDamage() {


	///this->totalAttack = this->magicMod + this->baseDmg + this->weaponMod;

	///totalAttack = rand() % + getBaseMinDamage() + getBaseMaxDamage();

	 int mini = getBaseMinDamage();
    int maxi = getBaseMaxDamage();

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(static_cast<unsigned>(seed));
	std::uniform_int_distribution<int> atkDist(mini, maxi);
    totalAttack = atkDist(generator);
	return this->totalAttack;
}

int AttackComponent::getTotalDefence(){


    int mini = getMinDefence();
    int maxi = getMaxDefence();

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(static_cast<unsigned>(seed));
	std::uniform_int_distribution<int> defDist(mini, maxi);
    int totalDefence = defDist(generator);

    return totalDefence;  //TODO baseDef
}
