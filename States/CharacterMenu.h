#ifndef CHARACTERMENU_H
#define CHARACTERMENU_H

#include "GUI.h"
#include "State.h"

class CharacterMenu : public State{

    public:

        CharacterMenu();
        ~CharacterMenu();
        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void render();
        void refreshGUI();

        //void loadCharacters();

    private:
            std::shared_ptr<GUI::Menu> invMenu;
            std::shared_ptr<GUI::Menu> invMenu2;

            int choice;
};

#endif // LOADGAME_H


