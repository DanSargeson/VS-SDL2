#include "Battle.h"
#include "Engine.h"
#include "Input.h"
#include "PlayerDeath.h"

Battle::Battle() : State(), missCounter(0), alpha(255), alpha2(255), battleTxtTimer(std::make_unique<Timer>()), battleGameTimer(std::make_unique<GameTimer>())/*, seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())), generator(seed)*/, noOfEnemies(0) {

     std::uniform_int_distribution<int> numEnemiesDistribution(1, 3);
     noOfEnemies = numEnemiesDistribution(generator);

     totalEXP = 0;
     totalGold = 0;

     player = StateData::GetInstance()->getActiveCharacter();

    std::vector<std::string> ops;
    ops.push_back("Attack");
    ops.push_back("Defend");
    ops.push_back("Use Item");
    battleMenu.reset();
    battleMenu = std::make_shared<GUI::Menu>();
    battleMenu->setMenuOptions(ops, true);

    enemyMenu.reset();
    enemyMenu = std::make_shared<GUI::Menu>();

    enemyMenu->setActive(false);

    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(5, 10, 12, 8, true);
    StateData::GetInstance()->mainText->setString("Test");

    StateData::GetInstance()->dynamicText = std::make_shared<GUI::Text>(false);
    StateData::GetInstance()->dynamicText->setPosition(GUI::p2pX(20), GUI::p2pY(10));
    StateData::GetInstance()->dynamicText->setString("You are attacked: ");

    StateData::GetInstance()->enemyText = std::make_shared<GUI::Text>(true);
    StateData::GetInstance()->enemyText->setPosition(GUI::p2pX(20), GUI::p2pY(50));
    StateData::GetInstance()->enemyText->setString("Selectaaaaa an option: ");
    StateData::GetInstance()->enemyText->setColour(255, 0, 0, 0);

    playerAttkTxt = std::make_unique<GUI::Text>(true);
    playerAttkTxt->setColour(0, 0, 255, 0);
    playerAttkTxt->setPosition(GUI::p2pX(60), GUI::p2pY(20));
    playerAttkTxt->clearText();

    enemyAttkTxt = std::make_unique<GUI::Text>(true);
    enemyAttkTxt->setColour(255, 0, 0, 0);
    enemyAttkTxt->setPosition(GUI::p2pX(60), GUI::p2pY(50));
    enemyAttkTxt->clearText();

    playerTurn = false;
    endTurn = false;
	choice = 0;
	playerAccuracy = 0;
	playerDefence = 0;
	playerTotal = 0;
	enemyAccuracy = 0;
	enemyDefence = 0;
	enemyTotal = 0;
	combatTotal = 0;
	combatRoll = 0;
	combatRollPlayer = 0;
	combatRollEnemy = 0;
	while(enemies.size() > 0) {
		enemies.erase(enemies.begin());
	}

	//COIN TOSS DETERMINES TURN


	seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

     generator.seed(seed);

     std::uniform_int_distribution<int> coinDistribution(1, 6);
     int coinToss = coinDistribution(generator);
//	if (coinToss <= 4)
//		playerTurn = true;
//	else
//		playerTurn = false;


	playerTurn = (coinToss <= 4);
	escape = false;
	playerDefeated = false;
	enemyDefeated = false;

//	noOfEnemies = 2;

    //int x = GUI::p2pXi(10);
    //int y = GUI::p2pYi(25);
	for (size_t i = 0; i < noOfEnemies; i++){
		std::cout << "LEVEL:: " << std::to_string(StateData::GetInstance()->getActiveCharacter()->getLevel()) << "\n\n\n";
		int low = getData()->getActiveCharacter()->getLevel() - 1;
		int high = getData()->getActiveCharacter()->getLevel() * 2;

		int rando = 0;
		if(low <= 0){

            rando = 1;
		}

		rando = rand() % high + low;
		//int lvl = StateData::GetInstance()->getActiveCharacter()->getLevel();
		enemies.push_back(Enemy(rando));
		//std::string msg = "test " + std::to_string(i);
	//	y += (i * 2);
        //temp.setString();
		enemyText.push_back(GUI::Text());
        SDL_Delay(19);
	}

	for(size_t i = 0; i < enemies.size(); i++){

        enemyText[i].setString(enemies[i].getName());
		enemyText[i].setPosition(96, 140 + (i * 40));
	}

	//BATTLE VARIABLES
	attackRoll = 0;
	defendRoll = 0;
	damage = 0;
	gainEXP = 0;
	gainGold = 0;

	battleEyes = std::make_shared<GUI::Tooltip>();

	initBattle();
}

Battle::~Battle(){

    battleMenu.reset();
    enemyMenu.reset();

    enemyAttkTxt.reset();
    playerAttkTxt.reset();

    StateData::GetInstance()->mainText->clearText();
    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
    if(!escape){
        StateData::GetInstance()->mainText->setString("Select an option: ");
    }
    else{
        StateData::GetInstance()->mainText->setString("Ran away safely!!");
    }
    StateData::GetInstance()->enemyText->clearText();
    StateData::GetInstance()->dynamicText->clearText();
    enemies.clear();
}


void Battle::initBattle(){

battleGameTimer->start();

if(!escape && !playerDefeated && !enemyDefeated) {

		if (playerTurn && !playerDefeated) {
            //TODO:: HERE IS WHERE TO CHANGE THINGS FOR BATTLEMODE
            std::vector<std::string> ops;
            ops.push_back("Attack");
            ops.push_back("Defend");
            ops.push_back("Use Item");
            battleMenu->setMenuOptions(ops, true);
            std::string msg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            std::string enemyMsg = "";
            if(battleMenu->getActive()){

                for(int i = 0; i < enemies.size(); i++){

                    enemyMsg += enemies[i].getName() + ": " + "HP: " + std::to_string(enemies[i].getHP()) + "/" + std::to_string(enemies[i].getHPMax()) + " ";
                }
                StateData::GetInstance()->enemyText->setString(enemyMsg);
            }
			}
        }

        else{

            enemyAttacks();
        }
}


void Battle::updateMenu(){


    StateData::GetInstance()->dynamicText->setString("Which enemy to attack?: ");
    std::vector<std::string> enemyMenuStr;

    for(int i = 0; i < enemies.size(); i++){

        enemyMenuStr.push_back(enemies[i].getName());
    }

    enemyMenu->setMenuOptions(enemyMenuStr, true);
    enemyMenu->setActive(true);
    battleMenu->setActive(false);
}

void Battle::update(const float& dt){


if(endTurn){

    battleMenu->setActive(false);
    return;
}

battleMenu->update();

battleTxtTimer->Tick();

if(playerDefeated){

    StateData::GetInstance()->mainText->setColour(255, 0, 0, 0);
    StateData::GetInstance()->mainText->setString("You Died!");

    playerTurn = false;
    endTurn = true;

//    ~Battle();
    Engine::GetInstance()->PopState();
    Engine::GetInstance()->AddState(std::make_shared<PlayerDeath>());

    return;
}


            std::string msg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            StateData::GetInstance()->mainText->setString(msg);
            StateData::GetInstance()->mainText->render();
            std::string enemyMsg = "";
            for(int i = 0; i < enemies.size(); i++){

                enemyMsg += enemies[i].getName() + ": " + "HP: " + std::to_string(enemies[i].getHP()) + "/" + std::to_string(enemies[i].getHPMax()) + " ";
            }
            StateData::GetInstance()->enemyText->setString(enemyMsg);

    if(!escape && !playerDefeated && !enemyDefeated) {

		if (playerTurn && !playerDefeated) {

        //#############FINALISE TURN
            if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
                playerDefeated = true;
//                ~Battle();
                Engine::GetInstance()->PopState();
                Engine::GetInstance()->AddState(std::make_shared<PlayerDeath>());

                return;
            }
            else if (enemies.size() <= 0) {
                enemyDefeated = true;
                cout << "All enemies defeated!\n\n";
  //              ~Battle();
                Engine::GetInstance()->PopState();
            }
        }

        if(!playerTurn && !playerDefeated){

                //std::cout << "DT:  " << battleGameTimer->getTicks() << std::endl;
                if(battleGameTimer->getTicks() > 300){
                    enemyAttacks();
                    battleGameTimer->stop();
                }
        }
	}


        updateText();
}

void Battle::updateText(){

    if(playerAttkTxt && playerTurn){

        if(alpha >= 0 && battleTxtTimer->GetDeltaTime() <= 3){

            alpha -= 5;
            SDL_SetTextureAlphaMod(playerAttkTxt->getTexture(), alpha);
            battleTxtTimer->Restart();
        }
        else{

            playerAttkTxt->clearText();
            alpha = 255;
        }
    }


    if(enemyAttkTxt){

        if(alpha2 >= 0){

            alpha2 -= 5;
            SDL_SetTextureAlphaMod(enemyAttkTxt->getTexture(), alpha2);
        }
        else{

            enemyAttkTxt->clearText();
            alpha2 = 255;
        }
    }
}


const void Battle::playerAttacks(){

///            combatTotal = enemies[choice].getDefence() + StateData::GetInstance()->getActiveCharacter()->getAccuracy();
            enemyTotal = enemies[choice].getSkill(2); /// / (double)combatTotal * 100;
///            playerTotal = StateData::GetInstance()->getActiveCharacter()->getAccuracy() / (double)combatTotal * 100;

            playerTotal = StateData::GetInstance()->getActiveCharacter()->getSkill(0); //0 == MELEE
            combatTotal = enemies[choice].getSkill(2); // 2 == DEFENCE

            seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
             generator.seed(seed);
             std::uniform_int_distribution<int> playerTotalDistribution(1, playerTotal);
             combatRollPlayer = playerTotalDistribution(generator);

             std::uniform_int_distribution<int> enemyTotalDistribution(1, enemyTotal);
             combatRollEnemy = enemyTotalDistribution(generator);


				if (combatRollPlayer > combatRollEnemy || missCounter >= 5) { //###########PLAYER HITS
					//HIT
					missCounter = 0;
					damage = StateData::GetInstance()->getActiveCharacter()->getDamage();
					enemies[choice].loseHP(damage);
//					if(totalDmg < 0){
//                        totalDmg = 1;
//					}
					std::string dmgMsg = "HIT for " + std::to_string(damage) + " damage!";
					playerAttkTxt->setString(dmgMsg);
					alpha = 255;

					//#####PLAYER WINS
					if (!enemies[choice].isAlive()) {
						endMsg = " YOU DEFEATED!\n\n";
						gainGold = rand() & enemies[choice].getLevel() * 10 + 1;
						totalGold += gainGold;
						StateData::GetInstance()->getActiveCharacter()->setGold(gainGold);
						gainEXP = enemies[choice].getExp();
						totalEXP += gainEXP;
						StateData::GetInstance()->getActiveCharacter()->gainXP(gainEXP);


                        endMsg += "Gold Gained: " + std::to_string(gainGold) + "\n";
                        endMsg += "EXP Gained: " + std::to_string(gainEXP);
						if(enemies.size() == 1){

                            endMsg += "\n\nTotal EXP Gained: " + std::to_string(totalEXP);
                            endMsg += "\n Total Gold Gained: " + std::to_string(totalGold);
						}

						//ITEM ROLL
						seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

                        generator.seed(seed);

                        std::uniform_int_distribution<int> itemDistribution(1, 100);
                        int r = itemDistribution(generator);


						//int r = rand() % 100 + 1;
						int rarity = -1;
						if (r <= 70) {
							//GET ITEM
							rarity = 0; //COMMON ITEM
							//int newRoll = rand() % 100 + 1;
                        }
                        else if (r > 70 && r <= 80) {
								rarity = 1; //UNCOMMON ITEM
                        }

                        else if(r > 80 && r <= 85 && StateData::GetInstance()->getActiveCharacter()->getLevel() > 20) {
                            rarity = 2; //RARE
                        }

                        else if(r > 85 && r < 95 && StateData::GetInstance()->getActiveCharacter()->getLevel() > 35){
                            rarity = 3;
                        }
                        else if(r > 95 && StateData::GetInstance()->getActiveCharacter()->getLevel() >= 50){

                            rarity = 4;
                        }

                        //TODO DEBUG REMOVE!!!!

                        seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
                        generator.seed(seed);
                        r = itemDistribution(generator);
                        int lvl = 10;

							if (r >= 50) {

								if (r <= 75) {
///									int lvl = StateData::GetInstance()->getActiveCharacter()->getLevel();
									Weapon tempW(lvl, rarity);
									auto tempWe = make_shared<Weapon>(tempW);
									StateData::GetInstance()->getActiveCharacter()->addItem(tempWe);
									endMsg += "\nWeapon dropped: ";
									endMsg +=  tempWe->getName() + " " + tempWe->getTypeStr() + "\n";
								}
								else {
									Armour tempA(lvl, rarity);
									auto tempAw = make_shared<Armour>(tempA);
									StateData::GetInstance()->getActiveCharacter()->addItem(tempAw);
									endMsg += "\nArmour dropped: ";
									endMsg += tempAw->getName() + " " + tempAw->getTypeStr() + "\n";
								}
							}
                        StateData::GetInstance()->dynamicText->setString(endMsg, true, GUI::p2pY(80));
						enemies.erase(enemies.begin() + choice);
						enemyText.erase(enemyText.begin() + choice);
//						int s = enemies.size();
//						std::cout << std::endl << std::to_string(s);
						for(size_t i = 0; i < enemies.size(); i++){

                            enemyText[i].setString(enemies[i].getName());
                            enemyText[i].setPosition(96, 140 + (i * 40));
                        }
					} //####END PLAYER WINS
				}
				else {
					//MISS
					playerAttkTxt->setString("Missed enemy!");
					alpha = 255;
					missCounter++;
					cout << "MISSED ENEMY!\n\n";
				}

				battleGameTimer->start();
}

const void Battle::enemyAttacks(){

    std::string enemyMsg = "";

    if(enemies.size() <= 0){

        endTurn = true;
        return;
    }

    if(!playerTurn && !escape && !enemyDefeated){
			//ENEMY TURN
			for (size_t i = 0; i < enemies.size(); i++){    //TIMER NEEDS TO GO AROUND HERE....
				//combatTotal = enemies[i].getAccuracy() + StateData::GetInstance()->getActiveCharacter()->getDefence();
				//enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
				//playerTotal = StateData::GetInstance()->getActiveCharacter()->getDefence() / (double)combatTotal * 100;

				enemyTotal = enemies[i].getSkill(0); //0 == MELEE
				playerTotal = StateData::GetInstance()->getActiveCharacter()->getSkill(2); //2 == DEFENCE
                combatTotal = StateData::GetInstance()->getActiveCharacter()->getSkill(2); // 2 == DEFENCE

				seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
             generator.seed(seed);
             std::uniform_int_distribution<int> playerTotalDistribution(1, playerTotal);
             combatRollPlayer = playerTotalDistribution(generator);

             std::uniform_int_distribution<int> enemyTotalDistribution(1, enemyTotal);
             combatRollEnemy = enemyTotalDistribution(generator);

				if (combatRollPlayer < combatRollEnemy) {
					//HIT
					damage = enemies[i].getDamage();
					StateData::GetInstance()->getActiveCharacter()->loseHP(damage);
					enemyMsg += "\n" + enemies[i].getName() + " HIT for " + std::to_string(damage) + " damage! ";
					alpha2 = 255;
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
						cout << "YOU DIED!\n\n";
						playerDefeated = true;
						break;
					}
				}
				else {
					//MISS
					enemyMsg += "\n" + enemies[i].getName() + " Missed! ";
					alpha2 = 255;
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					cout << "ENEMY MISSED!\n\n";
				}
			}

            std::string msg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            StateData::GetInstance()->mainText->setString(msg);
			//END TURN
			 endTurn = true;
		}
}

void Battle::updateEvents(SDL_Event& e){

    battleMenu->update();
    enemyMenu->update();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(endTurn){

            endTurn = false;
            playerTurn = true;
            StateData::GetInstance()->dynamicText->setString("Choose action: ");
            battleMenu->setActive(true);
        }
    }

    /** THIS IS THE RUN AWAY FROM BATTLE CODE         */

                if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE) && playerTurn){


                    int coinToss = rand() % 2 + 1;
                        if (coinToss == 2){
                            StateData::GetInstance()->dynamicText->setString("Ran away!!");
                            escape = true;
                            //return;
                        }
                        else{
                            escape = false;
                        }

                    if(!escape){
                        alpha = 255;
                        playerAttkTxt->setString("Failed to escape");
                        playerTurn = false;
                        enemyAttacks();

                        return;
                    }
                    else{
                        Engine::GetInstance()->PopState();
                        return;
                    }

                }


                /*  END OF RUNNING FROM BATTLE  */

    if(e.type == SDL_MOUSEBUTTONDOWN){
//                choice = 12;
//
//
//            }

        if(battleMenu->isSelected()){

        int choice = battleMenu->getChoice();

        if(battleMenu->getChoice() == 0){


            ///THIS NEEDS TO BE THE ENEMY MENU

            std::vector<std::string> ops;

            for(int i = 0; i < enemies.size(); i++){

                ops.push_back(enemies[i].getName());
            }

            enemyMenu->setMenuOptions(ops, true);
            enemyMenu->setActive(true);
            battleMenu->setActive(false);

            }
        }

        if(enemyMenu->isSelected() && playerTurn){

            choice = enemyMenu->getChoice();

            ///THIS GOES IN THE SELECTED ENEMY
            playerAttacks();
            //TODO: Should go below so defence, items etc work
            playerTurn = false;
            enemyMenu->setActive(false);
            battleMenu->setActive(true);

        }
            ///END IN ENEMY
    }

    //std::cout << "THE CHOICE IS CURRENTLY: " << std::to_string(choice) << "\n";
    if(e.type == SDL_MOUSEMOTION){

        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_Rect r;

        for(int i = 0; i < enemies.size(); i++){


        r = enemyText[i].getPositionRect();

        if(x > r.x &&
           x < r.x + r.w &&
           y > r.y &&
           y < r.y + r.h){

                std::string msg = "HP: " + std::to_string(enemies[i].getHP()) + "/" + std::to_string(enemies[i].getHPMax())
                    + "\nAttack: ????\nDefence: ????";
                msg += "\nSkills: \nDefence Sk: " + std::to_string(enemies[i].getSkill(2));
                msg += "\nMelee Sk: " + std::to_string(enemies[i].getSkill(0));
                battleEyes->setDisplayText(msg);
                battleEyes->update(x, y);
                battleEyes->setHidden(false);

                return;
           }
           else{

                battleEyes->setHidden(true);
           }
        }
    }
}

void Battle::render(){

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    StateData::GetInstance()->mainText->render();
    StateData::GetInstance()->enemyText->render();
    StateData::GetInstance()->dynamicText->render();

    if(alpha2 > 10){
        enemyAttkTxt->render();
    }
    if(alpha > 10){
        playerAttkTxt->render();
    }

    if(endTurn || battleMenu->getActive()){
        battleMenu->render();
    }
    else if(enemyMenu->getActive()){
        enemyMenu->render();
    }

    for(int i = 0; i < enemyText.size(); i++){

        enemyText[i].render();
    }

    battleEyes->render();
}
