#ifndef ATTACKCOMPONENT_H
#define ATTACKCOMPONENT_H

#include "SkillComponent.h"
#include "AttributeComponent.h"
#include "Weapon.h"


enum ELEMENT_TYPE {

	NORMAL = 0,
	ICE,
	FIRE,
	GRASS,
	EARTH,
	WATER,
	AIR
};


class AttackComponent{

private:

	//SkillComponent* skillComponent;
	std::shared_ptr<class SkillComponent> skillComponent;
	//AttributeComponent* attributeComponent;
	std::shared_ptr<AttributeComponent> attributeComponent;

	std::map<std::string, int> magicTable;

	int baseDmg;
	int magicMod;
	int weaponMod;
	int totalAttack;


public:

	AttackComponent(std::shared_ptr<SkillComponent> skillComp, std::shared_ptr<AttributeComponent> attriComp);
	virtual ~AttackComponent();

	int getTotalAttack();
	void calculateElementBonus(int type = 0);
	int getMagicDamage(int type);
	void calculateWeaponModifier(Weapon& weaponMod);

	int getBaseMinDamage();
	int getBaseMaxDamage();
	int getTotalDamage();
};

#endif
