#include "FactionEncounter.h"
#include "LoadFiles.h"

int FactionEncounter::position = 1;

FactionEncounter::FactionEncounter(int faction){


    getEnemyText()->setString("");
    getEnemyText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));

    getDynamicText()->setString("");
    getDynamicText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));

    m_fileName = "Assets/factionQuests.txt";

    ///"Assets/newDialogue.txt"

    json_file = "Assets/diag.json";

    npc = std::make_shared<NPC>(faction); // RED
    file = std::make_shared<LoadFiles>(m_fileName, 1);

    npc->createDialogueComponent();
    npc->createFactionComponent();
    ///npc->setCharacterName(npc->getName());
    ///npc->setDialogueText(file->loadDialogue());

    ///file->loadFactionDialogue(npc->getFaction());
    file->readJsonFile2(json_file);
   // std::pair msg1 = file->getDialogueAndResponses(npc->getFactionStr(), 1, 0);
   std::string check = npc->getFactionStr();
    getMainText()->setString(file->getDialogue(check, 1));
    m_menu = std::make_shared<GUI::Menu>();

    m_menu->setMenuOptions(file->getFirstResponses(check, 1), true);

}

FactionEncounter::~FactionEncounter(){

    //getMainText()->setString("Select an option: ");
    npc.reset();
    State::~State();
}

void FactionEncounter::update(const float& dt){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        getEnemyText()->clearText();
        getDynamicText()->clearText();

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

//            if(m_menu->getChoice() == 0){
//                Engine::GetInstance()->PopState();
//            }
           // else{

                file->selectResponse(npc->getFactionStr(), 1, (m_menu->getChoice() + 1));
                std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
                getMainText()->setString(msg2);
                m_menu->setMenuOptions(file->getPlayerOps(), true);
 //           }
        }
    }

    State::updateEvents(e);
}

void FactionEncounter::render()
{
    getMainText()->render();
    if(getEnemyText()->getString() != ""){

        getEnemyText()->render();
    }
    if(getDynamicText()->getString() != ""){

        getDynamicText()->render();
    }
    m_menu->render();
}

