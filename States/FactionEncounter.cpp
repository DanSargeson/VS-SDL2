#include "FactionEncounter.h"
#include "LoadFiles.h"

int FactionEncounter::position = 1;

FactionEncounter::FactionEncounter(int faction){

    firstEncounter = true;


    getEnemyText()->setString("");

    getDynamicText()->setString("");

    m_fileName = "Assets/factionQuests.txt";

    ///"Assets/newDialogue.txt"

    json_file = "Assets/diag.json";

    npc = std::make_shared<NPC>(faction); // RED
    file = std::make_shared<LoadFiles>(m_fileName, 1);

    npc->createDialogueComponent();
    npc->createFactionComponent();
    file->readJsonFile2(json_file);
   // std::pair msg1 = file->getDialogueAndResponses(npc->getFactionStr(), 1, 0);
   std::string check = npc->getFactionStr();
    getMainText()->setString(file->getDialogue(check, 1));
    menu = std::make_shared<GUI::Menu>();

    menu->setMenuOptions(file->getFirstResponses(check, 1), true);

}

FactionEncounter::~FactionEncounter(){

    //getMainText()->setString("Select an option: ");
    npc.reset();
    //State::~State();
}

void FactionEncounter::update(const float& dt){

}

void FactionEncounter::updateEvents(SDL_Event& e)
{

    menu->update();

    if(e.type == SDL_MOUSEBUTTONDOWN){


        if(menu->isSelected()){

//            if(menu->getChoice() == 0){
//                Engine::GetInstance()->PopState();
//            }
           // else{

                firstEncounter = false;

                file->selectResponse(npc->getFactionStr(), 1, (menu->getChoice() + 1));
                std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
                getMainText()->setString(msg2);
                menu->setMenuOptions(file->getPlayerOps(), true);
 //           }
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        getEnemyText()->clearText();
        getDynamicText()->clearText();

        if(!menu->getActive()){

            Engine::GetInstance()->PopState();
        }

        return;
    }

    State::updateEvents(e);
}

void FactionEncounter::refreshGUI(){

    State::refreshGUI();

    if(firstEncounter){

    std::string check = npc->getFactionStr();
    getMainText()->setString(file->getDialogue(check, 1));
    menu->setMenuOptions(file->getFirstResponses(check, 1), true);
    }
    else{

        std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
        getMainText()->setString(msg2);
        menu->setMenuOptions(file->getPlayerOps(), true);
    }
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
    menu->render();
}

