#include "RandomEncounter.h"
#include "SkillComponent.h"


RandomEncounter::RandomEncounter(int faction){

    firstEncounter = true;

    filename = "Assets/newDialogue.txt";

    getEnemyText()->setString("");

    getDynamicText()->setString("");

    choice = -1;

    int playerLvlMin = getActiveCharacter()->getLevel();

    playerLvlMin--;

    if(playerLvlMin <= 0){

        playerLvlMin = 1;
    }

    int npcLevel = getRandomValue(playerLvlMin, (getActiveCharacter()->getLevel() + 3));

    npc = std::make_shared<NPC>(faction, npcLevel);

    file = std::make_shared<LoadFiles>(filename, 0);

//    npc->createDialogueComponent();
//    npc->createFactionComponent();
//    npc->createAttributeComponent(npcLevel, true, true);
//    npc->createSkillComponent();

//    menu.reset();
    menu = std::make_shared<GUI::Menu>();


    refreshGUI();

    std::cout << "NPC LEVEL: " << npcLevel << std::endl;
    ///std::cout << "INT: " << npc->getAttribute(4) << std::endl;

    //getData()->mainText->setString("TESTING");
}

RandomEncounter::~RandomEncounter(){

    getData()->dynamicText->clearText();
    getData()->enemyText->clearText();
//    State::~State();
    State::refreshGUI();
}

void RandomEncounter::refreshGUI(){

    State::refreshGUI();

    getEnemyText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));
    getDynamicText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));

    if(firstEncounter){
    std::string msg = "You are approached by a commoner of the " + npc->getFactionStr() + " faction.\n\n\n";
    msg += "\"" + file->loadRandomDialogue() +  "\"";
    getData()->mainText->setString(msg, true, 720);

    unlockedCharm = false;

    std::vector<std::string> ops;
    ops.push_back("Chat");

    int check = npc->getFaction();
    int repCheck = getData()->getActiveCharacter()->getRep(check);
    if(getData()->getActiveCharacter()->getRep(npc->getFaction()) >= 110){

        ops.push_back("Charm");
        unlockedCharm = true;
    }


    ops.push_back("Steal");
    ops.push_back("Barter");

    menu->setMenuOptions(ops, true);


    }
    else{


    //###########################

    if(choice == 0){

                    getData()->getActiveCharacter()->gainRep(npc->getFaction(), 1);
                    std::string msg = "You have a pleasant chat with the stranger.\nFaction rep slightly increased.";
                    if(getData()->getActiveCharacter()->getRep(npc->getFaction()) == 110){

                        msg += "\n**New interaction unlocked!**";
                    }
                    getData()->dynamicText->setString(msg);

                menu->setActive(false);
            }

            if(choice == 1){

            //Charm
                if(unlockedCharm){
                    getData()->enemyText->clearText();
                    if(charm()){

                        getData()->dynamicText->setString("The stranger is impressed by your wit. Faction rep gained.");
                        getData()->getActiveCharacter()->gainRep(npc->getFaction(), 5);

                        menu->setActive(false);
                    }
                    else{

                        std::string msg = "The stranger isn't fooled by false flattery.";

                        if(getData()->getActiveCharacter()->getRep(npc->getFaction()) >= 112){

                            msg += "\nFaction rep decreased slightly.";
                            getData()->getActiveCharacter()->loseRep(npc->getFaction(), 1);
                        }

                        getData()->enemyText->setString(msg);
                        menu->setActive(false);
                    }
                }
                else{

                    attemptSteal();
                    menu->setActive(false);
                }

                menu->setActive(false);
            }

            if(choice == 2){

                if(unlockedCharm){

                    attemptSteal();
                    menu->setActive(false);
                }
                else{

                    //barter
                    getData()->enemyText->clearText();
                    getData()->dynamicText->setString("The stranger has no items...");
                    menu->setActive(false);
                }

            }
            if(choice == 3){

                if(unlockedCharm){

                    //barter
                    getData()->enemyText->clearText();
                    getData()->dynamicText->setString("The stranger has no items...");
                }
                else{

                    return;
                }

            }
        }
}


void RandomEncounter::update(const float& dt)
{

}

void RandomEncounter::updateEvents(SDL_Event& e){

    menu->update();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        if(!menu->getActive()){

            Engine::GetInstance()->PopState();
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){

        std::string ss = getData()->getActiveCharacter()->printPlayerDetails();
        std::cout << ss << std::endl;
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){
        if(menu->isSelected()){

//            if(menu->getChoice() == 0){
//
//                Engine::GetInstance()->PopState();
//
//                return;
//            }
            choice = menu->getChoice();
            if(menu->getChoice() == 0){


                    getData()->getActiveCharacter()->gainRep(npc->getFaction(), 1);
                    std::string msg = "You have a pleasant chat with the stranger.\nFaction rep slightly increased.";
                    if(getData()->getActiveCharacter()->getRep(npc->getFaction()) == 110){

                        msg += "\n**New interaction unlocked!**";
                    }
                    getData()->dynamicText->setString(msg, true);

                menu->setActive(false);
            }

            if(menu->getChoice() == 1){

            //Charm
                if(unlockedCharm){
                    getData()->enemyText->clearText();
                    if(charm()){

                        int rando = getRandomValue(1, 5);
                        int totalXP = rando * (getActiveCharacter()->getAttribute(5) + getActiveCharacter()->getAttribute(6)); // 5 == CHARISMA, 6 == LUCK
                        std::string msg = "The stranger is impressed by your wit. Faction rep gained.\n" + std::to_string(totalXP) + " EXP gained.";
                        getData()->dynamicText->setString(msg, true, 680);
                        getData()->getActiveCharacter()->gainRep(npc->getFaction(), 5);
                        getData()->getActiveCharacter()->gainXP(totalXP);
                        //getData()->getActiveCharacter()->increaseSkill(7); //7 == SKILLS::PERSUASION

                        menu->setActive(false);
                    }
                    else{

                        std::string msg = "The stranger isn't fooled by false flattery.";

                        if(getData()->getActiveCharacter()->getRep(npc->getFaction()) >= 112){

                            msg += "\nFaction rep decreased slightly.";
                            getData()->getActiveCharacter()->loseRep(npc->getFaction(), 1);
                        }

                        getData()->dynamicText->setString(msg, true);
                        menu->setActive(false);
                    }
                }
                else{

                    attemptSteal();
                    menu->setActive(false);
                }

                menu->setActive(false);
            }

            if(menu->getChoice() == 2){

                if(unlockedCharm){

                    attemptSteal();
                    menu->setActive(false);
                }
                else{

                    //barter
                    getData()->enemyText->clearText();
                    getData()->dynamicText->setString("The stranger has no items...");
                    menu->setActive(false);
                }

            }
            if(menu->getChoice() == 3){

                if(unlockedCharm){

                    //barter
                    getData()->enemyText->clearText();
                    getData()->dynamicText->setString("The stranger has no items...");
                }
                else{

                    return;
                }

            }
        }
    }

    State::updateEvents(e);
}

void RandomEncounter::render(){

    menu->render();
    getData()->mainText->render();

    if(getData()->dynamicText->getString() != ""){

        getData()->dynamicText->render();
    }
    if(getData()->enemyText->getString() != ""){

        getData()->enemyText->render();
    }
}

bool RandomEncounter::charm(){

///bool success = false;

//    int playerTotal = getData()->getActiveCharacter()->getAttribute(5);
//    int npcTotal = npc->getAttribute(4);
//
//    int luck = rand() % getData()->getActiveCharacter()->getAttribute(6) + 1;
//    playerTotal += luck;

    int playerPersuasion = getActiveCharacter()->getSkill(SKILLS::PERSUASION);    ///7 == PERSUASION
    int npcPerception = npc->getSkill(SKILLS::PERCEPTION);   /// 8 == PERCEPTION

    bool success = getActiveCharacter()->skillCheck(npc, playerPersuasion, npcPerception);

//    if(playerTotal > npcTotal){
//
//        success = true;
//    }

    return success;
}

bool RandomEncounter::rob()
{
   // bool success = false;

//    int playerTotal = getData()->getActiveCharacter()->getSkill(5);
//    playerTotal += getData()->getActiveCharacter()->getAttribute(2);
//    int npcTotal = npc->getAttribute(3);
//    npcTotal += npc->getSkill(8);

    int stealth = getActiveCharacter()->getSkill(SKILLS::STEALTH);
    int npcPerception = npc->getSkill(SKILLS::PERCEPTION);

   bool success = getActiveCharacter()->skillCheck(npc, stealth, npcPerception);

//    int luck = rand() % getData()->getActiveCharacter()->getAttribute(6) + 1;
//    playerTotal += luck;
//
//    if(playerTotal > npcTotal){
//
//        success = true;
//    }

    return success;
}

void RandomEncounter::attemptSteal(){

 //Steal HERE
                getData()->dynamicText->clearText();
                int gold = getRandomValue(1, (1+(npc->getLevel()*2)));
                if(rob()){

                    std::string msg = "You succeed in robbing the stranger, gold increased by " + std::to_string(gold);
                    getData()->dynamicText->setString(msg);
                    getData()->getActiveCharacter()->gainGold(gold);
                }
                else{

                    std::string msg = "";
                    if((getData()->getActiveCharacter()->getGold() - gold) < 0){

                        double percentage = 0.20;
                        getData()->getActiveCharacter()->setGold(0);
                        double check = static_cast<int>(getData()->getActiveCharacter()->getHP() * percentage);
                        if(check < 1){

                            check = 1;
                        }
                        getData()->getActiveCharacter()->loseHP(check);
                        if(getData()->getActiveCharacter()->getHP() <= 0){

                            msg = "You don't have enough to pay the fine.\nYou lose what you have and are beaten to within an inch of your life.";
                            getData()->getActiveCharacter()->setHP(1);
                        }
                        else{
                            msg = "You don't have enough to pay the fine.\nYou lose what you have and are beaten. " + std::to_string(static_cast<int>(check)) + " HP lost.";
                        }

                        msg += "\n" + npc->getFactionStr() + " faction rep down";
                        getData()->getActiveCharacter()->loseRep(npc->getFaction(), 5);
                    }
                    else{
                        msg = "You are caught and lose " + std::to_string(gold) + " gold";
                        getData()->getActiveCharacter()->gainGold(-gold);
                        msg += "\n\n" + npc->getFactionStr() + " faction rep down";
                        getData()->getActiveCharacter()->loseRep(npc->getFaction(), 5);
                    }
                    getData()->enemyText->setString(msg, true, 880);
                }

}

void RandomEncounter::barter()
{

}

