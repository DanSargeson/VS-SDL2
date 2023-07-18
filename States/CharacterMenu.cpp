#include "CharacterMenu.h"
#include "Engine.h"
#include "Input.h"

CharacterMenu::CharacterMenu(){

    invMenu = std::make_shared<GUI::Menu>(*StateData::GetInstance());

    std::vector<std::string> ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
    invMenu->setMenuOptions(ops, true);
    invMenu2 = std::make_shared<GUI::Menu>(*StateData::GetInstance());
    invMenu2->setActive(false);
    choice = -1;
    //StateData::GetInstance()->mainText->setPosition(GUI::p2pXi(5), GUI::p2pYi(5), GUI::p2pXi(80), GUI::p2pYi(80));
    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), 5, 5, 89, 60, true);
}

CharacterMenu::~CharacterMenu(){

    StateData::GetInstance()->mainText->clearText();
    //StateData::GetInstance()->mainText->setString("Select an option: ");
    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(Engine::GetInstance()->GetRenderer(), Engine::GetInstance()->GetWindow(), 5, 5, 89, 60, true);
    StateData::GetInstance()->mainText->setString("Select an option: ");
}

void CharacterMenu::refreshGUI(){

    CharacterMenu();
}

void CharacterMenu::update(const float& dt){

    StateData::GetInstance()->mainText->setString(StateData::GetInstance()->getActiveCharacter()->printPlayerDetails(), true, GUI::p2pY(120));
    invMenu->update();
    invMenu2->update();
}

void CharacterMenu::updateEvents(SDL_Event& e){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN) && e.key.repeat == 0){

        invMenu->scrollText(0);
    }

      if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP) && e.key.repeat == 0){

        invMenu->scrollText(1);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

        Engine::GetInstance()->PopState();

        return;
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(invMenu->isSelected()){

            if(invMenu->getChoice() == 0){

                Engine::GetInstance()->PopState();

                return;
            }

            if(invMenu->getChoice() != 0){

                choice = invMenu->getChoice();
                std::vector<std::string> ops;
                ops.push_back("Equip Item");
                ops.push_back("Drop Item");

                invMenu->setActive(false);
                invMenu2->setMenuOptions(ops, true);
                invMenu2->setActive(true);

                    std::cout << invMenu->getChoice() << std::endl;
            }

        }   //FIRST MENU ENDS HERE


        if(invMenu2->isSelected()){

            if(invMenu2->getChoice() == 0){

                invMenu2->setActive(false);
                invMenu->setActive(true);
                choice = -1;
            }

            std::cout << "CHOICE: " << choice << std::endl;
            auto wv = StateData::GetInstance()->getActiveCharacter()->findItem(choice);
            if(invMenu2->getChoice() == 1){

                //if(wv->getItemType() == WEAPON){
                StateData::GetInstance()->getActiveCharacter()->equipItem(choice);

                invMenu2->setActive(false);
                invMenu->setActive(true);
                std::vector<std::string> ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
                invMenu->setMenuOptions(ops, true);
                choice = -1;
                //}
            }
        }
    }
}

void CharacterMenu::render(){

    StateData::GetInstance()->mainText->render();

    if(invMenu->getActive()){
        invMenu->render();
    }
    if(invMenu2->getActive()){
        invMenu2->render();
    }
}

