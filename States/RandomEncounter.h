#pragma once

#include "State.h"
#include "NPC.h"
#include "GUI.h"
#include "LoadFiles.h"

class RandomEncounter : public State{

    public:

        RandomEncounter();
        ~RandomEncounter();

        void update(const float& dt);
        void updateEvents(SDL_Event& e);
        void render();

    private:

        std::shared_ptr<NPC> npc;
        std::shared_ptr<GUI::Menu> menu;
        std::shared_ptr<LoadFiles> file;
        std::string filename;
};
