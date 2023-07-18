#pragma once

#include "Engine.h"
#include "Timer.h"

int main(int argc, char** argv){

    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning()){

            Engine::GetInstance()->Events();
            Engine::GetInstance()->Update(Timer::GetInstance()->GetDeltaTime());
            Engine::GetInstance()->Render();
            Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();

    return 0;
}


