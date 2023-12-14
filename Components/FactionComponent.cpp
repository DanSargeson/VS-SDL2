#include "stdafx.h"
#include "FactionComponent.h"

FactionComponent::FactionComponent(Entity* owner) : Component(owner){

	mFactions.push_back(Faction(FACTIONS::BLACK));
	mFactions.push_back(Faction(FACTIONS::WHITE));
	mFactions.push_back(Faction(FACTIONS::RED));
	mFactions.push_back(Faction(FACTIONS::BLUE));
	mFactions.push_back(Faction(FACTIONS::GREEN));
	mFactions.push_back(Faction(FACTIONS::BROWN));
	mFactions.push_back(Faction(FACTIONS::AQUA));
	mFactions.push_back(Faction(FACTIONS::PURPLE));
}

FactionComponent::~FactionComponent(){

}

int FactionComponent::getReputation(unsigned int faction){

	try {


		if (faction < 0 || faction >= mFactions.size()) {

			throw std::runtime_error("Error::FACTIONCOMPONENT::GetReputation - faction not found: " + faction);
		}
		else {

			return mFactions[faction].getRepLevel();
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

	return 0;
}


void FactionComponent::calculateReputation(int faction) {


	unsigned seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_int_distribution<int> repDist(REPUTATION::SUSPICIOUS_LOW, REPUTATION::SUSPICIOUS_HIGH);

	int rep = repDist(generator);

	try {


		switch (faction) {

		case FACTIONS::AQUA:
			//this->
			mFactions[FACTIONS::AQUA].setLevel(REPUTATION::REVERED);
			break;

		case FACTIONS::BLACK:

			break;

		case FACTIONS::BLUE:

			break;

		case FACTIONS::BROWN:

			break;

		case FACTIONS::GREEN:

			//GREEN ARE SUSPICIOUS AGAINST BLUE AND RED UNTIL THE PLAYER INTERVENES

			mFactions[FACTIONS::GREEN].setLevel(REPUTATION::REVERED);
			mFactions[FACTIONS::BLUE].setLevel(rep);
			mFactions[FACTIONS::RED].setLevel(rep);

			break;

		case FACTIONS::PURPLE:

			break;

		case FACTIONS::RED:

			break;

		case FACTIONS::WHITE:

			mFactions[FACTIONS::WHITE].setLevel(REPUTATION::REVERED);
			mFactions[FACTIONS::BLACK].setLevel(REPUTATION::HATED_LOW);
			break;

		default:

			throw std::runtime_error("ERROR: FACTION COMPONENT - LINE 82");
			break;
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

void FactionComponent::changeRep(int faction, int value){

	mFactions[faction].setLevel(value);
}

void FactionComponent::loseRep(int faction, int rep){

	mFactions[faction].loseRep(rep);
}

void FactionComponent::gainRep(int faction, int rep) {

	mFactions[faction].gainRep(rep);
}

std::string FactionComponent::getFactionName(int faction) {

	return mFactions[faction].getName();
}

std::string FactionComponent::getFactionsStr() {

	std::string msg;



	for (int i = 0; i < TOTAL_FACTIONS; i++) {

		msg += mFactions[i].getName() + ": ";

		if (mFactions[i].getRepLevel() <= REPUTATION::HATED_HIGH) {

			msg += "HATED\n";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::DISLIKED_HIGH) {

			msg += "DISLIKED\n";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::SUSPICIOUS_HIGH) {

			msg += "SUSPICIOUS\n";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::NEUTRAL_HIGH) {

			msg += "NEUTRAL\n";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::AMIABLE_HIGH) {

			msg += "AMIABLE\n";
		}
		else if (mFactions[i].getRepLevel() <= REPUTATION::LIKED_HIGH) {

			msg += "LIKED\n";
		}
		else if (mFactions[i].getRepLevel() >= REPUTATION::REVERED) {

			msg += "REVERED\n";
		}

	}

	return msg;
}

std::string FactionComponent::getFactionsStrSave() {

	std::string deets = "";

	for (int i = 0; i < FACTIONS::TOTAL_FACTIONS; i++) {

		deets += std::to_string(mFactions[i].getRepLevel()) + " ";
	}

	return deets;
}

void FactionComponent::loadFactions(int black, int white, int red, int blue, int green, int brown, int aqua, int purple){

	mFactions[FACTIONS::BLACK].setLevel(black);
	mFactions[FACTIONS::WHITE].setLevel(white);
	mFactions[FACTIONS::RED].setLevel(red);
	mFactions[FACTIONS::BLUE].setLevel(blue);
	mFactions[FACTIONS::GREEN].setLevel(green);
	mFactions[FACTIONS::BROWN].setLevel(brown);
	mFactions[FACTIONS::AQUA].setLevel(aqua);
	mFactions[FACTIONS::PURPLE].setLevel(purple);
}
