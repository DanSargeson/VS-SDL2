#include "RandomEncounter.h"


RandomEncounter::RandomEncounter(){

    filename = "Assets/newDialogue.txt";

    file = std::make_shared<LoadFiles>(filename, 3);

    int random = rand() % 7 + 1;
    npc = std::make_shared<NPC>(random); // RED


    npc->createDialogueComponent();
    npc->createFactionComponent();

    StateData::GetInstance()->mainText->setString(file->loadRandomDialogue());
    menu = std::make_shared<GUI::Menu>();
}

void RandomEncounter::update(const float& dt)
{

}

void RandomEncounter::updateEvents(SDL_Event& e)
{

}

void RandomEncounter::render()
{

}
