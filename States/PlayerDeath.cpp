#include "PlayerDeath.h"
#include "Timer.h"
#include "Engine.h"

PlayerDeath::PlayerDeath() : State(){

    textTimer = std::make_unique<Timer>();
    alpha = 0;
    StateData::GetInstance()->mainText->setString("YOU DIED!");
    SDL_SetTextureAlphaMod(StateData::GetInstance()->mainText->getTexture(), alpha);
}

void PlayerDeath::update(const float& dt){

//    Timer::GetInstance()->Tick();
    textTimer->Tick();
    if(textTimer->GetDeltaTime() <= 10000){
        alpha += 1;

        if(alpha > 255){
            alpha = 255;
        }

        SDL_SetTextureAlphaMod(StateData::GetInstance()->mainText->getTexture(), alpha);
    }
}

void PlayerDeath::updateEvents(SDL_Event& e){

}

void PlayerDeath::render(){

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 200, 127, 0, 25);
    StateData::GetInstance()->mainText->render();
}

