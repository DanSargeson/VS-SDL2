#include "RandomEncounter.h"


RandomEncounter::RandomEncounter(){

    filename = "Assets/newDialogue.txt";

    StateData::GetInstance()->enemyText->setString("");
    StateData::GetInstance()->enemyText->setPosition(GUI::p2pX(20), GUI::p2pY(50));

    StateData::GetInstance()->dynamicText->setString("");
    StateData::GetInstance()->dynamicText->setPosition(GUI::p2pX(20), GUI::p2pY(50));


    int random = rand() % 7 + 2;
    npc = std::make_shared<NPC>(random); // RED
    file = std::make_shared<LoadFiles>(filename, 0);

    int high = getData()->getActiveCharacter()->getLevel() + 8;
    int low = getData()->getActiveCharacter()->getLevel() - 1;

    int npcLevel = rand() % high + low;

    npc->createDialogueComponent();
    npc->createFactionComponent();
    npc->createAttributeComponent(npcLevel, true, true);
    npc->createSkillComponent();

    std::string msg = "You are approached by a commoner of the " + npc->getFactionStr() + " faction.\n\n\n";
    msg += "\"" + file->loadRandomDialogue() +  "\"";
    getData()->mainText->setString(msg, true, 880);
    menu = std::make_shared<GUI::Menu>();

    std::vector<std::string> ops;
    ops.push_back("Charm");
    ops.push_back("Steal");
    ops.push_back("Barter");


    menu->setMenuOptions(ops, true);

    std::cout << "NPC LEVEL: " << npcLevel << std::endl;
    std::cout << "INT: " << npc->getAttribute(4) << std::endl;

    //getData()->mainText->setString("TESTING");
}

RandomEncounter::~RandomEncounter(){

    getData()->dynamicText->clearText();
    getData()->enemyText->clearText();
    getData()->mainText->setString("Select an option: ");
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

            if(menu->getChoice() == 0){

                Engine::GetInstance()->PopState();

                return;
            }

            if(menu->getChoice() == 1){

                //Charm
                getData()->enemyText->clearText();
                if(charm()){

                    getData()->dynamicText->setString("The stranger is impressed by your wit. Faction rep gained.");
                    getData()->getActiveCharacter()->gainRep(npc->getFaction(), 1);
                }
                else{

                    getData()->dynamicText->setString("The stranger isn't fooled by false flattery. Faction rep decreased.");
                    getData()->getActiveCharacter()->loseRep(npc->getFaction(), 1);
                }

                menu->setActive(false);
            }

            if(menu->getChoice() == 2){

                //Steal
                getData()->dynamicText->clearText();
                int gold = rand() % 100 + 1;
                if(rob()){

                    std::string msg = "You succeed in robbing the stranger, gold increased by " + std::to_string(gold);
                    getData()->dynamicText->setString(msg);
                    getData()->getActiveCharacter()->setGold(gold);
                }
                else{

                    std::string msg = "";
                    if(getData()->getActiveCharacter()->getGold() - gold < 0){

                        double percentage = 0.20;
                        int check = static_cast<int>(getData()->getActiveCharacter()->getHP() * percentage);
                        getData()->getActiveCharacter()->loseHP(check);
                        msg = "You don't have enough to pay the fine. You are beaten. " + std::to_string(check) + " HP lost.";
                    }
                    else{
                        msg = "You are caught and lose " + std::to_string(gold) + " gold";
                        getData()->getActiveCharacter()->setGold(-gold);
                    }
                    getData()->enemyText->setString(msg);
                }

                menu->setActive(false);
            }

            if(menu->getChoice() == 3){

                //barter
                getData()->enemyText->clearText();
                getData()->dynamicText->setString("The stranger has no items...");
            }
        }
    }
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

    bool success = false;

    int playerTotal = getData()->getActiveCharacter()->getAttribute(5);
    int npcTotal = npc->getAttribute(4);

    int luck = rand() % getData()->getActiveCharacter()->getAttribute(6) + 1;
    playerTotal += luck;

    if(playerTotal > npcTotal){

        success = true;
    }

    return success;
}

bool RandomEncounter::rob()
{
    bool success = false;

    int playerTotal = getData()->getActiveCharacter()->getSkill(5);
    playerTotal += getData()->getActiveCharacter()->getAttribute(2);
    int npcTotal = npc->getAttribute(3);
    npcTotal += npc->getSkill(8);

    int luck = rand() % getData()->getActiveCharacter()->getAttribute(6) + 1;
    playerTotal += luck;

    if(playerTotal > npcTotal){

        success = true;
    }

    return success;
}

void RandomEncounter::barter()
{

}

