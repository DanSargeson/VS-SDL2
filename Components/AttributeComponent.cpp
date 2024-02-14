#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(Entity* owner, unsigned level, bool reset, bool enemy) : Component(owner){

    baseEXP = 50.f;
	mLevel = level;
	mExp = 0;
	//mExpNext = static_cast<float>((50 / 3) * (pow(mLevel + 1, 3) - 6 * pow(mLevel + 1, 2) + ((mLevel + 1) * 17) - 12));
	mExpNext = (baseEXP * mLevel) * 5;
	mAttributePoints = 0;
	mHasLevelled = false;

	for (int i = 0; i < TOTAL_ATTRIBUTES; i++) {

		mAttributes.push_back(1);
	}

	if (enemy) {

        baseEXP = 5.f;
        mExpNext = (baseEXP * mLevel) * 5;
		unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
		std::default_random_engine generator(seed);
//		std::uniform_int_distribution<int> levelDistribution(low, high);
		std::uniform_int_distribution<int> pointDistribution(0, 6);
//
//		mLevel = levelDistribution(generator);

		int point = 0;
		int counter = 0;
		if(mLevel > 1){
            point += mLevel;
		}

		for (int i = 0; i < point; i++) {

			int roll = pointDistribution(generator);

			switch (roll) {

			case 0:
				mAttributes[ATTRIBUTE::VITALITY] += 1;
				break;

			case 1:
				mAttributes[ATTRIBUTE::STRENGTH] += 1;
				break;

			case 2:
				mAttributes[ATTRIBUTE::DEXTERITY] += 1;
				break;

			case 3:
				mAttributes[ATTRIBUTE::AGILITY] += 1;
				break;

			case 4:
				mAttributes[ATTRIBUTE::INTELLIGENCE] += 1;
				break;

			case 5:
				mAttributes[ATTRIBUTE::CHARISMA] += 1;
				break;

			case 6:
				mAttributes[ATTRIBUTE::LUCK] += 1;
				break;

			default:
				break;
			}
		}

		std::cout << "Enemy level: " << mLevel << "\n";
		std::cout << "Enemy points: " << point << "\n";
		std::cout << "Enemy vit: " << mAttributes[ATTRIBUTE::VITALITY] << "\n";
		std::cout << "Enemy str: " << mAttributes[ATTRIBUTE::STRENGTH] << "\n";
		std::cout << "Enemy dex: " << mAttributes[ATTRIBUTE::DEXTERITY] << "\n";
		std::cout << "Enemy agi: " << mAttributes[ATTRIBUTE::AGILITY] << "\n";
		std::cout << "Enemy cha: " << mAttributes[ATTRIBUTE::CHARISMA] << "\n";
		std::cout << "Enemy int: " << mAttributes[ATTRIBUTE::INTELLIGENCE] << "\n";
		std::cout << "Enemy luck: " << mAttributes[ATTRIBUTE::LUCK] << "\n";
		std::cout << "EXP NEXT: " << std::to_string(mExpNext) << "\n\n";
	}

	//updateLevel();
	updateStats(reset);
}

AttributeComponent::~AttributeComponent(){

    mExp = 0;
}

void AttributeComponent::increaseAttribute(int attr){

	switch (attr) {

	case ATTRIBUTE::AGILITY:
		mAttributes[AGILITY] += 1;
		break;

	case ATTRIBUTE::CHARISMA:
		mAttributes[CHARISMA] += 1;
		break;

	case ATTRIBUTE::DEXTERITY:
		mAttributes[DEXTERITY] += 1;
		break;

	case ATTRIBUTE::INTELLIGENCE:
		mAttributes[INTELLIGENCE] += 1;
		break;

	case ATTRIBUTE::LUCK:
		mAttributes[LUCK] += 1;
		break;

	case ATTRIBUTE::STRENGTH:
		mAttributes[STRENGTH] += 1;
		break;

	case ATTRIBUTE::VITALITY:
		mAttributes[VITALITY] += 1;
		break;

	default:
		break;
	}

	for (int i = 0; i < TOTAL_ATTRIBUTES; i++) {

		if (mAttributes[i] >= 10) {

			mAttributes[i] = 10;
		}
	}
}

void AttributeComponent::decreaseAttribute(int attr){


	switch (attr) {

	case ATTRIBUTE::AGILITY:
		mAttributes[AGILITY] -= 1;
		break;

	case ATTRIBUTE::CHARISMA:
		mAttributes[CHARISMA] -= 1;
		break;

	case ATTRIBUTE::DEXTERITY:
		mAttributes[DEXTERITY] -= 1;
		break;

	case ATTRIBUTE::INTELLIGENCE:
		mAttributes[INTELLIGENCE] -= 1;
		break;

	case ATTRIBUTE::LUCK:
		mAttributes[LUCK] -= 1;
		break;

	case ATTRIBUTE::STRENGTH:
		mAttributes[STRENGTH] -= 1;
		break;

	case ATTRIBUTE::VITALITY:
		mAttributes[VITALITY] -= 1;
		break;

	default:
		break;
	}

	for (int i = 0; i < TOTAL_ATTRIBUTES; i++) {

		if (mAttributes[i] <= 0) {

			mAttributes[i] = 0;
		}
	}
}

void AttributeComponent::loadAttribute(int level, float xp, int hp, int vit, int str, int dex, int agi, int intel, int charis, int luck){

	mLevel = level;
	mExp = xp;
	mAttributes[ATTRIBUTE::VITALITY] = vit;
	mAttributes[STRENGTH] = str;
	mAttributes[DEXTERITY] = dex;
	mAttributes[AGILITY] = agi;
	mAttributes[INTELLIGENCE] = intel;
	mAttributes[CHARISMA] = charis;
	mAttributes[LUCK] = luck;

	updateLevel();
	updateStats(true);

	//mHp = hp;
}

void AttributeComponent::setAttributes(int vit, int str, int dex, int agi, int intel, int charis, int luck){

mAttributes[ATTRIBUTE::VITALITY] = vit;
	mAttributes[STRENGTH] = str;
	mAttributes[DEXTERITY] = dex;
	mAttributes[AGILITY] = agi;
	mAttributes[INTELLIGENCE] = intel;
	mAttributes[CHARISMA] = charis;
	mAttributes[LUCK] = luck;


    mHpMax = ((mAttributes[VITALITY] * 4) + mLevel  * 10);
}

int AttributeComponent::getHP(){

	return mHp;
}

int AttributeComponent::getHPMax(){

	return mHpMax;
}

float AttributeComponent::getEXP(){

	return mExp;
}

float AttributeComponent::getEXPNext(){

	return mExpNext;
}

unsigned AttributeComponent::getLevel(){

	return mLevel;
}

void AttributeComponent::gainEXP(const float exp){

	mExp += exp;
}

void AttributeComponent::loseEXP(const float exp){

	mExp -= exp;
	if (mExp < 0) {

		mExp = 0;
	}
}


void AttributeComponent::gainHP(const int hp){

	mHp += hp;

	if (mHp > mHpMax) {

		mHp = mHpMax;
	}
}

void AttributeComponent::loseHP(const int hp){

	mHp -= hp;

	if (mHp < 0) {

		mHp = 0;
	}
}

void AttributeComponent::calculateNextEXP()
{
}

void AttributeComponent::updateStats(const bool reset){

	mHpMax = ((mAttributes[VITALITY] * 4) + mLevel  * 10);

	if (reset) {

		mHp = mHpMax;
	}
}

void AttributeComponent::updateLevel(){

	if (mLevel == 0) {

		mLevel = 1;
	}

	mExpNext = (baseEXP * mLevel) * 5;

	while (mExp >= mExpNext && mExpNext != 0) {

		++mLevel;
		mExp -= mExpNext;

		//mExpNext = static_cast<float>((50 / 3) * (pow(mLevel + 1, 3) - 6 * pow(mLevel + 1, 2) + ((mLevel + 1) * 17) - 12));
		mExpNext = (baseEXP * mLevel) * 5;
		updateStats(true);

		mHasLevelled = true;
	}

	//if (mLevel % 5 == 0) { //TODO - Every 10 levels player gains an attribute point. Might change this.

		mAttributePoints++;
	//}

//	for(int i = 0; i < ATTRIBUTE::TOTAL_ATTRIBUTES; i++){
//
//        mAttributes[i]++;
//	}
}

void AttributeComponent::setAttributePoints(int p){

    mAttributePoints = p;
}

void AttributeComponent::update(){

	updateLevel();
}

void AttributeComponent::assignRandomAttributes(int level){

	//TODO
}

std::string AttributeComponent::debugPrint(){

	std::stringstream ss;

	ss << "Level: " << mLevel << "\n"
		<< "EXP: " << mExp << "\n"
		<< "EXP Required: " << mExpNext << "\n"
		<< "Points to spend: " << mAttributePoints << "\n";

	return  ss.str();
}

int AttributeComponent::getAttribute(const int attr){

	try {

		if (attr < 0 || attr >= ATTRIBUTE::TOTAL_ATTRIBUTES) {

			throw(std::runtime_error("Error: AttributeComponent::getAttribute() - Attribute not found: " + attr));
		}
		else {

			return static_cast<int>(mAttributes[attr]);
		}
	}
	catch (std::exception e) {

		std::ofstream outFile;

		outFile.open("ErrorLog.txt");

		if (outFile.is_open()) {

			outFile << e.what() << std::endl;

			outFile.close();
		}
	}

	return -1;
}
