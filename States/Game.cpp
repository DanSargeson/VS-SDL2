#include "Game.h"
#include "Engine.h"
#include "Event.h"
#include "Battle.h"
#include "CharacterMenu.h"

Game::Game() : State(){

    //gameMenu = std::make_shared<GUI::Menu>();

//    mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), true);
//    mainText->setPosition(GUI::p2pX(20), GUI::p2pY(20));
//    mainText->setString("Select an option: ");

    //StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow());
    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), 5, 5, 89, 60, true);
    StateData::GetInstance()->enemyText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow());
    StateData::GetInstance()->dynamicText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow());

    StateData::GetInstance()->mainText->setString("Select an option: ");
    //StateData::GetInstance()->mainText->setPosition(GUI::p2pX(20), GUI::p2pY(20));

    StateData::GetInstance()->enemyText->setString("");
    StateData::GetInstance()->enemyText->setPosition(GUI::p2pX(20), GUI::p2pY(50));

    StateData::GetInstance()->dynamicText->setString("");
    StateData::GetInstance()->dynamicText->setPosition(GUI::p2pX(20), GUI::p2pY(40));

	std::vector<std::string> menuOptions;

    gameMenu.reset();
	gameMenu = make_unique<GUI::Menu>(*StateData::GetInstance());

	//menuOptions.push_back("0: Quit");
	menuOptions.push_back("Travel");    //1
	menuOptions.push_back("Shop");      //2
	menuOptions.push_back("Level Up");  //3
	menuOptions.push_back("Rest - Cost 10 Gold");   //4
	menuOptions.push_back("Character Menu");        //5
	menuOptions.push_back("Create Character");
	menuOptions.push_back("Save Game");
	menuOptions.push_back("Load Character");
	menuOptions.push_back("Character Switch");

	gameMenu->setMenuOptions(menuOptions, true);
}

Game::~Game(){

}

void Game::update(const float& dt){

    gameMenu->update();
}

void Game::updateEvents(SDL_Event& e){

    gameMenu->update();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN) && e.key.repeat == 0){

        gameMenu->scrollText(0);
    }

      if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP) && e.key.repeat == 0){

        gameMenu->scrollText(1);
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        //updateMouseEvents(e.button);
        //GAME LOOP HERE
        if(gameMenu->isSelected()){
            if(gameMenu->getChoice() == 1){

                StateData::GetInstance()->mainText->setString("You travel into parts unknown...");
                SDL_Delay(200);
                StateData::GetInstance()->getActiveCharacter()->travel();
               // Event e;

               // e.createEvent();
                //StateData::GetInstance()->push_state(std::make_shared<Battle>());
                Engine::GetInstance()->AddState(std::make_shared<Battle>());
            }

            if(gameMenu->getChoice() == 4){

                StateData::GetInstance()->getActiveCharacter()->resetHP();
                StateData::GetInstance()->getActiveCharacter()->setGold(-10);

                StateData::GetInstance()->mainText->setString("You awake feeling well rested");
                StateData::GetInstance()->enemyText->setColour(255, 0, 0, 0);
                StateData::GetInstance()->enemyText->setString("Lost 10 gold");
            }

            if(gameMenu->getChoice() == 5){

                Engine::GetInstance()->AddState(std::make_shared<CharacterMenu>());
            }
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(!StateData::GetInstance()->mainText->isEmpty()){

            StateData::GetInstance()->mainText->clearText();
            StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), 5, 5, 89, 60, true);
            StateData::GetInstance()->mainText->setString("Select an option: ");
        }

        if(!StateData::GetInstance()->dynamicText->isEmpty()){

            StateData::GetInstance()->dynamicText->clearText();
        }

        if(!StateData::GetInstance()->enemyText->isEmpty()){

            StateData::GetInstance()->enemyText->clearText();
        }
    }
}

void Game::render(){


    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    gameMenu->render();
   // mainText->render();
    StateData::GetInstance()->mainText->render();
    StateData::GetInstance()->dynamicText->render();
    StateData::GetInstance()->enemyText->render();
}
