#ifndef BATTLE_H
#define BATTLE_H

#include "State.h"
#include "Timer.h"

class Battle : public State{

    public:

        Battle();
        ~Battle();

        void update(const float &dt);
        void updateEvents(SDL_Event &e);

        void initBattle();
        void updateMenu();
        void updateText();
        void enemyAttacks();
        void playerAttacks();
        void render();

    private:
        std::shared_ptr<GUI::Menu> battleMenu;
        std::shared_ptr<GUI::Menu> enemyMenu;
        std::vector<Enemy> enemies;

        std::unique_ptr<Timer> battleTxtTimer;
        std::unique_ptr<GameTimer> battleGameTimer;

        bool playerTurn;
        int choice;
        int playerAccuracy;
        int playerDefence;
        int playerTotal;
        int enemyAccuracy;
        int enemyDefence;
        int enemyTotal;
        int combatTotal;
        int combatRoll;
        int combatRollPlayer;
        int combatRollEnemy;
        float alpha;
        float alpha2;

        bool escape;
        bool playerDefeated;
        bool enemyDefeated;
        int noOfEnemies;

        //bool playerAtk;

        //BATTLE VARIABLES
        int attackRoll;
        int defendRoll;
        int damage;
        int gainEXP;
        int gainGold;

        int missCounter;
        bool endTurn;

        std::string endMsg;
        std::unique_ptr<GUI::Text> playerAttkTxt;
        std::unique_ptr<GUI::Text> enemyAttkTxt;


        unsigned seed;
        std::default_random_engine generator;
};

#endif // BATTLE_H
