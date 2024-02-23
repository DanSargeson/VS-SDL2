#ifndef BATTLE_H
#define BATTLE_H

#include <thread>
#include <atomic>

#include "State.h"
#include "Timer.h"
#include "Player.h"

class Battle : public State{

    public:

        Battle();
        ~Battle();

        void update(const float &dt);
        void updateEvents(SDL_Event &e);

        void initBattle();
        void updateMenu();
        void updateText();
        void updateWinText();
        const void enemyAttacks();
        const void playerAttacks();
        void render();
        void refreshGUI();

        void startTextThread();
        void startWinThread();

        void runMenuSelection();

    private:
        std::shared_ptr<GUI::Menu> battleMenu;
        std::shared_ptr<GUI::Menu> enemyMenu;
        std::vector<std::shared_ptr<Enemy>> enemies;
        std::vector<std::shared_ptr<GUI::textBox>> enemyTextBoxes;
        std::vector<std::shared_ptr<GUI::Text>> enemyText;
        GUI::Text temp;

        std::unique_ptr<GUI::textBox> battleCloseMsg;

        std::unique_ptr<Timer> battleTxtTimer;
        std::unique_ptr<GameTimer> battleGameTimer;
        std::unique_ptr<GameTimer> endGameTimer;

        bool playerTurn;
        bool playerWins;
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
        float winAlpha;

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
        int totalEXP;
        int totalGold;
        int gainGold;

        int missCounter;
        int enemyMissCounter;
        bool endTurn;

        std::string endMsg;
        std::unique_ptr<GUI::Text> playerAttkTxt;
        std::unique_ptr<GUI::Text> enemyAttkTxt;

        std::thread textThread;
        std::thread winThread;
        std::atomic<bool> textThreadRunning;
        std::atomic<bool> winThreadRunning;




//        unsigned seed;
//        std::default_random_engine generator;

        std::shared_ptr<Player> player;
        std::shared_ptr<GUI::Tooltip> battleEyes;
};

#endif // BATTLE_H
