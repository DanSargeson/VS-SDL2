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

    npc = std::make_shared<Entity>();


    npc->createDialogueComponent();
    ///npc->setCharacterName(npc->getName());
    ///npc->setDialogueText(file->loadDialogue());

    if(type <= 3){
        StateData::GetInstance()->mainText->setString(file->loadRandomDialogue());
        m_menu = std::make_shared<GUI::Menu>();
    }
    else{
        file->loadFactionDialogue(1);
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

        Engine::GetInstance()->PopState();

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
    m_menu->render();
}

