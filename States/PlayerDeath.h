#ifndef PLAYERDEATH_H
#define PLAYERDEATH_H

#include "Timer.h"
#include "State.h"

class PlayerDeath : public State{


    public:

        PlayerDeath();
        void update(const float &dt);
        void updateEvents(SDL_Event &e);
        void render();

    private:

        std::unique_ptr<GameTimer> textTimer;
        int alpha;
        std::shared_ptr<GUI::Text> deathMsg;
};

#endif
