//#include "stdafx.h"
#include "MainMenu.h"

//#include "GameState.h"
#include "CharacterCreator.h"
#include "LoadGame.h"
///#include "Editor.h"
//#include "Texture.h"
#include "Engine.h"
#include <filesystem>
#include <SDL2/SDL_mixer.h>

MainMenu::MainMenu() : State(){


    mBgTexture = std::make_unique<Texture>();


    if (!mBgTexture->loadFromFile("Assets/titleScreenDark2.png", Engine::GetInstance()->GetRenderer())) {

		printf("Unable to load BG Texture. MainMenuState.cpp line 12");
	}

	//music = std::make_unique<Mix_Music>("");
	music = Mix_LoadMUS("Assets/Audio/Bell.wav");

	if(music == NULL){

        printf("Unable to load main menu music..");
	}


	loadFiles();
	initButtons();

	//If there is no music playing
                    if( Mix_PlayingMusic() == 0 )
                    {
                        Mix_VolumeMusic(70);
                        //Play the music
                        if( Mix_PlayMusic( music, -1) == -1 )
                        {
                            printf("ERROR PLAYING MUSIC mainMenu.cpp line 69.");
                        }
                    }
}

MainMenu::~MainMenu(){

//    auto it = this->mButtons.begin();
//	for (it = this->mButtons.begin(); it != this->mButtons.end(); ++it) {
//
//		delete it->second;
//	}

//	mBgTexture->free();
//	mBgTexture->~Texture();
//	delete mBgTexture;

Mix_FreeMusic(music);
}

//void MainMenu::setStateData()
//{
//}

//void MainMenu::updateInput(const float & dt){
//
//	//mStateData->activeCharacter = 0;
//}

void MainMenu::update(const float & dt){

//	if (!std::filesystem::exists("Data/Characters.DATA")) {
//
//		mButtons["LOAD_GAME"]->setActive(false);
//	}
//	else {
//
//		mButtons["LOAD_GAME"]->setActive(true);
//	}
//	updateKeyTime(dt);
//	updateInput(dt);

	for (auto button : mButtons) {

		button.second->update();
	}
}

//void MainMenu::updateKeyTime(const float &dt, float maxTime){
//}

//void MainMenu::updateEvents(SDL_Event & e){
//}

void MainMenu::loadFiles(){

    std::string fileName = "characters.txt";
    ifstream inFile(fileName);
    StateData::GetInstance()->characters.clear();


    string name = "";
    int disTravel = 0;
    int gold = 0;
    int level = 0;
    int exp = 0;
    int str = 0;
    int vit = 0;
    int dex = 0;
    int intel = 0;
    int hp = 0;
    int stamina = 0;
    int statPoints = 0;
    int skillPoints = 0;
    int corrupt = 0;

	//ITEMS
	Inventory tempItems;

	int itemType = -1;
	int defence = 0;
	int type = 0;
	int damageMin = 0;
	int damageMax = 0;
	string itemName = "";
	int itemLevel = 0;
	int buyValue = 0;
	int sellValue = 0;
	int rarity = 0;

    string line = "";
    stringstream strs;


    if(inFile.is_open()){
		while (getline(inFile, line)) {
			strs.str(line);
			strs >> name;
			strs >> disTravel;
			strs >> gold;
			strs >> level;
			strs >> exp;
			strs >> str;
			strs >> vit;
			strs >> dex;
			strs >> intel;
			strs >> hp;
			strs >> stamina;
			strs >> statPoints;
			strs >> skillPoints;
			strs >> corrupt;

			auto temp = std::make_shared<Player> (name, disTravel, gold, level, exp,
				str, vit, dex, intel, hp,
				stamina, statPoints, skillPoints, corrupt, false);

			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> damageMin
				>> damageMax
				>> type) {

				if (itemType == itemTypes::WEAPON) {
					Weapon activeWeapon(type, damageMin, damageMax, itemName, itemLevel, 0, 0, rarity);
					auto awv = make_shared<Weapon>(activeWeapon);
					temp->setWeapon(awv);
				}
			}
			//ACTIVE ITEMS
			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defence
				>> type) {
				if (itemType == itemTypes::ARMOUR) {
					Armour activeArm(type, defence, itemName, itemLevel, 0, 0, rarity);
					auto avv = make_shared<Armour>(activeArm);
					int type = avv->getType();

					switch (type) {
					case HEAD:
						temp->setArmourHead(avv);
						break;

					case CHEST:
						temp->setArmourChest(avv);
						break;

					case ARMS:
						temp->setArmourArms(avv);
						break;

					case LEGS:
						temp->setArmourLegs(avv);
						break;

					default:
						break;
					}
				}

			}

			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (

				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> damageMin
				>> damageMax
				>> type
				) {

				Weapon tempWeapon(type, damageMin, damageMax, itemName, itemLevel, 0, 0, rarity);
				auto wv = make_shared<Weapon>(tempWeapon);
				tempItems.addItemVectorSmart(wv);
				temp->addItem(wv);
			}


			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (
				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defence
				>> type
				) {
				Armour tempArmour(type, defence, itemName, itemLevel, 0, 0, rarity);
				auto av = make_shared<Armour>(tempArmour);
				tempItems.addItemVectorSmart(av);
				temp->addItem(av);
			}


                StateData::GetInstance()->characters.push_back(temp);

				cout << "Character: " << temp->getName() << " loaded" << "\n";
				temp->setInv(tempItems);
				//cout << "Loaded Inv: " << temp.getInvAsString() << "\n";
				//cout << "tempItems: " << tempItems.getInvAsString() << "\n";
				strs.clear();
               /* for(int i = 0; i < characters.size(); i++){
                    cout << this->characters[i].getStatsAsString() << endl;
					cout << "Loaded Character: " << this->characters[i].getName() << endl;
                }*/

            }
    }

    inFile.close();
}

void MainMenu::updateEvents(SDL_Event & e){


if( Mix_PlayingMusic() == 0 )
                    {
                        Mix_VolumeMusic(70);
                        music = Mix_LoadMUS("Assets/Audio/Bell.wav");

                        //Play the music
                        if( Mix_PlayMusic( music, -1) == -1 )
                        {
                            printf("ERROR PLAYING MUSIC mainMenu.cpp line 69.");
                        }
                    }
	if (mButtons["LOAD_GAME"]->isPressed(e.button)) {

            std::cout << "LOAD GAME" << std::endl;
	}

	if (mButtons["GAME_STATE"]->isPressed(e.button)) {

		std::cout << "NEW GAME" << std::endl;

        Engine::GetInstance()->AddState(std::make_shared<CharacterCreator>());
		return;
	}

	if (mButtons["LOAD_CHAR"]->isPressed(e.button)) {


	std::cout << "LOAD" << std::endl;

        if(std::filesystem::exists("characters.txt")){
            Engine::GetInstance()->AddState(std::make_shared<LoadGame>());

        }

        ///Engine::GetInstance()->AddState(std::make_shared<LoadCharacter>());
		return;
	}

	if (mButtons["EDITOR_STATE"]->isPressed(e.button)) {


        ///Engine::GetInstance()->AddState(std::make_shared<Editor>());
        std::cout << "EDITOR" << std::endl;

		SDL_Delay(400);

		return;
	}

	if(mButtons["QUIT"]->isPressed(e.button)){

        Engine::GetInstance()->Quit();
	}
}

//void MainMenu::updateGUI(){
//
//	initButtons();
//}

void MainMenu::render(){

//        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 25);
        SDL_RenderClear(Engine::GetInstance()->GetRenderer());



        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), mBgTexture->getTexture(), NULL, NULL);




    //SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), , NULL. NULL);
//	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), mBgTexture->getTexture(), NULL, NULL);
//
	for (auto i : mButtons) {

		i.second->renderButtons();
	}
}

void MainMenu::initKeyBinds()
{
}

void MainMenu::initVariables(){

//	mBgTexture = std::make_unique<Texture>();
}

//void MainMenu::initFonts()
//{
//}

void MainMenu::initSaveData() {

	if (std::filesystem::exists("Data/Characters.DATA")) {

	//TODO:: BRING THESE BACK
		//stateData->saveData->loadAllCharacters(stateData->characters);
		//stateData->activeCharacter = stateData->saveData->getLastChar();
	}
}

void MainMenu::initButtons(){

	unsigned int charSize = GUI::calcCharSize(80);


	///TODO: All need smart pointers...


	mButtons["LOAD_GAME"] = new GUI::Button(GUI::p2pXi(75), GUI::p2pY(19.5f),
		GUI::p2pX(20.8f), GUI::p2pY(8.3f), charSize);
	mButtons["LOAD_GAME"]->setRenderText("Continue Game");

	if (!std::filesystem::exists("characters.DATA")) {

		mButtons["LOAD_GAME"]->setActive(false);
	}
	else {

		mButtons["LOAD_GAME"]->setActive(true);
	}

	mButtons["GAME_STATE"] = new GUI::Button(75, 32.5f, 20.8f, 8.3f, charSize);
	mButtons["GAME_STATE"]->setRenderText("New Game");

	mButtons["LOAD_CHAR"] = new GUI::Button(75, 45.5f, 20.8f, 8.3f, charSize);
	mButtons["LOAD_CHAR"]->setRenderText("Load Game");

	mButtons["EDITOR_STATE"] = new GUI::Button(75, 58.5f, 20.8f, 8.3f, charSize);
	mButtons["EDITOR_STATE"]->setRenderText("Editor");

	mButtons["QUIT"] = new GUI::Button(75, 71.5f, 20.8f, 8.3f, charSize);
	mButtons["QUIT"]->setRenderText("Quit");
}
