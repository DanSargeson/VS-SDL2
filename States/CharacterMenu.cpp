#include "CharacterMenu.h"
#include "Engine.h"
#include "Input.h"

CharacterMenu::CharacterMenu(){

    invMenu = std::make_shared<GUI::Menu>();

    std::vector<std::string> ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
    invMenu->setMenuOptions(ops, true, true);
    invMenu2 = std::make_shared<GUI::Menu>();
    invMenu->setActive(true);
    invMenu2->setActive(false);
    choice = -1;
    //StateData::GetInstance()->mainText->setPosition(GUI::p2pXi(5), GUI::p2pYi(5), GUI::p2pXi(80), GUI::p2pYi(80));
    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);

    StateData::GetInstance()->mainText->setString(StateData::GetInstance()->getActiveCharacter()->printPlayerDetails(), true, GUI::p2pY(120));

    initButtons();

    mButtons["ATTRIBUTES"]->setSelected(true);

    std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
    StateData::GetInstance()->mainText->setString(mmm, true, 420);
}

CharacterMenu::~CharacterMenu(){

    StateData::GetInstance()->mainText->clearText();
    //StateData::GetInstance()->mainText->setString("Select an option: ");
    StateData::GetInstance()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);
    StateData::GetInstance()->mainText->setString("Select an option: ");
}

void CharacterMenu::refreshGUI(){

    CharacterMenu();
}

void CharacterMenu::update(const float& dt){

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

                std::string msg = StateData::GetInstance()->getActiveCharacter()->getInvItemAsString(choice);
                StateData::GetInstance()->mainText->setString(msg, true, 420);
                //mStateData::getInstane
                    std::cout << invMenu->getChoice() << std::endl;
            }

        }   //FIRST MENU ENDS HERE



        //BUTTONS START HERE
        if (mButtons["SKILLS"]->isPressed(e.button)) {

            invMenu->setActive(true);
            invMenu2->setActive(false);

            mButtons["SKILLS"]->setSelected(true);
            mButtons["ATTRIBUTES"]->setSelected(false);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["FACTIONS"]->setSelected(false);

            std::string msg = StateData::GetInstance()->getActiveCharacter()->displaySkills();
            StateData::GetInstance()->mainText->setString(msg, true, GUI::p2pY(420));
        }

        if (mButtons["FACTIONS"]->isPressed(e.button)) {

            mButtons["SKILLS"]->setSelected(false);
            mButtons["ATTRIBUTES"]->setSelected(false);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["FACTIONS"]->setSelected(true);

            invMenu->setActive(true);
            invMenu2->setActive(false);
            std::string fact = StateData::GetInstance()->getActiveCharacter()->getFactionStr();
            StateData::GetInstance()->mainText->setString(fact, true, 420);
        }

        if (mButtons["ATTRIBUTES"]->isPressed(e.button)) {

            mButtons["SKILLS"]->setSelected(false);
            mButtons["ATTRIBUTES"]->setSelected(true);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["FACTIONS"]->setSelected(false);

            invMenu->setActive(true);
            invMenu2->setActive(false);

            //std::cout << "Attrib pressed\n\n\n\n\n";

           /// StateData::GetInstance()->getActiveCharacter()->getAttributes();
           /// StateData::GetInstance()->mainText->setString("ATTRIBUTES");
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            StateData::GetInstance()->mainText->setString(mmm, true, 420);
        }


//         if (mButtons["INVENTORY"]->isPressed(e.button)) {
//
//            mButtons["SKILLS"]->setSelected(false);
//            mButtons["ATTRIBUTES"]->setSelected(false);
//            mButtons["INVENTORY"]->setSelected(true);
//            mButtons["FACTIONS"]->setSelected(false);
//
//            invMenu->setActive(true);
//            invMenu2->setActive(false);
//            std::string msg = "Choose an item from the menu: ";
//            StateData::GetInstance()->mainText->setString(msg, true, 420);
//        }


        //BUTTONS END HERE

        //INV MENU2 STARTS HERE
        if(invMenu2->isSelected()){

            if(invMenu2->getChoice() == 0){

                invMenu2->setActive(false);
                invMenu->setActive(true);
                std::string msg = "Choose an item from the menu: ";
            StateData::GetInstance()->mainText->setString(msg, true, 420);
                //choice = -1;
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

    for (auto i : mButtons) {

		i.second->renderButtons();
	}
}

void CharacterMenu::initButtons(){

    unsigned int charSize = GUI::calcCharSize(85);


    mButtons["SKILLS"] = new GUI::Button(27.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["SKILLS"]->setRenderText("Skills");

    mButtons["FACTIONS"] = new GUI::Button(42.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["FACTIONS"]->setRenderText("Factions");

    mButtons["ATTRIBUTES"] = new GUI::Button(57.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["ATTRIBUTES"]->setRenderText("Attributes");

//    mButtons["INVENTORY"] = new GUI::Button(65.f, 65.5f, 11.8f, 4.1f, charSize);
//    mButtons["INVENTORY"]->setRenderText("Inventory");

}
