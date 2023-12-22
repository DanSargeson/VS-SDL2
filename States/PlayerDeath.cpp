#include "PlayerDeath.h"
#include "Timer.h"
#include "Engine.h"

PlayerDeath::PlayerDeath() : State(){

    textTimer = std::make_unique<GameTimer>();
    alpha = 0;
    alpha2 = 0;
     int w;
    SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, NULL);

    SDL_RenderClear(Engine::GetInstance()->GetRenderer());

    deathMsg = std::make_shared<GUI::Text>(false);

    deathMsg->setFontSize(100);
   // int w = getMainText()->getTextWidth();
    deathMsg->setColour(255, 0, 0, 0);
    //deathMsg->setBorder(false);
    deathMsg->setString("Gift of Death received");
    int dmX = (w / 2) - (deathMsg->getTextWidth() / 2);
    deathMsg->setPosition(dmX, GUI::p2pY(40));
   // deathMsg->clearText();
    SDL_SetTextureAlphaMod(deathMsg->getTexture(), alpha);

    getDynamicText()->setString("Continue...");
    int dynaX = (w / 2) - (getDynamicText()->getTextWidth() / 2);
    getDynamicText()->setPosition(dynaX, GUI::p2pY(80));
    getDynamicText()->setColour(0, 255, 0, 0);

    StateData::GetInstance()->getActiveCharacter()->increaseCorruption();

    getEnemyText()->setString("Corruption has increased");
    SDL_SetTextureAlphaMod(getEnemyText()->getTexture(), alpha);
    int enemX = (w / 2) - (getEnemyText()->getTextWidth() / 2);
    getEnemyText()->setPosition(enemX, GUI::p2pY(55));

    //HERE SAVEGAME
    textTimer->start();
   // std::cout << deathMsg->getColour() << std::endl;
}

PlayerDeath::~PlayerDeath(){

    State::~State();
}

void PlayerDeath::update(const float& dt){

//    Timer::GetInstance()->Tick();
    if(textTimer->getTicks() <= 15000){
        alpha += 1;

        if(alpha > 255){
            alpha = 255;
            //textTimer->stop();
        }

        if(textTimer->getTicks() > 1500){

            alpha2 += 1;
        }


        if(alpha2 > 255){

            alpha2 = 255;
        }

        SDL_SetTextureAlphaMod(deathMsg->getTexture(), alpha);
        SDL_SetTextureAlphaMod(getEnemyText()->getTexture(), alpha2);
    }
}

void PlayerDeath::updateEvents(SDL_Event& e){


    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(textTimer->getTicks() > 4000){

            StateData::GetInstance()->getActiveCharacter()->resetHP(); //resets maxHP
            saveCharacters();
            Engine::GetInstance()->PopState();
        }
    }
}

void PlayerDeath::render(){

//    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 200, 127, 0, 25);
   /// SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    ///SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    if(textTimer->getTicks() > 50){
        deathMsg->render();

        if(textTimer->getTicks() > 1500){

            getEnemyText()->render();
        }
    }

    if(textTimer->getTicks() > 4000){

            getDynamicText()->render();
        }
//    std::cout << deathMsg->getColour() << std::endl;
}

