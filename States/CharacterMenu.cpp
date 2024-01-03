#include "CharacterMenu.h"
#include "Engine.h"
#include "Input.h"

CharacterMenu::CharacterMenu(){

  //  menu = std::make_shared<GUI::Menu>();

    invMenu2 = std::make_shared<GUI::Menu>();
    ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();

    checkItemStrength();
    menu->setMenuOptions(ops, true, true);
    menu->setActive(true);
    invMenu2->setActive(false);
    choice = -1;
    //getMainText()->setPosition(GUI::p2pXi(5), GUI::p2pYi(5), GUI::p2pXi(80), GUI::p2pYi(80));
    getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);

    getMainText()->setString(StateData::GetInstance()->getActiveCharacter()->printPlayerDetails(), true, GUI::p2pY(120));

    initButtons();

    mButtons["ATTRIBUTES"]->setSelected(true);

    std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
    getMainText()->setString(mmm, true, 420);
}

void CharacterMenu::checkItemStrength(){

    for(int i = 0; i < ops.size(); i++){

        auto wv = getData()->getActiveCharacter()->findItem(i);

        if(wv->getItemType() == WEAPON){

            if(dynamic_cast<Weapon&>(*wv).getDamageMin() > getData()->getActiveCharacter()->getActiveWeapon()->getDamageMin()){

                    ops[i] += " **";
            }
        }
    }
}

CharacterMenu::~CharacterMenu(){

//    State::~State();
//    menu.reset();
    invMenu2.reset();
}

void CharacterMenu::refreshGUI(){

    State::refreshGUI();
    invMenu2->refreshGUI();
    initButtons();
}

void CharacterMenu::update(const float& dt){

    menu->update();
    invMenu2->update();
}

void CharacterMenu::updateEvents(SDL_Event& e){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN) && e.key.repeat == 0){

        menu->scrollText(0);
    }

      if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP) && e.key.repeat == 0){

        menu->scrollText(1);
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(menu->isSelected() && menu->getActive()){

//            if(invMenu->getChoice() == 0){
//
//                Engine::GetInstance()->PopPopState();
//
//                return;
//            }

                choice = menu->getChoice();
                std::vector<std::string> ops2;
                ops2.push_back("Equip Item");
                ops2.push_back("Drop Item");

                menu->setActive(false);
                invMenu2->setMenuOptions(ops2, true);
                invMenu2->setActive(true);

                std::string msg = StateData::GetInstance()->getActiveCharacter()->getInvItemAsString(choice);
                getMainText()->setString(msg, true, 420);
                //mStateData::getInstane
        ///            std::cout << invMenu->getChoice() << std::endl;

        }   //FIRST MENU ENDS HERE

    ///THIS IS THE ONE111 else{

     //INV MENU2 STARTS HERE


        if(invMenu2->getActive() && invMenu2->isSelected()){
            std::cout << "CHOICE: " << choice << std::endl;
            auto wv = StateData::GetInstance()->getActiveCharacter()->findItem(choice);
            int cc = invMenu2->getChoice();
            //if(invMenu2->getChoice() == 0){

                //if(wv->getItemType() == WEAPON){

                if(cc == 0){        ///Equip item
                    StateData::GetInstance()->getActiveCharacter()->equipItem(choice);
                }
                if(cc == 1){  ///Drop item

                    getData()->getActiveCharacter()->removeItem(wv);
                }

                //invMenu2->setActive(false);
                //invMenu->setActive(true);
                ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
                checkItemStrength();
                menu->setMenuOptions(ops, true, true);
                 std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
                getMainText()->setString(mmm, true, 420);
                 mButtons["SKILLS"]->setSelected(false);
                mButtons["ATTRIBUTES"]->setSelected(true);
            //mButtons["INVENTORY"]->setSelected(false);
                mButtons["FACTIONS"]->setSelected(false);
                //}
            ///}

            ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
            checkItemStrength();
            menu->setMenuOptions(ops, true, true);
            menu->setActive(true);
            invMenu2->setActive(false);
    }



        //BUTTONS START HERE
        if (mButtons["SKILLS"]->isPressed(e.button)) {

            menu->setActive(false);
            invMenu2->setActive(false);

            mButtons["SKILLS"]->setSelected(true);
            mButtons["ATTRIBUTES"]->setSelected(false);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["FACTIONS"]->setSelected(false);

            std::string msg = StateData::GetInstance()->getActiveCharacter()->displaySkills();
            getMainText()->setString(msg, true, GUI::p2pY(420));
        }

        if (mButtons["FACTIONS"]->isPressed(e.button)) {

            mButtons["SKILLS"]->setSelected(false);
            mButtons["ATTRIBUTES"]->setSelected(false);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["FACTIONS"]->setSelected(true);

            menu->setActive(false);
            invMenu2->setActive(false);
            std::string fact = StateData::GetInstance()->getActiveCharacter()->getFactionStr();
            getMainText()->setString(fact, true, 420);
        }

        if (mButtons["ATTRIBUTES"]->isPressed(e.button)) {

            mButtons["SKILLS"]->setSelected(false);
            mButtons["ATTRIBUTES"]->setSelected(true);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["FACTIONS"]->setSelected(false);

            menu->setActive(true);
            invMenu2->setActive(false);

            //std::cout << "Attrib pressed\n\n\n\n\n";

           /// StateData::GetInstance()->getActiveCharacter()->getAttributes();
           /// getMainText()->setString("ATTRIBUTES");
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, 420);
        }

        //BUTTONS END HERE
    }

    if(invMenu2->getActive() == false){
        State::updateEvents(e);
    }
    else{

        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

            invMenu2->setActive(false);
            menu->setActive(true);
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, 420);
        }
    }
}

void CharacterMenu::render(){

    getMainText()->render();

    if(menu->getActive()){
        menu->render();
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
