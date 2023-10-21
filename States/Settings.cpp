#include "Settings.h"
#include "Engine.h"

Settings::Settings(){

    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    StateData::GetInstance()->dynamicText = std::make_shared<GUI::Text>();
    StateData::GetInstance()->dynamicText->setPosition(GUI::p2pX(20), GUI::p2pY(40));
    StateData::GetInstance()->dynamicText->setString("");

    settingsTxt = std::make_unique<GUI::Text>();
    volume = std::make_unique<GUI::Text>();

    settingsTxt->setString("Testing 123");
    settingsTxt->setPosition(GUI::p2pX(20), GUI::p2pY(10));

    volume->setString("Volume");
    volume->setPosition(GUI::p2pX(15), GUI::p2pY(20));

    volumeButton = std::make_unique<GUI::Button>(27.f, 20.5f, 4.f, 4.f, 20);
    volumeButton->setRenderText(">");

    volDown = std::make_unique<GUI::Button>(23.f, 20.5f, 4.f, 4.f, 20);
    volDown->setRenderText("<");
}

Settings::~Settings()
{

}

void Settings::update(const float& dt){

}

void Settings::updateEvents(SDL_Event& e){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_B)){

        Engine::GetInstance()->PopState();
        StateData::GetInstance()->dynamicText->clearText();
        return;
    }

    if(volumeButton->isPressed(e.button)){

        if(Mix_PlayingMusic() != 0 || Mix_VolumeMusic(-1) == 0){

            int currentVol = Mix_VolumeMusic(-1);
            currentVol += 10;
            if(currentVol > 100){

                Mix_VolumeMusic(MIX_MAX_VOLUME);
                currentVol = 100;
            }
            else{

                Mix_VolumeMusic(currentVol);
            }
            std::string txt = "Curr Volume: " + std::to_string(currentVol);
            StateData::GetInstance()->dynamicText->setString(txt);
        }
    }

    if(volDown->isPressed(e.button)){

    if(Mix_PlayingMusic() != 0){

            int currentVol = Mix_VolumeMusic(-1);
            if(currentVol >= 128){

                currentVol = 100;
            }

            currentVol-=10;

            if(currentVol < 0){

                currentVol = 0;
            }
            Mix_VolumeMusic(currentVol);
            std::string txt = "Curr Volume: " + std::to_string(currentVol);
            StateData::GetInstance()->dynamicText->setString(txt);
        }
    }
}

void Settings::render(){


    settingsTxt->render();
    volume->render();
    volumeButton->renderButtons();
    volDown->renderButtons();
    StateData::GetInstance()->dynamicText->render();
}

