#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <memory>

#include "State.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine{

public:

    static Engine* GetInstance(){       //Checks if object is created, if true returns object if false create object

            return s_Instance = (s_Instance != nullptr) ?  s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update(float dt);
        void UpdateEvents(SDL_Event &event);
        void Render();
        void Events();

        inline bool IsRunning() { return m_IsRunning; }
        inline SDL_Renderer* GetRenderer() { return m_Renderer; }
        inline SDL_Window* GetWindow() { return m_Window; }
        inline void AddState(std::shared_ptr<State> s) { mStates.push_back(s); currentState++; }
        inline void PopState(){ if(!mStates.empty()){ mStates.pop_back(); currentState--;} }

private:

        Engine(){}
        bool m_IsRunning;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance; //static object ptr singleton



        ///TEST
        ///Probably need an InitStateData function...
        std::vector<std::shared_ptr<class State>> mStates;
        int currentState;
//        GameMap* m_LevelMap;


};

#endif // ENGINE_H

