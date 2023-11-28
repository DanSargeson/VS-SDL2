#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "GUI.h"
#include "LoadFiles.h"

class Game : public State{


public:
    Game();
    ~Game();
    	//void setStateData();
//	void updateInput(const float &dt);

    void update(const float &dt);
	void updateEvents(SDL_Event &e);
	void render();

private:
    std::unique_ptr<GUI::Menu> gameMenu;
    std::shared_ptr<GUI::Text> mainText;

    std::shared_ptr<GUI::textBox> textBox;

    std::shared_ptr<Entity> testNpc;

    std::shared_ptr<LoadFiles> file;

    int tutorialCount;
    //Mix_Music *music;
};


#endif // GAME_H

