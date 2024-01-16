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
//    getData()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
 //   getData()->enemyText = std::make_shared<GUI::Text>();
  //  getData()->dynamicText = std::make_shared<GUI::Text>();

	textBox = std::make_shared<GUI::textBox>();
    refreshGUI();

    getMainText()->setString(getActiveCharacter()->getStatsAttributeScreen(), true, GUI::p2pY(120));
    //getMainText()->setPosition(GUI::p2pX(20), GUI::p2pY(20));

    getEnemyText()->setString("");


    getDynamicText()->setString("");

	//std::vector<std::string> menuOptions;


    initButtons();
	testNpc = std::make_shared<Entity>();
    file = std::make_shared<LoadFiles>("Assets/factionDiag.txt");
///    testNpc->setFaction(file->loadFaction());

	//menuOptions.push_back("0: Quit

//    refreshGUI();

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
}

void Game::refreshGUI(){

    State::refreshGUI();
//    getData()->mainText->setString("Select an option.");
	ops.clear();
	ops.push_back("Visit Civilisation");    //1
	ops.push_back("Explore Wilderness");      //2
	ops.push_back("Level Up");  //3
	ops.push_back("Rest - Cost 10 Gold");   //4
	ops.push_back("Inventory");        //5
	ops.push_back("Settings");
	ops.push_back("Save Game");             //7
	ops.push_back("Help");                  //9

	menu->setMenuOptions(ops, true);
	textBox->refreshGUI();
	initButtons();
}

void Game::update(const float& dt){

    //Play the music
        if(Mix_PlayingMusic() == 0){

                        if( Mix_PlayMusic( music, -1) == -1 )
                        {
                            printf("ERROR PLAYING MUSIC Game.cpp line 57.");
                        }
        }

    ///

    if(StateData::GetInstance()->getTutorial() == true){

        switch(tutorialCount){

        case 0:
            textBox->setSize(70, 30);
            textBox->setActive(true);
            textBox->setHeader("Welcome to the tutorial!");
            textBox->setText("Here I will explain some of the screens.\n\nPress ENTER to continue...");
            textBox->setPosition(GUI::p2pX(20), GUI::p2pY(20));
            break;

        case 1:
            //textBox->setSize(50, 50);
            textBox->setActive(true);
            textBox->setHeader("Main Menu");
            textBox->setText("Here is your main menu, scroll using the UP and DOWN arrow buttons\n\nPress ENTER to continue...");
            textBox->setPosition(GUI::p2pX(40), GUI::p2pY(10));
            break;

        case 2:
            textBox->setActive(true);
            textBox->setHeader("Information Screen");
            textBox->setText("Here you will find information about the area you are currently in\n\nPress ENTER to close");
            textBox->setPosition(GUI::p2pX(40), GUI::p2pY(30));
            break;

        default:
            break;
        }
    }

    if(textBox->getActive() || testNpc->getDialogueActive()){

        menu->setActive(false);
    }
    else{

        menu->setActive(true);
    }
    menu->update();

    if(getData()->getActiveCharacter()->getExp() >= getData()->getActiveCharacter()->getExpNext()){

        getData()->dynamicText->setPosition(20.f, 60.f);
        getData()->dynamicText->setString("Level Up Available!!");
    }

    saveCharacters();
}

void Game::initButtons(){

    unsigned int charSize = GUI::calcCharSize(125);


    mButtons["SKILLS"] = new GUI::Button(27.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["SKILLS"]->setRenderText("Skills");

    mButtons["FACTIONS"] = new GUI::Button(42.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["FACTIONS"]->setRenderText("Factions");

    mButtons["ATTRIBUTES"] = new GUI::Button(57.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["ATTRIBUTES"]->setRenderText("Attributes");

//    mButtons["INVENTORY"] = new GUI::Button(65.f, 65.5f, 11.8f, 4.1f, charSize);
//    mButtons["INVENTORY"]->setRenderText("Inventory");

}

void Game::updateEvents(SDL_Event& e){

    menu->update();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN) && e.key.repeat == 0){

        menu->scrollText(0);
    }

      if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP) && e.key.repeat == 0){

        menu->scrollText(1);
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        //updateMouseEvents(e.button);
        //GAME LOOP HERE
        if(menu->isSelected()){

            if(menu->getChoice() == 0){


                seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

                generator.seed(seed);

                std::uniform_int_distribution<int> eventDistribution(1, 6);
                int eventToss = eventDistribution(generator);

                getMainText()->setString("You travel into parts unknown...");
                SDL_Delay(200);
                StateData::GetInstance()->getActiveCharacter()->travel();
               // Event e;




               /*** BEGIN RANDOM VALUE **/
               std::vector<int> numbers = {2, 3, 4};
                int randomValue = getRandomValue(0, numbers.size() - 1);
                /*** END RANDOM VALUE **/


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

                int randomIndex = getRandomValue(0, numbers.size() - 1);
                randomValue = numbers[randomIndex];


//               if(eventToss <= 2){
//
//                    Engine::GetInstance()->AddState(std::make_shared<Battle>());
//               }

               if( eventToss < 2){

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

            if(menu->getChoice() == 1){

                Engine::GetInstance()->AddState(std::make_shared<Battle>());
            }

            if(menu->getChoice() == 2){

                StateData::GetInstance()->getActiveCharacter()->levelUp();
               // getMainText()->setString("Levelled up!!");
                getDynamicText()->setString("");
            }

            if(menu->getChoice() == 3){

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

            if(menu->getChoice() == 4){

                Engine::GetInstance()->AddState(std::make_shared<CharacterMenu>());
            }

            if(menu->getChoice() == 5){

                Engine::GetInstance()->AddState(std::make_shared<Settings>());
            }


            if(menu->getChoice() == 6){

                saveCharacters();
                getMainText()->setString("Game Saved");
            }

            if(menu->getChoice() == 7){

                tutorialCount = 0;
                StateData::GetInstance()->setTutorial(true);
            }
        }

         //BUTTONS START HERE
        if (mButtons["SKILLS"]->isPressed(e.button)) {

         //   menu->setActive(false);
          //  invMenu2->setActive(false);

            //mButtons["SKILLS"]->setSelected(true);
            //mButtons["ATTRIBUTES"]->setSelected(false);
            //mButtons["INVENTORY"]->setSelected(false);
            //mButtons["FACTIONS"]->setSelected(false);

            std::string msg = StateData::GetInstance()->getActiveCharacter()->displaySkills();
            getMainText()->setString(msg, true, GUI::p2pY(420));
        }

        if (mButtons["FACTIONS"]->isPressed(e.button)) {

            //mButtons["SKILLS"]->setSelected(false);
            //mButtons["ATTRIBUTES"]->setSelected(false);
            //mButtons["INVENTORY"]->setSelected(false);
            //mButtons["FACTIONS"]->setSelected(true);

          //  menu->setActive(false);
           // invMenu2->setActive(false);
            std::string fact = StateData::GetInstance()->getActiveCharacter()->getFactionStr();
            getMainText()->setString(fact, true, 420);
        }

        if (mButtons["ATTRIBUTES"]->isPressed(e.button)) {

            //mButtons["SKILLS"]->setSelected(false);
            //mButtons["ATTRIBUTES"]->setSelected(true);
            //mButtons["INVENTORY"]->setSelected(false);
            //mButtons["FACTIONS"]->setSelected(false);

            //menu->setActive(true);
            //invMenu2->setActive(false);

            //std::cout << "Attrib pressed\n\n\n\n\n";

           /// StateData::GetInstance()->getActiveCharacter()->getAttributes();
           /// getMainText()->setString("ATTRIBUTES");
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, 420);
//            getMainText()->setFontSize(10);
        }

    }   ///END MOUSEBUTTONDOWN

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
            getMainText()->setString(getActiveCharacter()->getStatsAttributeScreen(), true, GUI::p2pY(120));
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
    menu->render();
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

            menu->render();
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

     for (auto i : mButtons) {

		i.second->renderButtons();
	}
}
