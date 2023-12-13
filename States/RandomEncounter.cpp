#include "RandomEncounter.h"


RandomEncounter::RandomEncounter(){

    filename = "Assets/newDialogue.txt";


    int random = rand() % 7 + 1;
    npc = std::make_shared<NPC>(random); // RED
    file = std::make_shared<LoadFiles>(filename, 0);


    npc->createDialogueComponent();
    npc->createFactionComponent();

    getData()->mainText->setString(file->loadRandomDialogue());
    menu = std::make_shared<GUI::Menu>();

    std::vector<std::string> ops;
    ops.push_back("Op 1.");
    ops.push_back("Op 2.");
    ops.push_back("Op 3.");


    menu->setMenuOptions(ops, true);

    //getData()->mainText->setString("TESTING");
}

RandomEncounter::~RandomEncounter(){

    getData()->mainText->setString("Select an option: ");
}


void RandomEncounter::update(const float& dt)
{

}

void RandomEncounter::updateEvents(SDL_Event& e){

    menu->update();

    if(e.type == SDL_MOUSEBUTTONDOWN){
        if(menu->isSelected()){

            if(menu->getChoice() == 0){

                Engine::GetInstance()->PopState();

                return;
            }
        }
    }
}

void RandomEncounter::render(){

    menu->render();
    getData()->mainText->render();
}
