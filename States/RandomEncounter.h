#pragma once

#include "State.h"
#include "NPC.h"
#include "GUI.h"
#include "LoadFiles.h"

class RandomEncounter : public State{

    public:

        RandomEncounter(int faction = -1);
        ~RandomEncounter();

        void update(const float& dt);
        void updateEvents(SDL_Event& e);
        void runMenuSelection();
        void render();

        void refreshGUI();
        bool charm();
        bool rob();

        void attemptSteal();
        void barter();

    private:

        std::shared_ptr<NPC> npc;
        std::shared_ptr<GUI::Menu> menu;
        std::shared_ptr<LoadFiles> file;
        std::string filename;
        bool firstEncounter;
        bool unlockedCharm;
        int choice;
};
