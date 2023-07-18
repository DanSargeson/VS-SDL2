#include "Battle.h"
#include "Engine.h"
#include "Input.h"

Battle::Battle() : State(){


    /*
    EXPERMINTAL
    */

    missCounter = 0;
    alpha = 255;
    alpha2 = 255;

     seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

     generator.seed(seed);

     std::uniform_int_distribution<int> numEnemiesDistribution(1, 3);
     noOfEnemies = numEnemiesDistribution(generator);

    /*
        BACK TO OLD WAY
    */

    std::vector<std::string> ops;
    ops.push_back("Attack");
    ops.push_back("Defend");
    ops.push_back("Use Item");
    battleMenu.reset();
    battleMenu = std::make_shared<GUI::Menu>(*StateData::GetInstance());
    battleMenu->setMenuOptions(ops, true);

    enemyMenu.reset();
    enemyMenu = std::make_shared<GUI::Menu>(*StateData::GetInstance());

    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), 5, 10, 12, 8, true);
   // StateData::GetInstance()->mainText->setPosition(GUI::p2pX(5), GUI::p2pY(10));
    //StateData::GetInstance()->mainText->setPositionF(5, 10, 12, 7);
    StateData::GetInstance()->mainText->setString("Test");

    StateData::GetInstance()->dynamicText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), false);
    StateData::GetInstance()->dynamicText->setPosition(GUI::p2pX(20), GUI::p2pY(10));
    StateData::GetInstance()->dynamicText->setString("You are attacked: ");

    //std::cout << StateData::GetInstance()->mainText->getString();

    StateData::GetInstance()->enemyText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), true);
    StateData::GetInstance()->enemyText->setPosition(GUI::p2pX(20), GUI::p2pY(50));
    StateData::GetInstance()->enemyText->setString("Selectaaaaa an option: ");
    StateData::GetInstance()->enemyText->setColour(255, 0, 0, 0);

    playerAttkTxt = std::make_unique<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), true);
    playerAttkTxt->setColour(0, 0, 255, 0);
    playerAttkTxt->setPosition(GUI::p2pX(60), GUI::p2pY(20));
    playerAttkTxt->clearText();

    enemyAttkTxt = std::make_unique<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), true);
    enemyAttkTxt->setColour(255, 0, 0, 0);
    enemyAttkTxt->setPosition(GUI::p2pX(60), GUI::p2pY(50));
    enemyAttkTxt->clearText();

    playerTurn = false;
//    playerAtk = false;
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
     std::cout << std::endl << std::to_string(coinToss);
	//int coinToss = rand() % 2 + 1;
	if (coinToss <= 4)
		playerTurn = true;
	else
		playerTurn = false;

	escape = false;
	playerDefeated = false;
	enemyDefeated = false;
//	noOfEnemies = rand() % 3 + 1;

	for (size_t i = 0; i < noOfEnemies; i++){
		enemies.push_back(Enemy(StateData::GetInstance()->getActiveCharacter()->getLevel() + rand()%5));
	}

	//BATTLE VARIABLES
	attackRoll = 0;
	defendRoll = 0;
	damage = 0;
	gainEXP = 0;
	gainGold = 0;

	initBattle();
}

Battle::~Battle(){

    battleMenu.reset();
    enemyMenu.reset();

    enemyAttkTxt.reset();
    playerAttkTxt.reset();

    StateData::GetInstance()->mainText->clearText();
    //StateData::GetInstance()->mainText->clearText();
    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), 5, 5, 89, 60, true);
    if(!escape){
      //  StateData::GetInstance()->dynamicText->clearText();
        StateData::GetInstance()->mainText->setString("Select an option: ");
    }
    else{
        StateData::GetInstance()->mainText->setString("Ran away safely!!");
    }
    StateData::GetInstance()->enemyText->clearText();
    StateData::GetInstance()->dynamicText->clearText();

//    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), false);
//    StateData::GetInstance()->mainText->setPosition(GUI::p2pX(20), GUI::p2pY(20));
//
//    StateData::GetInstance()->enemyText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), true);
//    StateData::GetInstance()->enemyText->setPosition(GUI::p2pX(50), GUI::p2pY(20));
//    StateData::GetInstance()->enemyText->setStringenemyText->setStringenemyText->setString("Select an option: ");
}


void Battle::initBattle(){

if(!escape && !playerDefeated && !enemyDefeated) {

		if (playerTurn && !playerDefeated) {
            //TODO:: HERE IS WHERE TO CHANGE THINGS FOR BATTLEMODE
            std::vector<std::string> ops;
            ops.push_back("Attack");
            ops.push_back("Defend");
            ops.push_back("Use Item");
            battleMenu->setMenuOptions(ops, true);
            std::string msg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHpMax());
            //StateData::GetInstance()->mainText->setString(msg);
            std::string enemyMsg = "";
            if(battleMenu->getActive()){

                for(int i = 0; i < enemies.size(); i++){

                    enemyMsg += enemies[i].getName() + ": " + "HP: " + std::to_string(enemies[i].getHp()) + "/" + std::to_string(enemies[i].getHpMax()) + " ";
                }
                StateData::GetInstance()->enemyText->setString(enemyMsg);
            }
			cout << "Choose action: \n";
			}
        }

        else{

            enemyAttacks();
        }

        //endTurn = true;
}


//TODO: Update menu should be something like setMenuToEnemies...
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

if(playerDefeated){

    StateData::GetInstance()->mainText->setColour(255, 0, 0, 0);
    StateData::GetInstance()->mainText->setString("You Died!");

    playerTurn = false;
    endTurn = true;
    return;
}


            std::string msg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHpMax());
            StateData::GetInstance()->mainText->setString(msg);
            std::string enemyMsg = "";
            for(int i = 0; i < enemies.size(); i++){

                enemyMsg += enemies[i].getName() + ": " + "HP: " + std::to_string(enemies[i].getHp()) + "/" + std::to_string(enemies[i].getHpMax()) + " ";
            }
            StateData::GetInstance()->enemyText->setString(enemyMsg);
    //############################START OF INIT BATTLE
    if(!escape && !playerDefeated && !enemyDefeated) {

		if (playerTurn && !playerDefeated) {

//            if(!playerTurn && !playerDefeated){
//
//                enemyAttacks();
//            }

        //#############FINALISE TURN
            if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
                playerDefeated = true;
                Engine::GetInstance()->PopState();
            }
            else if (enemies.size() <= 0) {
                enemyDefeated = true;
                cout << "All enemies defeated!\n\n";
                Engine::GetInstance()->PopState();
            }
        }

        if(!playerTurn && !playerDefeated){

                enemyAttacks();
        }
	}

	//if(playerAttkTxt && enemyAttkTxt){
        updateText();
	//}
}

void Battle::updateText(){


    if(playerAttkTxt){

//      if(alpha > 5){
//
//            StateData::GetInstance()->dynamicText->render();
//        }s
        if(alpha >= 0){

            alpha -= 1;
            //SDL_Delay(200);
            SDL_SetTextureAlphaMod(playerAttkTxt->getTexture(), alpha);
          //  SDL_Delay(20);
        }
        else{

            playerAttkTxt->clearText();
            alpha = 255;
        }
    }


    if(enemyAttkTxt){

//      if(alpha > 5){
//
//            StateData::GetInstance()->dynamicText->render();
//        }

        if(alpha2 >= 0){

            alpha2 -= 1;
            //SDL_Delay(200);
            SDL_SetTextureAlphaMod(enemyAttkTxt->getTexture(), alpha2);
         //   SDL_Delay(20);
        }
        else{

            enemyAttkTxt->clearText();
            alpha2 = 255;
        }
    }
}


void Battle::playerAttacks(){

            combatTotal = enemies[choice].getDefence() + StateData::GetInstance()->getActiveCharacter()->getAccuracy();
            enemyTotal = enemies[choice].getDefence() / (double)combatTotal * 100;
            playerTotal = StateData::GetInstance()->getActiveCharacter()->getAccuracy() / (double)combatTotal * 100;

            std::cout << "\nCombat total: " << combatTotal << std::endl;
            std::cout << "player total: " << combatTotal << std::endl;
            std::cout << "enemy total: " << combatTotal << std::endl;

            seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
             generator.seed(seed);
             std::uniform_int_distribution<int> playerTotalDistribution(1, playerTotal);
             combatRollPlayer = playerTotalDistribution(generator);

           //  seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
           //  generator.seed(seed);
             std::uniform_int_distribution<int> enemyTotalDistribution(1, enemyTotal);
             combatRollEnemy = enemyTotalDistribution(generator);

             std::cout << "\n\nEnemy: " << combatRollEnemy;
             std::cout << "\nPlayer: " << combatRollPlayer << std::endl << std::endl;
            //combatRollPlayer = rand() % playerTotal + 1;
            //combatRollEnemy = rand() % enemyTotal + 1;

				if (combatRollPlayer > combatRollEnemy || missCounter >= 5) { //###########PLAYER HITS
					//HIT
					missCounter = 0;
					damage = StateData::GetInstance()->getActiveCharacter()->getDamage();
					std::cout << "DAMGE: " << damage << " >>>>>>>>>>>>> ";
					int totalDmg = enemies[choice].takeDamage(damage);
					if(totalDmg < 0){
                        totalDmg = 1;
					}
					std::string dmgMsg = "HIT for " + std::to_string(totalDmg) + " damage!";
					playerAttkTxt->setString(dmgMsg);
					alpha = 255;

					//#####PLAYER WINS
					if (!enemies[choice].isAlive()) {
						endMsg = " YOU DEFEATED!\n\n";
						gainGold += rand() & enemies[choice].getLevel() * 10 + 1;
						StateData::GetInstance()->getActiveCharacter()->setGold(gainGold);
						gainEXP += enemies[choice].getExp();
						StateData::GetInstance()->getActiveCharacter()->setExp(gainEXP);
						endMsg += " Gold Gained: " + std::to_string(gainGold) + "\n";
						endMsg += " EXP Gained: " + std::to_string(gainEXP);

						//ITEM ROLL
						//TODO: CHANGE THIS IT DROPS SOMETHING EVERYTIME...
						seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();

                        generator.seed(seed);

                        std::uniform_int_distribution<int> itemDistribution(1, 100);
                        int r = itemDistribution(generator);


						//int r = rand() % 100 + 1;
						int rarity = -1;
						if (r <= 50) {
							//GET ITEM
							rarity = 0; //COMMON ITEM
							//int newRoll = rand() % 100 + 1;
                        }
                        else if (r > 50 && r <= 75) {
								rarity = 1; //UNCOMMON ITEM
                        }

                        else if(r > 75 && r <= 85 && StateData::GetInstance()->getActiveCharacter()->getLevel() > 20) {
                            rarity = 2; //RARE
                        }

                        else if(r > 85 && StateData::GetInstance()->getActiveCharacter()->getLevel() > 35){
                            rarity = 3;
                        }
                        else if(r > 97 && StateData::GetInstance()->getActiveCharacter()->getLevel() >= 50){

                            rarity = 4;
                        }

                        seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
                        generator.seed(seed);
                        r = itemDistribution(generator);

							if (r >= 50) {

								if (r <= 75) {
									int lvl = StateData::GetInstance()->getActiveCharacter()->getLevel();
									Weapon tempW(lvl, rarity);
									auto tempWe = make_shared<Weapon>(tempW);
									StateData::GetInstance()->getActiveCharacter()->addItem(tempWe);
									endMsg += "\nWeapon dropped: ";
									endMsg +=  tempWe->getName() + " " + tempWe->getTypeStr() + "\n";
								}
								else {
									Armour tempA(StateData::GetInstance()->getActiveCharacter()->getLevel(), rarity);
									auto tempAw = make_shared<Armour>(tempA);
									StateData::GetInstance()->getActiveCharacter()->addItem(tempAw);
									endMsg += "\nArmour dropped: ";
									endMsg += tempAw->getName() + " " + tempAw->getTypeStr() + "\n";
								}
							}
                        StateData::GetInstance()->dynamicText->setString(endMsg, true, GUI::p2pY(80));
						enemies.erase(enemies.begin() + choice);
						cout << "Continue...\n";
						//cin.get();
					} //####END PLAYER WINS
				}
				else {
					//MISS
					playerAttkTxt->setString("Missed enemy!");
					alpha = 255;
					missCounter++;
					cout << "MISSED ENEMY!\n\n";
				}
}

void Battle::enemyAttacks(){

    std::string enemyMsg = "";

    if(!playerTurn && !escape && !enemyDefeated){
			//ENEMY TURN
			//cout << "= ENEMY ATTACKS = \n\n";
			for (size_t i = 0; i < enemies.size(); i++){
				combatTotal = enemies[i].getAccuracy() + StateData::GetInstance()->getActiveCharacter()->getDefence();
				enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
				playerTotal = StateData::GetInstance()->getActiveCharacter()->getDefence() / (double)combatTotal * 100;
				//combatRollPlayer = rand() % playerTotal + 1;
				//combatRollEnemy = rand() % enemyTotal + 1;

				seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
             generator.seed(seed);
             std::uniform_int_distribution<int> playerTotalDistribution(1, playerTotal);
             combatRollPlayer = playerTotalDistribution(generator);

             //seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
             //generator.seed(seed);
             std::uniform_int_distribution<int> enemyTotalDistribution(1, enemyTotal);
             combatRollEnemy = enemyTotalDistribution(generator);

				if (combatRollPlayer < combatRollEnemy) {
					//HIT
					damage = enemies[i].getDamage();
					int totalDmg = StateData::GetInstance()->getActiveCharacter()->takeDamage(damage);
					enemyMsg += "\n" + enemies[i].getName() + " HIT for " + std::to_string(totalDmg) + " damage! ";
					alpha2 = 255;
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					//std::string playMsg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHpMax());
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
						cout << "YOU DIED!\n\n";
						playerDefeated = true;
						break;
					}
				}
				else {
					//MISS
					//enemyAttkTxt->setPosition(GUI::p2pX(20), GUI::p2pY(50));
					enemyMsg += "\n" + enemies[i].getName() + " Missed! ";
					alpha2 = 255;
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					cout << "ENEMY MISSED!\n\n";
				}

				cout << "Continue...\n";
				//fcin.get();
			}

			//END TURN
			//playerTurn = true;
			 endTurn = true;
			 std::cout << endl << endl << "END TURN: " << endTurn << " playerTurn: " << playerTurn << endl;
		}
}

void Battle::updateEvents(SDL_Event& e){

    //choice = -1;
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

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(battleMenu->isSelected() && battleMenu->getActive()){

                choice = 12;
                if(battleMenu->getChoice() == 0 && playerTurn){

                    int coinToss = rand() % 2 + 1;
                        if (coinToss == 2){
                            StateData::GetInstance()->dynamicText->setString("Ran away!!");
                            escape = true;
                            //return;
                        }
                        else
                            escape = false;

                    if(!escape){
                        alpha = 255;
                        playerAttkTxt->setString("Failed to escape");
                        playerTurn = false;
                    }
                    else{
                        Engine::GetInstance()->PopState();
                        return;
                    }
                }
                if(battleMenu->getChoice() == 1 && playerTurn){ //PLAYER PICKS ATTACK ON THEIR TURN

                    updateMenu();   //SETS BATTLEMENU TO ACTIVE
                }
            }

        if(enemyMenu->isSelected() && enemyMenu->getActive()){

            choice = enemyMenu->getChoice() - 1;
            if(choice == -1){
                enemyMenu->setActive(false);
                battleMenu->setActive(true);
            }
            else{
                playerAttacks();
                //TODO: Should go below so defence, items etc work
                playerTurn = false;
                enemyMenu->setActive(false);
                battleMenu->setActive(true);
            }

         //       playerTurn = false;
                enemyMenu->setActive(false);
                battleMenu->setActive(true);
        }
    }

    //std::cout << "THE CHOICE IS CURRENTLY: " << std::to_string(choice) << "\n";
}

void Battle::render(){

    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    StateData::GetInstance()->mainText->render();
    StateData::GetInstance()->enemyText->render();
    StateData::GetInstance()->dynamicText->render();

    if(alpha2 > 0){
        enemyAttkTxt->render();
    }
    if(alpha > 0){
        playerAttkTxt->render();
    }

    if(endTurn || battleMenu->getActive()){
        battleMenu->render();
    }
    else if(enemyMenu->getActive()){
        enemyMenu->render();
    }
}
