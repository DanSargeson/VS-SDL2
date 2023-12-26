#include "Game.h"
#include "Engine.h"
#include "Event.h"
#include "Settings.h"
#include "Battle.h"
#include "FactionEncounter.h"
#include "RandomEncounter.h"
#include "CharacterMenu.h"
#include "LoadGame.h"

Game::Game() : State(){

  ///  Mix_HaltMusic();
//  LoadGame lg;/
//  lg.loadCharacters();
    tutorialCount = 0;
    getData()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
    getData()->enemyText = std::make_shared<GUI::Text>();
    getData()->dynamicText = std::make_shared<GUI::Text>();

    refreshGUI();

    getMainText()->setString("Select an option: ");
    //getMainText()->setPosition(GUI::p2pX(20), GUI::p2pY(20));

    getEnemyText()->setString("");


    getDynamicText()->setString("");

	std::vector<std::string> menuOptions;

    gameMenu.reset();
	gameMenu = make_unique<GUI::Menu>();

	textBox = std::make_shared<GUI::textBox>();

	testNpc = std::make_shared<Entity>();
    file = std::make_shared<LoadFiles>("Assets/factionDiag.txt");
///    testNpc->setFaction(file->loadFaction());

	//menuOptions.push_back("0: Quit");
	menuOptions.push_back("Travel");    //1
	menuOptions.push_back("Shop");      //2
	menuOptions.push_back("Level Up");  //3
	menuOptions.push_back("Rest - Cost 10 Gold");   //4
	menuOptions.push_back("Character Menu");        //5
	menuOptions.push_back("Settings");
	menuOptions.push_back("Save Game");             //7
	menuOptions.push_back("Help");                  //9

	gameMenu->setMenuOptions(menuOptions, true);

//	music = Mix_LoadMUS("Assets/Audio/Intro.wav");
//
//	Mix_VolumeMusic(10);

	if(music == NULL){

        printf("Unable to load GAME music..");
	}

                        //Play the music
//                        if( Mix_PlayMusic( music, -1) == -1 )
//                        {
//                            printf("ERROR PLAYING MUSIC Game.cpp line 57.");
//                        }

}

Game::~Game(){

 //Mix_FreeMusic(music);
 State::~State();
}

void Game::update(const float& dt){

    //Play the music
        if(Mix_PlayingMusic() == 0){

                        if( Mix_PlayMusic( music, -1) == -1 )
                        {
                            printf("ERROR PLAYING MUSIC Game.cpp line 57.");
                        }
        }

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

        case 2:
            textBox->setActive(true);
            textBox->setPosition(40, 30);
            textBox->setHeader("Information Screen");
            textBox->setText("Here you will find information about the area you are currently in\n\nPress ENTER to close");
            break;

        default:
            break;
        }
    }

    if(textBox->getActive() || testNpc->getDialogueActive()){

        gameMenu->setActive(false);
    }
    else{

        gameMenu->setActive(true);
    }
    gameMenu->update();

    if(getData()->getActiveCharacter()->getExp() >= getData()->getActiveCharacter()->getExpNext()){

        getData()->dynamicText->setPosition(20.f, 60.f);
        getData()->dynamicText->setString("Level Up Available!!");
    }

    saveCharacters();
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


                seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

                generator.seed(seed);

                std::uniform_int_distribution<int> eventDistribution(1, 6);
                int eventToss = eventDistribution(generator);

                getMainText()->setString("You travel into parts unknown...");
                SDL_Delay(200);
                StateData::GetInstance()->getActiveCharacter()->travel();
               // Event e;

               std::vector<int> numbers = {2, 3, 4};

                // Use std::random_device to obtain a seed for the random number generator
                std::random_device rd;

                // Use std::mt19937 as the random number generator
                std::mt19937 gen(rd());

                // Use std::uniform_int_distribution to generate random indices
                std::uniform_int_distribution<> dis(0, numbers.size() - 1);

                // Generate a random index
                int randomIndex = dis(gen);

                // Access the corresponding element in the set
                int randomValue = numbers[randomIndex];

                if(getData()->getActiveCharacter()->getRep(randomValue) >= 110){

                    switch(randomValue){

                        case 2:
                            //RED, can include
                            numbers.push_back(5);   //BROWN, NEEDS TO CHANGE!!
                            break;

                        case 3:
                            //BLUE
                            numbers.push_back(6);     //AQUA NEED TO CHANGE!!
                            break;

                        case 4:
                            //GREEN;
                            numbers.push_back(7); //PURPLE NEED TO CHANGE!!
                            break;
                    }
                }

                std::uniform_int_distribution<> dis2(0, numbers.size() - 1);
                randomIndex = dis2(gen);
                randomValue = numbers[randomIndex];

               if(eventToss <= 2){

                    Engine::GetInstance()->AddState(std::make_shared<Battle>());
               }

               else if( eventToss > 2){

                   if(getData()->getActiveCharacter()->getRep(randomValue) >= 160){      ///TODO: Magic number

                        Engine::GetInstance()->AddState(std::make_shared<FactionEncounter>(randomValue));
                    }
                    else{

                        Engine::GetInstance()->AddState(std::make_shared<RandomEncounter>(randomValue));
                    }
               }
               else{

                    Engine::GetInstance()->AddState(std::make_shared<RandomEncounter>(randomValue));
               }

               // e.createEvent();
                //StateData::GetInstance()->push_state(std::make_shared<Battle>());
            }

            if(gameMenu->getChoice() == 2){

                StateData::GetInstance()->getActiveCharacter()->levelUp();
               // getMainText()->setString("Levelled up!!");
                getDynamicText()->setString("");
            }

            if(gameMenu->getChoice() == 3){

                if(StateData::GetInstance()->getActiveCharacter()->getGold() >= 10){

                    StateData::GetInstance()->getActiveCharacter()->resetHP();
                    StateData::GetInstance()->getActiveCharacter()->gainGold(-10);

                    getMainText()->setString("You awake feeling well rested");
                    getEnemyText()->setColour(255, 0, 0, 0);
                    getEnemyText()->setString("Lost 10 gold");
                }
                else{

                    getEnemyText()->setColour(255, 0, 0, 0);
                    getEnemyText()->setString("You don't have enough gold.");
                }
            }

            if(gameMenu->getChoice() == 4){

                Engine::GetInstance()->AddState(std::make_shared<CharacterMenu>());
            }

            if(gameMenu->getChoice() == 5){

                Engine::GetInstance()->AddState(std::make_shared<Settings>());
            }


            if(gameMenu->getChoice() == 6){

                saveCharacters();
                getMainText()->setString("Game Saved");
            }

            if(gameMenu->getChoice() == 7){

                tutorialCount = 0;
                StateData::GetInstance()->setTutorial(true);
            }
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_L)){

        //testNpc
        testNpc->createDialogueComponent();
        testNpc->setCharacterName(file->loadName());
        testNpc->setDialogueText(file->loadDialogue());
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){

        std::string msg = "Corruption: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getCorruption());
        getEnemyText()->setString(msg);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(!getMainText()->isEmpty()){

            //getMainText()->clearText();
            getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
            getMainText()->setString("Select an option: ");
        }

        if(!getDynamicText()->isEmpty()){

            getDynamicText()->clearText();
        }

        if(!getEnemyText()->isEmpty()){

            getEnemyText()->clearText();
        }

        if(testNpc->getDialogueActive()){

            testNpc->setDialogueActive(false);
        }

        if(textBox->getActive()){

            textBox->setActive(false);

            if(StateData::GetInstance()->getTutorial() == true){

                if(tutorialCount < 2){

                    tutorialCount++;

                    return;
                }
                StateData::GetInstance()->setTutorial(false);
            }
        }
    }


     State::updateEvents(e);
}

void Game::render(){

    SDL_RenderClear(Engine::GetInstance()->GetRenderer());

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    gameMenu->render();
    getMainText()->render();
    getDynamicText()->render();
    getEnemyText()->render();

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
        if(tutorialCount == 2){

            getMainText()->render();
            textBox->render();

        }
       } //END TUTORIAL
        textBox->render();
    }

    if(testNpc->getDialogueActive()){

        testNpc->renderDialogue();
    }
}
