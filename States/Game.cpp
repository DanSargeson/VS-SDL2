#include "Game.h"
#include "Engine.h"
#include "Event.h"
#include "Battle.h"
#include "CharacterMenu.h"
#include "LoadGame.h"

Game::Game() : State(){

    tutorialCount = 0;
    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
    StateData::GetInstance()->enemyText = std::make_shared<GUI::Text>();
    StateData::GetInstance()->dynamicText = std::make_shared<GUI::Text>();

    StateData::GetInstance()->mainText->setString("Select an option: ");
    //StateData::GetInstance()->mainText->setPosition(GUI::p2pX(20), GUI::p2pY(20));

    StateData::GetInstance()->enemyText->setString("");
    StateData::GetInstance()->enemyText->setPosition(GUI::p2pX(20), GUI::p2pY(50));

    StateData::GetInstance()->dynamicText->setString("");
    StateData::GetInstance()->dynamicText->setPosition(GUI::p2pX(20), GUI::p2pY(40));

	std::vector<std::string> menuOptions;

    gameMenu.reset();
	gameMenu = make_unique<GUI::Menu>();

	textBox = std::make_shared<GUI::textBox>();

	//menuOptions.push_back("0: Quit");
	menuOptions.push_back("Travel");    //1
	menuOptions.push_back("Shop");      //2
	menuOptions.push_back("Level Up");  //3
	menuOptions.push_back("Rest - Cost 10 Gold");   //4
	menuOptions.push_back("Character Menu");        //5
	menuOptions.push_back("Create Character");
	menuOptions.push_back("Save Game");             //7
	menuOptions.push_back("Load Character");        //8
	menuOptions.push_back("Help");                  //9

	gameMenu->setMenuOptions(menuOptions, true);
}

Game::~Game(){

}

void Game::update(const float& dt){

    if(StateData::GetInstance()->getTutorial() == true){

        switch(tutorialCount){

        case 0:
            textBox->setSize(400, 400);
            textBox->setActive(true);
            textBox->setHeader("Welcome to the tutorial!");
            textBox->setText("Here I will explain some of the screens.\n\nPress ENTER to continue...");
            textBox->setPosition(20, 20);
            break;

        case 1:
            textBox->setSize(400, 400);
            textBox->setActive(true);
            textBox->setPosition(40, 10);
            textBox->setHeader("Main Menu");
            textBox->setText("Here is your main menu, scroll using the UP and DOWN arrow buttons\n\nPress ENTER to continue...");
            break;

        default:
            break;
        }
    }

    if(textBox->getActive()){

        gameMenu->setActive(false);
    }
    else{

        gameMenu->setActive(true);
    }
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

            if(gameMenu->getChoice() == 0){

                Engine::GetInstance()->PopState();

                return;
            }
            if(gameMenu->getChoice() == 1){

                StateData::GetInstance()->mainText->setString("You travel into parts unknown...");
                SDL_Delay(200);
                StateData::GetInstance()->getActiveCharacter()->travel();
               // Event e;

               // e.createEvent();
                //StateData::GetInstance()->push_state(std::make_shared<Battle>());
                Engine::GetInstance()->AddState(std::make_shared<Battle>());
            }

            if(gameMenu->getChoice() == 3){

                StateData::GetInstance()->getActiveCharacter()->levelUp();
               // StateData::GetInstance()->mainText->setString("Levelled up!!");
            }

            if(gameMenu->getChoice() == 4){

//                if(StateData::GetInstance()->getActiveCharacter()->getGold() >= 10){
//
//                    StateData::GetInstance()->getActiveCharacter()->resetHP();
//                    StateData::GetInstance()->getActiveCharacter()->setGold(-10);
//
//                    StateData::GetInstance()->mainText->setString("You awake feeling well rested");
//                    StateData::GetInstance()->enemyText->setColour(255, 0, 0, 0);
//                    StateData::GetInstance()->enemyText->setString("Lost 10 gold");
//                }
//                else{
//
//                    StateData::GetInstance()->enemyText->setColour(255, 0, 0, 0);
//                    StateData::GetInstance()->enemyText->setString("You don't have enough gold.");
//                }
                    StateData::GetInstance()->mainText->setString("You awake feeling well rested!");
                    StateData::GetInstance()->getActiveCharacter()->resetHP();
            }

            if(gameMenu->getChoice() == 5){

                Engine::GetInstance()->AddState(std::make_shared<CharacterMenu>());
            }


            if(gameMenu->getChoice() == 7){

                saveCharacters();
                StateData::GetInstance()->mainText->setString("Game Saved");
            }

            if(gameMenu->getChoice() == 8){

                Engine::GetInstance()->PopState();
                Engine::GetInstance()->AddState(std::make_shared<LoadGame>());

                return;
            }

            if(gameMenu->getChoice() == 9){

//                textBox->setActive(true);
//                std::string txt = "Text 1. \nText 2.";
//                textBox->setSize(200, 200);
//                textBox->setHeader("Header");
//                textBox->setText(txt);
//                textBox->setPosition(15, 15);
                tutorialCount = 0;
                StateData::GetInstance()->setTutorial(true);
            }
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){

        std::string msg = "Corruption: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getCorruption());
        StateData::GetInstance()->enemyText->setString(msg);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(!StateData::GetInstance()->mainText->isEmpty()){

            StateData::GetInstance()->mainText->clearText();
            StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
            StateData::GetInstance()->mainText->setString("Select an option: ");
        }

        if(!StateData::GetInstance()->dynamicText->isEmpty()){

            StateData::GetInstance()->dynamicText->clearText();
        }

        if(!StateData::GetInstance()->enemyText->isEmpty()){

            StateData::GetInstance()->enemyText->clearText();
        }

        if(textBox->getActive()){

            textBox->setActive(false);

            if(StateData::GetInstance()->getTutorial() == true){

                if(tutorialCount < 1){

                    tutorialCount++;

                    return;
                }
                StateData::GetInstance()->setTutorial(false);
            }
        }
    }
}

void Game::render(){

    SDL_RenderClear(Engine::GetInstance()->GetRenderer());

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    gameMenu->render();
    StateData::GetInstance()->mainText->render();
    StateData::GetInstance()->dynamicText->render();
    StateData::GetInstance()->enemyText->render();

       if(textBox->getActive()){

       if(StateData::GetInstance()->getTutorial() == true){
        int w, h;
        SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, &h);
        SDL_Rect overlay = { 0, 0, w, h };
        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 211, 211, 211, 100);
        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &overlay);
        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);

        if(tutorialCount == 1){

            gameMenu->render();
            textBox->render();
        }
       } //END TUTORIAL
        textBox->render();
    }
}
