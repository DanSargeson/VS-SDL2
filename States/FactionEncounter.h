#pragma once

#include "State.h"
#include "NPC.h"
#include "LoadFiles.h"


class FactionEncounter : public State{

    public:

        FactionEncounter(int faction);
        virtual ~FactionEncounter();

        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void render();

        void refreshGUI();

    private:

         std::shared_ptr<LoadFiles> file;
         std::shared_ptr<NPC> npc;
         std::string m_fileName;
         std::string json_file;
        // std::shared_ptr<GUI::Menu> m_menu;
         static int position;

         bool firstEncounter;

         std::map<std::string, std::map<int, Dialogue>> dialogueMap;

};
