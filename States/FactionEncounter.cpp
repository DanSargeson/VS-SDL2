#include "FactionEncounter.h"
#include "LoadFiles.h"

int FactionEncounter::position = 1;

FactionEncounter::FactionEncounter(){


    StateData::GetInstance()->enemyText->setString("");
    StateData::GetInstance()->enemyText->setPosition(GUI::p2pX(20), GUI::p2pY(50));

    StateData::GetInstance()->dynamicText->setString("");
    StateData::GetInstance()->dynamicText->setPosition(GUI::p2pX(20), GUI::p2pY(50));

    m_fileName = "Assets/factionQuests.txt";

    ///"Assets/newDialogue.txt"

    json_file = "Assets/diag.json";


    int random = rand() % 6 + 2;
    npc = std::make_shared<NPC>(random); // RED
    file = std::make_shared<LoadFiles>(m_fileName, 1);


    npc->createDialogueComponent();
    npc->createFactionComponent();
    ///npc->setCharacterName(npc->getName());
    ///npc->setDialogueText(file->loadDialogue());

    ///file->loadFactionDialogue(npc->getFaction());
    file->readJsonFile2(json_file);
   // std::pair msg1 = file->getDialogueAndResponses(npc->getFactionStr(), 1, 0);
   std::string check = npc->getFactionStr();
    StateData::GetInstance()->mainText->setString(file->getDialogue(check, 1));
    m_menu = std::make_shared<GUI::Menu>();

    m_menu->setMenuOptions(file->getFirstResponses(check, 1), true);

}

FactionEncounter::~FactionEncounter(){

    StateData::GetInstance()->mainText->setString("Select an option: ");

}

void FactionEncounter::update(const float& dt){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        StateData::GetInstance()->enemyText->clearText();
        StateData::GetInstance()->dynamicText->clearText();

        if(!m_menu->getActive()){

            Engine::GetInstance()->PopState();
        }

        return;
    }
}

void FactionEncounter::updateEvents(SDL_Event& e)
{

    m_menu->update();

    if(e.type == SDL_MOUSEBUTTONDOWN){


        if(m_menu->isSelected()){

            if(m_menu->getChoice() == 0){
                Engine::GetInstance()->PopState();
            }
            else{

                file->selectResponse(npc->getFactionStr(), 1, m_menu->getChoice());
                std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
                StateData::GetInstance()->mainText->setString(msg2);
                m_menu->setMenuOptions(file->getPlayerOps(), true);
            }
        }
    }
}

void FactionEncounter::render()
{
    StateData::GetInstance()->mainText->render();
    if(StateData::GetInstance()->enemyText->getString() != ""){

        StateData::GetInstance()->enemyText->render();
    }
    if(StateData::GetInstance()->dynamicText->getString() != ""){

        StateData::GetInstance()->dynamicText->render();
    }
    m_menu->render();
}

