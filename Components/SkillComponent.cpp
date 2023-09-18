#include "stdafx.h"
#include "SkillComponent.h"
#include "AttributeComponent.h"

SkillComponent::SkillComponent(Entity* owner) : Component(owner) {


	/*
	
	Split colours into two skills each, if the player joins the red team they will gain extra vit and melee, blue is extra ranged and defence,
	
	green/yellow is accuracy and endurance???


	Possibly reblance.


				
				

	
	*/
	mSkills.push_back(Skill(SKILLS::MELEE));			//UNARMED AND MELEE WEAPONS
	mSkills.push_back(Skill(SKILLS::RANGED));			//BOWS AND THROWING WEAPONS
	mSkills.push_back(Skill(SKILLS::DEFENCE));			//BLOCK CHANCE
	mSkills.push_back(Skill(SKILLS::ACCURACY));		//HIT CHANCE
	mSkills.push_back(Skill(SKILLS::MAGIC));			//MAGIC CHANCE - MAYBE CHANGE TO ELEMENTAL????
	mSkills.push_back(Skill(SKILLS::STEALTH));			//CHANCE TO BE DETECTED AND CAHNCE CAUGHT STEALING
	mSkills.push_back(Skill(SKILLS::LOCKPICKING));		//PICKING LOCKS
	mSkills.push_back(Skill(SKILLS::PERSUASION));		//DIALOGUE OPTIONS - CHANCE TO PERSUADE/INFLUENCE
	mSkills.push_back(Skill(SKILLS::PERCEPTION));		//CHANCE TO DETECT TRAPS AND SEE THROUGH LIARS??
}

SkillComponent::~SkillComponent(){


}

int SkillComponent::getSkill(const unsigned int skill) {
	
	try {

		if (skill < 0 || skill >= mSkills.size()) {

			throw std::runtime_error("Error::SKILLCOMPONENT::GetSkill - skill not found: " + skill);
		}
		else {

			return mSkills[skill].getLevel();
		}
	}
	catch (std::exception e) {

		std::ofstream outFile;

		outFile.open("errorLog.txt");

		if (outFile.is_open()) {

			outFile << e.what() << std::endl;

			outFile.close();
		}
	}

	return -1;
}

void SkillComponent::gainExp(const unsigned int skill, const int xp){

	try {


		if (skill < 0 || skill >= mSkills.size()) {

			throw std::runtime_error("Error::SKILLCOMPONENT::GainEXP - skill not found: " + skill);
		}
		else {


			mSkills[skill].gainExp(xp);
		}
	}
	catch (std::exception e) {

		std::ofstream outFile;

		outFile.open("errorLog.txt");

		if (outFile.is_open()) {

			outFile << e.what() << std::endl;

			outFile.close();
		}
	}
}


void SkillComponent::increaseSkill(int skill){

	mSkills[skill].setLevel(mSkills[skill].getLevel() + 1);
	if (mSkills[skill].getLevel() >= 100) {

		mSkills[skill].setLevel(100);
	}

	std::cout << "New value: " + std::to_string(mSkills[skill].getLevel()) + "\n";
}

void SkillComponent::loadSkills(int skill, int value){

	switch (skill) {

	case SKILLS::ACCURACY:
		
		mSkills[SKILLS::ACCURACY].setLevel(value);
		break;

	case SKILLS::DEFENCE:

		mSkills[SKILLS::DEFENCE].setLevel(value);
		break;

	case SKILLS::LOCKPICKING:

		mSkills[SKILLS::LOCKPICKING].setLevel(value);
		break;

	/*case SKILLS::LUCK:

		skills[SKILLS::LUCK].setLevel(value);
		break;*/

	case SKILLS::MAGIC:

		mSkills[SKILLS::MAGIC].setLevel(value);
		break;

	case SKILLS::MELEE:

		mSkills[SKILLS::MELEE].setLevel(value);
		break;

	case SKILLS::PERCEPTION:

		mSkills[SKILLS::PERCEPTION].setLevel(value);
		break;

	case SKILLS::PERSUASION:

		mSkills[SKILLS::PERSUASION].setLevel(value);
		break;

	case SKILLS::RANGED:

		mSkills[SKILLS::RANGED].setLevel(value);
		break;

	case SKILLS::STEALTH:

		mSkills[SKILLS::STEALTH].setLevel(value);
		break;
	}
}

std::string SkillComponent::getSkillName(int skill){

	int type = mSkills[skill].getType();

	std::string msg = "Increased ";

	switch (type) {

	case SKILLS::ACCURACY:
		msg += "Accuracy\n";
		break;

	case SKILLS::DEFENCE:
		msg += "Defence\n";
		break;

	/*case SKILLS::LUCK :
		msg += "Luck\n";
		break;*/

	case SKILLS::STEALTH:
		msg += "Stealth\n";
		break;

	case SKILLS::MELEE:
		msg += "Melee Damage\n";
		break;

	case SKILLS::RANGED:
		msg += "Ranged Damage\n";
		break;

	case SKILLS::MAGIC:
		msg += "Magic\n";
		break;

	case SKILLS::LOCKPICKING:
		msg += "Lockpicking\n";
		break;

	case SKILLS::PERCEPTION:
		msg += "Perception\n";
		break;

	case SKILLS::PERSUASION:
		msg += "Persuasion\n";
		break;

	default:
		msg = "Error retrieving skills";
		break;
	}

	//std::to_string(mSkills[skill].getLevel())
	return msg += std::to_string(mSkills[skill].getLevel());
}

void SkillComponent::assignRandomSkills(int level){


	/*
	
	lvl 1 = 5
	lvl 2 = 0
	lvl 3 = 10
	lvl 4 = 0
	lvl 5 = 15

	*/

	int skillPoint = level * 5;

	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> skillDistribution(0, 9);


	for (int i = 0; i < skillPoint; i++) {

		int diceRoll = skillDistribution(generator);


		switch (diceRoll) {

		case SKILLS::ACCURACY:
			this->increaseSkill(SKILLS::ACCURACY);
			break;

		case SKILLS::DEFENCE:
			this->increaseSkill(SKILLS::DEFENCE);
			break;

		case SKILLS::LOCKPICKING:
			this->increaseSkill(SKILLS::LOCKPICKING);
			break;

	/*	case SKILLS::LUCK:
			this->increaseSkill(SKILLS::LUCK);
			break;*/

		case SKILLS::MAGIC:
			this->increaseSkill(SKILLS::MAGIC);
			break;

		case SKILLS::MELEE:
			this->increaseSkill(SKILLS::MELEE);
			break;

		case SKILLS::PERCEPTION:
			this->increaseSkill(SKILLS::PERCEPTION);
			break;

		case SKILLS::PERSUASION:
			this->increaseSkill(SKILLS::PERSUASION);
			break;

		case SKILLS::RANGED:
			this->increaseSkill(SKILLS::RANGED);
			break;

		case SKILLS::STEALTH:
			this->increaseSkill(SKILLS::STEALTH);
			break;

		default:
			break;
		}

	}

	////debug
	//mSkills[SKILLS::MELEE].setLevel(1);
	//mSkills[SKILLS::DEFENCE].setLevel(1);
}

void SkillComponent::calculateSkills(AttributeComponent& ac) {


	/*
		LUCK HAS AN AFFECT ON ALL ABILITIES, SLIGHTLY
	*/

	int luckLevel = ac.getAttribute(LUCK);
	int level = ac.getLevel();

	/*
		AGILITY
	*/
	int agilityLevel = ac.getAttribute(AGILITY);

	int rangeLvl = ((agilityLevel * 5 + agilityLevel / 4) + (luckLevel));
	mSkills[SKILLS::RANGED].setLevel(rangeLvl + level);
	int accuLvl = (agilityLevel * 5 + agilityLevel / 4) + (luckLevel);
	mSkills[SKILLS::ACCURACY].setLevel(accuLvl + level);


	/*
		CHARISMA
	*/
	
	int charismaLevel = ac.getAttribute(ATTRIBUTE::CHARISMA);
	int persuLvl = (charismaLevel * 5 + charismaLevel / 4) + luckLevel;
	mSkills[SKILLS::PERSUASION].setLevel(persuLvl + level);


	/*
		VITALITY
	*/
	
	int vitLevel = ac.getAttribute(ATTRIBUTE::VITALITY);
	int defenceLvl = (vitLevel * 5 + vitLevel / 4) + luckLevel;
	mSkills[SKILLS::DEFENCE].setLevel(defenceLvl + level);


	/*
		DEXTERITY
	*/
	
	int dexLevel = ac.getAttribute(ATTRIBUTE::DEXTERITY);

	int LockLvl = (dexLevel * 5 + dexLevel / 4) + luckLevel;
	int stealthLvl = (dexLevel * 5 + dexLevel / 4) + luckLevel;
	mSkills[SKILLS::STEALTH].setLevel(stealthLvl + level);
	mSkills[SKILLS::LOCKPICKING].setLevel(LockLvl + level);


	/*
		INTELLIGENCE
	*/
	
	int intLevel = ac.getAttribute(ATTRIBUTE::INTELLIGENCE);

	int magLvl = (intLevel * 5 + intLevel / 4) + luckLevel;
	int percepLvl = (intLevel * 5 + intLevel / 4) + luckLevel;
	mSkills[SKILLS::MAGIC].setLevel(magLvl + level);
	mSkills[SKILLS::PERCEPTION].setLevel(percepLvl + level);

	/*
		STRENGTH
	*/
	
	int strLevel = ac.getAttribute(ATTRIBUTE::STRENGTH);

	int meleeLvl = (strLevel * 5 + strLevel / 4) + luckLevel;
	mSkills[SKILLS::MELEE].setLevel(meleeLvl + level);


	/*
			NEED TO IMPLEMENT A GOLD DISCOVERY NUMBER AND A CARRY WEIGHT
			WHICH WILL BE AFFECTED BY CHARISMA AND STRENGTH RESPECTIVELY

	*/

	//this->vitality = 0.01f;		//HEALTH + DEFENCE - DONE
	//this->strength = 0.01f;		//MELEE DMG + CARRY WEIGHT????
	//this->dexterity = 0.01f;		//STEALTH + LOCKPICKING		- DONE
	//this->agility = 0.01f;		//RANGED DMG + ACCURACY		- DONE
	//this->intelligence = 0.01f;	//MAGIC + PERCEPTION		- DONE
	//this->charisma = 0.10f;		//PERSUASION + MORE MONEY????
}


