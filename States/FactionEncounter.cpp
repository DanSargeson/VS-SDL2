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


    int random = rand() % 7 + 1;
    npc = std::make_shared<NPC>(random); // RED
    file = std::make_shared<LoadFiles>(m_fileName, 1);


    npc->createDialogueComponent();
    npc->createFactionComponent();
    ///npc->setCharacterName(npc->getName());
    ///npc->setDialogueText(file->loadDialogue());

    ///file->loadFactionDialogue(npc->getFaction());
    file->readJsonFile2(json_file);
   // std::pair msg1 = file->getDialogueAndResponses(npc->getFactionStr(), 1, 0);
    StateData::GetInstance()->mainText->setString(file->getDialogue("red", 1));
    m_menu = std::make_shared<GUI::Menu>();

    m_menu->setMenuOptions(file->getFirstResponses("red", 1), true);

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

//            npc->getFaction();
///            std::string msg = "Gained favour with " + npc->getFactionName(npc->getFaction()) + " faction";
///            StateData::GetInstance()->dynamicText->setString(msg);
///
///            StateData::GetInstance()->getActiveCharacter()->gainRep(npc->getFaction(), 1);
///           m_menu->setActive(false);
              file->selectResponse("red", 1, m_menu->getChoice());
              std::string msg2 = file->getDialogue("red", file->getCurrDiagID());
              StateData::GetInstance()->mainText->setString(msg2);
              m_menu->setMenuOptions(file->getPlayerOps(), true);

//              if(file->getCurrDiagID() == 0){
//
//                getData()->mainText->setString("Goodbye");
//                Engine::GetInstance()->PopState();
//              }
        }
//        else if(m_menu->getChoice() == 2){
//
//            std::string msg = "Lost favour with " + npc->getFactionName(npc->getFaction()) + " faction";
//            StateData::GetInstance()->enemyText->setString(msg);
//            StateData::GetInstance()->getActiveCharacter()->loseRep(npc->getFaction(), 1);
//            m_menu->setActive(false);
//        }
//        else{
//
//            file->loadFactionDialogue(2);
//            StateData::GetInstance()->mainText->setString(file->loadQuestDialogue(1));
//            m_menu = std::make_shared<GUI::Menu>();
//            m_menu->setMenuOptions(file->loadPlayerOptions(), true);
//        }
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

