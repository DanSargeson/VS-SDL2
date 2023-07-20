#include "PlayerDeath.h"
#include "Timer.h"
#include "Engine.h"

PlayerDeath::PlayerDeath() : State(){

    textTimer = std::make_unique<GameTimer>();
    alpha = 0;

    SDL_RenderClear(Engine::GetInstance()->GetRenderer());

    deathMsg = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), false);

    deathMsg->setFontSize(150);
   // int w = StateData::GetInstance()->mainText->getTextWidth();
    deathMsg->setColour(255, 0, 0, 0);
    //deathMsg->setBorder(false);
    deathMsg->setPosition(GUI::p2pX(22), GUI::p2pY(40));
   // deathMsg->clearText();
    deathMsg->setString("YOU DIED!!");
    SDL_SetTextureAlphaMod(deathMsg->getTexture(), alpha);

    StateData::GetInstance()->dynamicText->setString("Continue...");
    StateData::GetInstance()->dynamicText->setPosition(GUI::p2pX(60), GUI::p2pY(80));
    StateData::GetInstance()->dynamicText->setColour(0, 255, 0, 0);

    StateData::GetInstance()->getActiveCharacter()->increaseCorruption();

    textTimer->start();
   // std::cout << deathMsg->getColour() << std::endl;
}

PlayerDeath::~PlayerDeath(){

    StateData::GetInstance()->dynamicText->clearText();
}

void PlayerDeath::update(const float& dt){

//    Timer::GetInstance()->Tick();
    if(textTimer->getTicks() <= 10000){
        alpha += 1;

        if(alpha > 255){
            alpha = 255;
            //textTimer->stop();
        }

        SDL_SetTextureAlphaMod(deathMsg->getTexture(), alpha);
    }
}

void PlayerDeath::updateEvents(SDL_Event& e){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(textTimer->getTicks() > 4000){

            StateData::GetInstance()->getActiveCharacter()->resetHP();
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
    }

    if(textTimer->getTicks() > 4000){

            StateData::GetInstance()->dynamicText->render();
        }
//    std::cout << deathMsg->getColour() << std::endl;
}

