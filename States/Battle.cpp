#include "Battle.h"
#include "Engine.h"
#include "Input.h"
#include "PlayerDeath.h"
#include "SkillComponent.h"

Battle::Battle() : State(), missCounter(0), enemyMissCounter(0), alpha(255), alpha2(255), battleTxtTimer(std::make_unique<Timer>()), battleGameTimer(std::make_unique<GameTimer>())/*, seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())), generator(seed)*/, noOfEnemies(0) {




//     std::uniform_int_distribution<int> numEnemiesDistribution(1, 3);
//     noOfEnemies = numEnemiesDistribution(generator);

    textThreadRunning = false;
    winThreadRunning = false;

    std::random_device rd;


    std::mt19937 gen(rd());

                // Use std::uniform_int_distribution to generate random indices

                int maxi = 1 + getData()->getActiveCharacter()->getLevel();
                if(maxi > 3){

                    maxi = 3;
                }
    std::uniform_int_distribution<> dis(1, maxi);

    noOfEnemies = dis(gen);
    int playerLvl = getData()->getActiveCharacter()->getLevel();
    if(playerLvl <= 5){

        noOfEnemies = 2;
        if(playerLvl <= 3){

            noOfEnemies = 1;
        }
    }


     playerWins = false;
     totalEXP = 0;
     totalGold = 0;

     player = StateData::GetInstance()->getActiveCharacter();

//    std::vector<std::string> ops;
    ops.clear();
    ops.push_back("Attack");
    ops.push_back("Defend");
    ops.push_back("Use Item");
    //menu.reset();
    //menu = std::make_shared<GUI::Menu>();
    menu->setMenuOptions(ops, true);

    enemyMenu.reset();
    enemyMenu = std::make_shared<GUI::Menu>();

    enemyMenu->setActive(false);

   // getMainText() = std::make_shared<GUI::Text>(5, 10, 12, 8, true);
    //getMainText()->setString("Test");
    //getDynamicText()->setString("You are attacked: ");

    getEnemyText()->setString("");
    getEnemyText()->setColour(255, 0, 0, 0);

    playerAttkTxt = std::make_unique<GUI::Text>(true);
    playerAttkTxt->setColour(0, 0, 255, 0);
    playerAttkTxt->setPosition(GUI::p2pX(15.f), GUI::p2pY(55.f));
    playerAttkTxt->clearText();

    enemyAttkTxt = std::make_unique<GUI::Text>(true);
    enemyAttkTxt->setColour(255, 0, 0, 0);
    enemyAttkTxt->setPosition(GUI::p2pX(60.f), GUI::p2pY(50.f));
    enemyAttkTxt->clearText();

    battleCloseMsg = std::make_unique<GUI::textBox>();
    battleCloseMsg->setSize(60, 40);
    battleCloseMsg->centreTextBox();
    battleCloseMsg->setActive(false);

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
		int high = getData()->getActiveCharacter()->getLevel() + 1;

		int rando = 0;
		std::uniform_int_distribution<>randEnemies(low, high);
		rando = randEnemies(gen);
		if(low <= 1){

            rando = 1;
		}

		//rando = rand() % high + low;
		std::shared_ptr<Enemy> temp = std::make_shared<Enemy>(rando);
		enemies.push_back(temp);
		enemyText.push_back(std::make_shared<GUI::Text>());

		for(int i = 0; i < enemies.size(); i++){

            enemyText[i]->setColour(255, 0, 0, 0);
		}
        SDL_Delay(19);
	}

	for(size_t i = 0; i < enemies.size(); i++){

        enemies[i]->calculateSkills();
        std::string msg = enemies[i]->getName() + " HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax());
        enemyText[i]->setString(msg);
        enemyText[i]->setColour(255, 0, 0, 0);
		enemyText[i]->setPosition(GUI::p2pX(60), GUI::p2pY(15 + (i*5)));
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

//    menu.reset();
//    enemyMenu.reset();

//    enemyAttkTxt.reset();
//    playerAttkTxt.reset();

    //getMainText()->clearText();
    //getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
    //getEnemyText()->clearText();
    //getDynamicText()->clearText();
    enemies.clear();

    if(textThread.joinable()){

        textThread.join();
        textThread.~thread();
    }

    if(winThread.joinable()){

        winThread.join();
        winThread.~thread();
    }

  getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
    getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));
}

void Battle::refreshGUI(){

    State::refreshGUI();

    for(size_t i = 0; i < enemies.size(); i++){

        std::string msg = enemies[i]->getName() + " HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax());
        enemyText[i]->setString(msg);
     //   enemyText[i]->setColour(255, 0, 0, 0);
		enemyText[i]->setPosition(GUI::p2pX(60), GUI::p2pY(15 + (i*5)));
	}

    enemyAttkTxt->refreshGUI();
    playerAttkTxt->refreshGUI();

    playerAttkTxt->setPosition(GUI::p2pX(15.f), GUI::p2pY(55.f));
    enemyAttkTxt->setPosition(GUI::p2pX(60.f), GUI::p2pY(50.f));


    battleCloseMsg->setSize(60, 40);
    battleCloseMsg->centreTextBox();
    //menu->setPosition();
}


void Battle::initBattle(){

winAlpha = 0;
endGameTimer = std::make_unique<GameTimer>();
endGameTimer->start();
battleGameTimer->start();

if(!escape && !playerDefeated && !enemyDefeated) {

		if (playerTurn && !playerDefeated) {
            //TODO:: HERE IS WHERE TO CHANGE THINGS FOR BATTLEMODE
            std::vector<std::string> ops;
            ops.push_back("Attack");
            ops.push_back("Defend");
            ops.push_back("Use Item");
            menu->setMenuOptions(ops, true);
            std::string msg = "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            std::string enemyMsg = "";
            if(menu->getActive()){

//                for(int i = 0; i < enemies.size(); i++){
//
//                    enemyMsg += enemies[i]->getName() + ": " + "HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax()) + " ";
//                }
//                getEnemyText()->setString(enemyMsg);
            }
			}
        }

        else{

            enemyAttacks();
        }
}


void Battle::updateMenu(){


    //getDynamicText()->setString("Which enemy to attack?: ");
    std::vector<std::string> enemyMenuStr;

    for(int i = 0; i < enemies.size(); i++){

        enemyMenuStr.push_back(enemies[i]->getName());
    }

    enemyMenu->setMenuOptions(enemyMenuStr, true);
    enemyMenu->setActive(true);
    menu->setActive(false);
}

void Battle::update(const float& dt){

if(endTurn){

//    if(playerWins){
//
//        updateText();
//    }

    menu->setActive(false);
    return;
}

battleTxtTimer->Tick();

if(playerDefeated){

    getMainText()->setColour(255, 0, 0, 0);
    getMainText()->setString("You Died!");

    playerTurn = false;
    endTurn = true;

    textThreadRunning = false;
    if(textThread.joinable()){

        textThread.join();
    }

    if(winThread.joinable()){

        winThread.join();
    }

//    ~Battle();
    Engine::GetInstance()->PopState();
    Engine::GetInstance()->AddState(std::make_shared<PlayerDeath>());

    return;
}

if(playerWins){

    if(winThread.joinable()){

        if(winAlpha >= 255){

            winThread.join();
        }
        return;
    }
}


            std::string msg = "You are attacked.\n\n";
            msg += "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            getMainText()->setString(msg, true);
            getMainText()->render();
            std::string enemyMsg = "";

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
                SDL_Delay(10);
                    enemyAttacks();
                   /// battleGameTimer->stop();
                //}
        }
	}

	if(alpha2 <=5 || alpha <=5){
        textThreadRunning = false;      ///HREE YOU COMMENTED
        if(textThread.joinable()){
            textThread.join();
        }
	}
}

void Battle::startTextThread(){

    textThreadRunning = true;
    textThread = std::thread(&Battle::updateText, this);
}

void Battle::startWinThread(){

    winThreadRunning = true;
    winThread = std::thread(&Battle::updateWinText, this);
}

void Battle::updateWinText(){

    while(winThreadRunning){

    if(playerWins){

        if(endGameTimer != nullptr && endGameTimer->getTicks() > 5){

            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            winAlpha+= 7;
            if(winAlpha > 255){

                winAlpha = 255;
                winThreadRunning = false;
            }

            battleCloseMsg->setAlpha(winAlpha);
            SDL_SetTextureAlphaMod(this->battleCloseMsg->getTexture(), winAlpha);
            SDL_SetTextureAlphaMod(this->battleCloseMsg->getHeaderTexture(), winAlpha);

            endGameTimer->restart();
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Battle::updateText(){


    while(textThreadRunning){

    if(playerAttkTxt && playerTurn){

        if(alpha >= 0){

            alpha -= 5;
            SDL_SetTextureAlphaMod(playerAttkTxt->getTexture(), alpha);
     ///       battleTxtTimer->Restart();
        }
        else{

            //alpha = 255;
            textThreadRunning = false;
        }
    }


    if(enemyAttkTxt){

        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
        if(alpha2 >= 0){

            alpha2 -= 5;
            SDL_SetTextureAlphaMod(enemyAttkTxt->getTexture(), alpha2);
        }
        else{

///            enemyAttkTxt->clearText();
        //    alpha2 = 255;
            textThreadRunning = false;
        }
    }
     std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}


const void Battle::playerAttacks(){

            alpha = 255;
///            enemyTotal = enemies[choice]->getSkill(2); /// / (double)combatTotal * 100;;

            playerAccuracy = StateData::GetInstance()->getActiveCharacter()->getSkill(SKILLS::ACCURACY); //3 == ACCURACY
            enemyTotal = enemies[choice]->getSkill(SKILLS::DODGE); // 2 == DEFENCE

//            seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
//             generator.seed(seed);
//             std::uniform_int_distribution<int> playerTotalDistribution(1, playerTotal);
//             combatRollPlayer = playerTotalDistribution(generator);
//
//             std::uniform_int_distribution<int> enemyTotalDistribution(1, enemyTotal);
//             combatRollEnemy = enemyTotalDistribution(generator);


				if (getActiveCharacter()->skillCheck(enemies[choice], playerAccuracy, enemyTotal) || missCounter >= 3) { //###########PLAYER HITS
					//HIT
					missCounter = 0;
					damage = StateData::GetInstance()->getActiveCharacter()->getDamage();
					defendRoll = enemies[choice]->getDefence();
                    int tot = 0;
                    if(damage >= defendRoll){

                        tot = damage - defendRoll;
                    }else{

                        tot = damage * 0.10;
                     }

                     if(tot <= 0){

                        tot = 1;
                     }
					enemies[choice]->loseHP(abs(tot));
					if(tot <= 0){
                        tot = 1;
					}
					std::string dmgMsg = "HIT for " + std::to_string(abs(tot)) + " damage!";

					std::string msg = enemies[choice]->getName() + " HP: " + std::to_string(enemies[choice]->getHP()) + "/" + std::to_string(enemies[choice]->getHPMax());
                    enemyText[choice]->setString(msg);
					playerAttkTxt->setString(dmgMsg);
					//alpha = 255;

					//#####PLAYER WINS
					if (!enemies[choice]->isAlive()) {
						battleCloseMsg->setHeader("YOU DEFEATED!");
						gainGold = rand() & enemies[choice]->getLevel() * 10 + 1;
						totalGold += gainGold;
						StateData::GetInstance()->getActiveCharacter()->gainGold(gainGold);
						gainEXP = enemies[choice]->getExp();
						totalEXP += gainEXP;
						StateData::GetInstance()->getActiveCharacter()->gainXP(gainEXP); //DEBUG REMOVE


                        endMsg += "Gold Gained: " + std::to_string(gainGold) + "\n";
                        endMsg += "EXP Gained: " + std::to_string(gainEXP) + "\n";

                        if(getData()->getActiveCharacter()->getExp() >= getData()->getActiveCharacter()->getExpNext()){

                            getData()->getActiveCharacter()->levelUp();
                            endMsg += "\nLevelled up!!\n";
						}

                        gainEXP = 0;
                        gainGold = 0;
						if(enemies.size() == 1){

                            endMsg += "\n\nTotal EXP Gained: " + std::to_string(totalEXP);
                            endMsg += "\nTotal Gold Gained: " + std::to_string(totalGold);

                            playerWins = true;
                            winAlpha = 0;
                            if(textThread.joinable()){

                                textThread.join();
                            }
                            startWinThread();
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
                        ///getDynamicText()->setString(endMsg, true, GUI::p2pY(80));
                        battleCloseMsg->setText(endMsg);
						enemies.erase(enemies.begin() + choice);
						enemyText.erase(enemyText.begin() + choice);
//						int s = enemies.size();
//						std::cout << std::endl << std::to_string(s);
						for(size_t i = 0; i < enemies.size(); i++){

                            std::string msg = enemies[i]->getName() + " HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax());
                            enemyText[i]->setString(msg);
                            //enemyText[i]->setString(enemies[i]->getName());
                            enemyText[i]->setColour(255, 0, 0, 0);
                            enemyText[i]->setPosition(GUI::p2pX(60), GUI::p2pY(15 + (i*5)));
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
        textThreadRunning = false;
        return;
    }

    if(!playerTurn && !escape && !enemyDefeated){
			//ENEMY TURN
			for (size_t i = 0; i < enemies.size(); i++){    //TIMER NEEDS TO GO AROUND HERE....
				//combatTotal = enemies[i]->getAccuracy() + StateData::GetInstance()->getActiveCharacter()->getDefence();
				//enemyTotal = enemies[i]->getAccuracy() / (double)combatTotal * 100;
				//playerTotal = StateData::GetInstance()->getActiveCharacter()->getDefence() / (double)combatTotal * 100;

				enemyTotal = enemies[i]->getSkill(0); //0 == MELEE
                combatTotal = StateData::GetInstance()->getActiveCharacter()->getSkill(SKILLS::DODGE); // 2 == DEFENCE

				seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
             generator.seed(seed);
             std::uniform_int_distribution<int> playerTotalDistribution(1, playerTotal);
             combatRollPlayer = playerTotalDistribution(generator);

             std::uniform_int_distribution<int> enemyTotalDistribution(1, enemyTotal);
             combatRollEnemy = enemyTotalDistribution(generator);

				if (enemies[i]->skillCheck(getActiveCharacter(), enemyTotal, combatTotal) || enemyMissCounter >= 3) {
					//HIT
					///int chancetoSave = getRandomValue(0, getActiveCharacter()->getAttribute(6)); //PLAYERS LUCK == 6

					///if(chancetoSave > 0){

                        //MISS
///					enemyMsg += "\n" + enemies[i]->getName() + " Missed! ";
///					alpha2 = 255;
///					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
///					cout << "ENEMY MISSED!\n\n";
///					enemyMissCounter++;

					///}
					///else{
                    enemyMissCounter = 0;
					damage = enemies[i]->getDamage();
					int defendRoll = getActiveCharacter()->getDefence();
                    int tot = 0;
                    if(damage >= defendRoll){

                        tot = damage - defendRoll;
                    }else{

                        tot = damage * 0.10;
                     }

                     if(tot <= 0){

                        tot = 1;
                     }
					StateData::GetInstance()->getActiveCharacter()->loseHP(tot);
					enemyMsg += "\n" + enemies[i]->getName() + " HIT for " + std::to_string(tot) + " damage! ";
					alpha2 = 255;
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					if (!StateData::GetInstance()->getActiveCharacter()->isAlive()) {
						cout << "YOU DIED!\n\n";
						playerDefeated = true;
						break;
					}
					///}
				}
				else {
					//MISS
					enemyMsg += "\n" + enemies[i]->getName() + " Missed! ";
					alpha2 = 255;
					enemyAttkTxt->setString(enemyMsg, true, GUI::p2pX(80));
					cout << "ENEMY MISSED!\n\n";
					enemyMissCounter++;
				}
			}

            std::string msg = "You are attacked.\n\n";
            msg += "HP: " + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHP()) + "/" + std::to_string(StateData::GetInstance()->getActiveCharacter()->getHPMax());
            getMainText()->setString(msg, true);
			//END TURN
			 endTurn = true;
		}
}

void Battle::updateEvents(SDL_Event& e){

    menu->update(e);
    enemyMenu->update(e);

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){
        runMenuSelection();
        if(endTurn){

                endTurn = false;
                playerTurn = true;
                menu->setActive(true);
            if(!textThreadRunning){

                    if(!winThreadRunning && !playerWins && !escape && !textThreadRunning){

                        startTextThread();
                        return;
                    }
                    else if(!winThreadRunning){

                            if(playerWins || escape){

                                Engine::GetInstance()->PopState();
                                return;
                            }
                    }
                //getDynamicText()->setString("Choose action: ");
            }
        }
    }

    /** THIS IS THE RUN AWAY FROM BATTLE CODE         */

                if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE) && playerTurn){


                    int coinToss = rand() % 2 + 1;
                        if (coinToss == 2){
                            //getDynamicText()->setString("Ran away!!");
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

////                        if(textThread.joinable()){
////
////                            textThread.join();
////                        }
////                        if(winThread.joinable()){
////
////                            winThread.join();
////                        }

                        alpha = 255;
                        getDynamicText()->setString("Got away safely");
                        ///getDynamicText()->render();
                        //SDL_Delay(100);
                        Engine::GetInstance()->PopState();
                        return;
                    }

                }


                /*  END OF RUNNING FROM BATTLE  */

    if(e.type == SDL_MOUSEBUTTONDOWN){

        runMenuSelection();
    }



    //std::cout << "THE CHOICE IS CURRENTLY: " << std::to_string(choice) << "\n";
    if(e.type == SDL_MOUSEMOTION){

//        int x, y;
//        SDL_GetMouseState(&x, &y);
//        SDL_Rect r;

        for(int i = 0; i < enemies.size(); i++){


       /// r = enemyText[i]->getPositionRect();

        if(battleEyes->checkBounds(enemyText[i])){

                std::string msg = "HP: " + std::to_string(enemies[i]->getHP()) + "/" + std::to_string(enemies[i]->getHPMax())
                    + "\nAttack: ????\nDefence: ????";
                msg += "\nSkills: \nDefence Sk: " + std::to_string(enemies[i]->getSkill(2));
                msg += "\nMelee Sk: " + std::to_string(enemies[i]->getSkill(0));
                battleEyes->setDisplayText(msg);
                battleEyes->update();
                battleEyes->setHidden(false);

                return;
           }
           else{

                battleEyes->setHidden(true);
           }
        }
    }
}

void Battle::runMenuSelection(){

            if(menu->isSelected() && playerTurn){


        ///RUN MENU OPTIONS START
        int choice = menu->getChoice();

        if(menu->getChoice() == 0){

            std::vector<std::string> ops;

            for(int i = 0; i < enemies.size(); i++){

                ops.push_back(enemies[i]->getName());
            }

            enemyMenu->setMenuOptions(ops, true);
            enemyMenu->setActive(true);
            menu->setActive(false);

            }

            ///
        }

        if(enemyMenu->isSelected() && playerTurn){

            playerTurn = false;
            enemyMenu->setActive(false);
            choice = enemyMenu->getChoice();
            ///THIS GOES IN THE SELECTED ENEMY
            playerAttacks();
            //TODO: Should go below so defence, items etc work
            menu->setActive(true);
        }
            ///END RUN MENU s
}

void Battle::render(){


    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    getMainText()->render();
    getEnemyText()->render();


    if(playerWins){

        if(!battleCloseMsg->getActive()){
            //SDL_Delay(600);
            endGameTimer->restart();
            battleCloseMsg->setAlpha(winAlpha);
            SDL_SetTextureAlphaMod(battleCloseMsg->getTexture(), winAlpha);
            SDL_SetTextureAlphaMod(battleCloseMsg->getHeaderTexture(), winAlpha);
            battleCloseMsg->setActive(true);
        }

        int w, h;
        SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, &h);
//        SDL_Rect overlay = { 0, 0, w, h };
//        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
//        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 211, 211, 211, winAlpha);
//        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &overlay);
//        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);
        battleCloseMsg->render();

        if(winAlpha != 255){

            endTurn = false;
        }
        else{

            endTurn = true;

        }
        endGameTimer->restart();
        return;
    }

    if(alpha2 > 10){
        SDL_SetTextureAlphaMod(enemyAttkTxt->getTexture(), alpha);
        enemyAttkTxt->render();
    }
    if(alpha > 10){

        SDL_SetTextureAlphaMod(playerAttkTxt->getTexture(), alpha);
        playerAttkTxt->render();
    }

    if(endTurn || menu->getActive()){
        menu->render();
    }
    else if(enemyMenu->getActive()){
        enemyMenu->render();
    }

    for(int i = 0; i < enemyText.size(); i++){

        enemyText[i]->render();
    }

    battleEyes->render();
}
