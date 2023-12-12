#include "FactionEncounter.h"
#include "LoadFiles.h"

int FactionEncounter::position = 1;

FactionEncounter::FactionEncounter(int type){


    if(type <= 3){

        m_fileName = "Assets/newDialogue.txt";
    }
    else{

        m_fileName = "Assets/factionQuests.txt";
    }

    ///"Assets/newDialogue.txt"

    file = std::make_shared<LoadFiles>(m_fileName, type);

    int random = rand() % 7 + 1;
    npc = std::make_shared<NPC>(random); // RED


    npc->createDialogueComponent();
    npc->createFactionComponent();
    ///npc->setCharacterName(npc->getName());
    ///npc->setDialogueText(file->loadDialogue());

    if(type <= 3){
        StateData::GetInstance()->mainText->setString(file->loadRandomDialogue());
        m_menu = std::make_shared<GUI::Menu>();
    }
    else{
        file->loadFactionDialogue(npc->getFaction());
        StateData::GetInstance()->mainText->setString(file->loadQuestDialogue());
        m_menu = std::make_shared<GUI::Menu>();
        m_menu->setMenuOptions(file->loadPlayerOptions(), true);
    }
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
        else if(m_menu->getChoice() == 1){

//            npc->getFaction();
            std::string msg = "Gained favour with " + npc->getFactionName(npc->getFaction()) + " faction";
            StateData::GetInstance()->dynamicText->setString(msg);

            StateData::GetInstance()->getActiveCharacter()->gainRep(npc->getFaction(), 500);
            m_menu->setActive(false);
        }
        else if(m_menu->getChoice() == 2){

            std::string msg = "Lost favour with " + npc->getFactionName(npc->getFaction()) + " faction";
            StateData::GetInstance()->enemyText->setString(msg);
            StateData::GetInstance()->getActiveCharacter()->loseRep(npc->getFaction(), 500);
            m_menu->setActive(false);
        }
        else{

            file->loadFactionDialogue(2);
            StateData::GetInstance()->mainText->setString(file->loadQuestDialogue());
            m_menu = std::make_shared<GUI::Menu>();
            m_menu->setMenuOptions(file->loadPlayerOptions(), true);
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

