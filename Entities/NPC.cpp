//#include "stdafx.h"
#include "NPC.h"
#include "FactionComponent.h"
#include "DialogueComponent.h"

int NPC::characterID = 0;

void NPC::generateID(){

	this->characterID++;
}

std::string NPC::getFactionStr(){

    std::string fact = factionComponent->getFactionName(faction);

    return fact;
}

NPC::NPC(int faction){

	this->type = NPC_TYPE::PEASANT;

	this->faction = faction;
	this->questGiver = false;
	this->companion = false;
	this->dialogue = " ";
	this->seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	this->generator.seed(seed);

	std::uniform_int_distribution<int> goldDistribution(1, 500);
	int randomGold = goldDistribution(generator);

	this->gold = randomGold;

	this->createDialogueComponent();


	std::uniform_int_distribution<int> textDistribution(1, 5);
	int randomText = textDistribution(generator);
	std::string v = "99" + std::to_string(randomText);
//	int total = std::stoi(v);
//	dialogueComponent->setDialogueOptions("Resources/Text/randomNews.txt", total);

	textFileName = "Resources/Text/randomNews.txt";
	this->createFactionComponent();

	this->createInventory();

	this->generateID();

//	initBackground(Engine::GetInstance()->GetRenderer());
}

NPC::NPC(int faction, std::string fileName, int id) {

	//this->type = NPC_TYPE::PEASANT;
	this->characterID = id;
	this->faction = faction;
	this->createDialogueComponent();
	this->createFactionComponent();
	this->questGiver = true;
	textFileName = fileName;
	//this->dialogueComponent->setDialogueOptions(fileName, this->characterID);
	//this->dialogueComponent->playerChoice(1);

	//this->dialogue = this->dialogueComponent->getDialogue();	//TODO:: CHANGE TO GETDIALOGUE OPTIONS

//	initBackground(rend);

	this->createInventory();
}

NPC::NPC(int faction, bool questGiver, std::string fileName){

	//this->factionComponent->changeRep()
	this->type = NPC_TYPE::PEASANT;
	this->faction = faction;
	this->questGiver = questGiver;
	this->dialogue = dialogue;
	this->createFactionComponent();
	this->createDialogueComponent();

	textFileName = fileName;
	this->factionComponent->calculateReputation(this->faction);

	std::uniform_int_distribution<int> goldDistribution(1, 500);

	int randomGold = goldDistribution(generator);

	this->gold = randomGold;

	this->createInventory();

//	initBackground(rend);
}

NPC::~NPC(){


}

//std::vector<std::string> NPC::getDialogueOptions() {
//
//	if (type == INNKEEPER) {
//
//		return dialogueComponent->getDialogueOptions(true);
//	}
//	else {
//
//		return Entity::getDialogueOptions();
//	}
//}

void NPC::initBackground(SDL_Renderer* rend) {

//	bg = std::make_unique<Texture>();
	std::string fileName = "Resources/Images/temp/";
	switch (faction) {

	case FACTIONS::BLACK:
		fileName = " ";
		break;

	case FACTIONS::RED:
		fileName += "Red.png";
		break;

	case FACTIONS::AQUA:
		fileName += "Aqua.png";
		break;

	case FACTIONS::BLUE:
		fileName += "Blue.png";
		break;

	case FACTIONS::BROWN:
		fileName += "Brown.png";
		break;

	case FACTIONS::GREEN:
		fileName += "Green.png";
		break;

	case FACTIONS::PURPLE:
		fileName += "Purple.png";
		break;

	case FACTIONS::WHITE:
		fileName += "White.png";
		break;

	default:
		fileName = " ";
		break;
	}

//	if (faction != FACTIONS::BLACK) {
//
//		bg->loadFromFile(fileName, rend);
//	}
}

int NPC::getFaction(){

	return this->faction;
}

bool NPC::givesQuest(){


	return this->questGiver;
}

int NPC::getType(){

	return type;
}

void NPC::setType(int t){

	type = t;
}

std::string NPC::getName(){


	return this->name;
}

void NPC::setName(std::string name){

	this->name = name;
}

void NPC::setTextureRect(SDL_Rect r){

//	bg->setTextureRect(r.x, r.y, r.w, r.h);
}

int NPC::getInvCount(){


	return this->inv.smrtSize();
}

//std::string NPC::getItemString(int index){
//
//
//	std::shared_ptr<Item> item = this->inv.findItemSmart(index);
//
//	return item->getTypeStr();
//}

void NPC::setDialogue(int id) {

	//DEBUG
	if (type == INNKEEPER) {

		textFileName = "Resources/Text/innkeeper.txt";
	}

//	dialogueComponent->NEWDIAG(textFileName, id);

	//std::uniform_int_distribution<int> textDistribution(1, 5);
	//int randomText = textDistribution(generator);

	//if (type == NPC_TYPE::PEASANT) {

	//	std::string v = "99" + std::to_string(randomText);
	//	int total = std::stoi(v);
	//	dialogueComponent->setDialogueOptions("Resources/Text/randomNews.txt", id);
	//}

	//if (type == NPC_TYPE::INNKEEPER) {

	//	int total = 666;
	//	dialogueComponent->NEWDIAG("Resources/Text/innkeeper.txt", id);
	//	//dialogueComponent->setDialogueOptions("Resources/Text/innkeeper.txt", id);
	//}
}

bool NPC::quitDialogue() {

//	return dialogueComponent->quitDialogue();
}

void NPC::setCharm(bool x) {

//	dialogueComponent->setCharm(x);
}

bool NPC::charm() {

//	return dialogueComponent->charm();
}

bool NPC::shop() {

//	return dialogueComponent->shop();
}

void NPC::talk(int choice) {

	if (type == INNKEEPER) {

//		dialogueComponent->talk(choice, true);
	}
	else {

//		dialogueComponent->talk(choice);
	}

}

//std::string NPC::getDialogue(){
//
//	if (this->dialogueComponent) {
//
//
//	//	return dialogueComponent->getDialogue();
//		//return this->dialogueComponent->getDialogue();
//	}
//
//	return "";
//}

int NPC::getDialogueID(){

//	int id = dialogueComponent->getID();
	return 0;
}

void NPC::createInventory(){

	this->seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	this->generator.seed(seed);

	std::uniform_int_distribution<int> invDistribution(1, 100);
	std::uniform_int_distribution<int> itemDistribution(1, 5);

	int items = itemDistribution(generator);

	//std::vector<std::shared_ptr<Item&>> itemVec;
	for (int i = 0; i < items; i++) {
		int random = invDistribution(generator);

		int lvl = 1;			//MAGIC NUMBER
		if (random > 50) {

			Weapon tempW(lvl, 1);

			auto tempWe = make_shared<Weapon>(tempW);
			this->inv.addItemVectorSmart(tempWe);
			//itemVec.push_back(tempW);
		}
		else {

			Armour tempA(lvl, 1);

			auto tempAe = make_shared<Armour>(tempA);
			this->inv.addItemVectorSmart(tempAe);
		}
	}
}

//int NPC::getCurrentMapID(){
//
//	return this->mapID;
//}

void NPC::setDialogueChoice(int choice){

//	this->dialogueComponent->playerChoice(choice);
}

std::shared_ptr<Item> NPC::getItem(int index){

	return inv.findItemSmart(index);
}

void NPC::removeItem(int index){


	this->inv.removeItemVectorSmart(this->inv.findItemSmart(index));
}

int NPC::getGold(){

	return this->gold;
}

std::string NPC::getInvAsString(){

	return inv.getInvAsString();
}

void NPC::update(){


}

void NPC::render(){

//	bg->render(rend, bg->getTextureRect().x, bg->getTextureRect().y);
}
