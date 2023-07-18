//#include "stdafx.h"
#include "MainMenu.h"

//#include "GameState.h"
#include "CharacterCreator.h"
#include "LoadGame.h"
///#include "Editor.h"
//#include "Texture.h"
#include "Engine.h"
#include <filesystem>

MainMenu::MainMenu() : State(){


    mBgTexture = std::make_unique<Texture>();


    if (!mBgTexture->loadFromFile("Assets/titleScreenDark2.png", Engine::GetInstance()->GetRenderer())) {

		printf("Unable to load BG Texture. MainMenuState.cpp line 12");
	}

	initButtons();
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

void MainMenu::updateEvents(SDL_Event & e){


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

        Engine::GetInstance()->AddState(std::make_shared<LoadGame>());
        ///Engine::GetInstance()->AddState(std::make_shared<LoadCharacter>());
		return;
	}

	if (mButtons["EDITOR_STATE"]->isPressed(e.button)) {


        ///Engine::GetInstance()->AddState(std::make_shared<Editor>());
        std::cout << "EDITOR" << std::endl;

		SDL_Delay(400);

		return;
	}
}

//void MainMenu::updateGUI(){
//
//	initButtons();
//}

void MainMenu::render(){



//        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 25);
//        SDL_RenderClear(Engine::GetInstance()->GetRenderer());


        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), mBgTexture->getTexture(), NULL, NULL);




    //SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), , NULL. NULL);
//	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), mBgTexture->getTexture(), NULL, NULL);
//
	for (auto i : mButtons) {

		i.second->renderButtons(Engine::GetInstance()->GetRenderer());
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

	auto wind = Engine::GetInstance()->GetWindow();
	unsigned int charSize = GUI::calcCharSize(80);


	///TODO: All need smart pointers...


	mButtons["LOAD_GAME"] = new GUI::Button(GUI::p2pX(75.5f), GUI::p2pY(19.5f),
		GUI::p2pX(20.8f), GUI::p2pY(8.3f), charSize);
	mButtons["LOAD_GAME"]->setRenderText("Continue Game");

	if (!std::filesystem::exists("Data/Characters.DATA")) {

		mButtons["LOAD_GAME"]->setActive(false);
	}
	else {

		mButtons["LOAD_GAME"]->setActive(true);
	}

	mButtons["GAME_STATE"] = new GUI::Button(GUI::p2pX(75.5f), GUI::p2pY(32.5f),
		GUI::p2pX(20.8f), GUI::p2pY(8.3f), charSize);
	mButtons["GAME_STATE"]->setRenderText("New Game");

	mButtons["LOAD_CHAR"] = new GUI::Button(GUI::p2pX(75.f), GUI::p2pY(45.5f), GUI::p2pX(20.8f), GUI::p2pY(8.3f), charSize);
	mButtons["LOAD_CHAR"]->setRenderText("Load Game");

	mButtons["EDITOR_STATE"] = new GUI::Button(GUI::p2pX(75.5f), GUI::p2pY(58.5f),
		GUI::p2pX(20.8f), GUI::p2pY(8.3f), charSize);
	mButtons["EDITOR_STATE"]->setRenderText("Editor");
}
