#pragma once

#include "State.h"
#include "NPC.h"
#include "LoadFiles.h"


class FactionEncounter : public State{

    public:

        FactionEncounter();
        virtual ~FactionEncounter();

        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void render();

    private:

         std::shared_ptr<LoadFiles> file;
         std::shared_ptr<NPC> npc;
         std::string m_fileName;
         std::shared_ptr<GUI::Menu> m_menu;
         static int position;
};
