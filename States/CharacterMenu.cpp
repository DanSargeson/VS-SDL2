#include "CharacterMenu.h"
#include "Engine.h"
#include "Input.h"

CharacterMenu::CharacterMenu(){

  //  menu = std::make_shared<GUI::Menu>();

    invMenu2 = std::make_shared<GUI::Menu>();
    ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();

    std::cout << getData()->getActiveCharacter()->getInvAsString() << endl;

    getMainText()->setFontSize(20);
    if(!ops.empty()){

        if(ops[0] == "You have no items"){

            menu->setMenuOptions(ops, false, false);
            menu->setActive(true);
        }
        else{
        std::cout << ops[0] <<std::endl;
        checkItemStrength();
        menu->setMenuOptions(ops, true, true);
        menu->setActive(true);
        }
    }

    std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
    getMainText()->setString(mmm, true, 420);
    invMenu2->setActive(false);
    choice = -1;
    //getMainText()->setPosition(GUI::p2pXi(5), GUI::p2pYi(5), GUI::p2pXi(80), GUI::p2pYi(80));
    ///getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);

    ///getMainText()->setString(StateData::GetInstance()->getActiveCharacter()->printPlayerDetails(), true, GUI::p2pY(120));

    initButtons();

    ///mButtons["ATTRIBUTES"]->setSelected(true);


}

void CharacterMenu::checkItemStrength(){


    for(int i = 0; i < ops.size(); i++){
        auto wv = getData()->getActiveCharacter()->findItem(i);
        if(wv->getItemType() == WEAPON){
            if(getActiveCharacter()->getActiveWeapon() != nullptr){

                if(dynamic_cast<Weapon&>(*wv).getDamageMin() > getData()->getActiveCharacter()->getActiveWeapon()->getDamageMin()){

                    ops[i] += " *";
                }
            }
            else {
                    ops[i] += " *";
            }
        }
        else if(wv->getItemType() == ARMOUR){

            int itemType = dynamic_cast<Armour&>(*wv).getType();

            switch(itemType){

            case armourType::HEAD:

                if(getData()->getActiveCharacter()->getActiveHead() != nullptr){

                if(dynamic_cast<Armour&>(*wv).getDefence() > getData()->getActiveCharacter()->getActiveHead()->getDefence()){

                        ops[i] += " *";
                    }
                }
                else{

                    ops[i] += " *";
                }
                    break;


            case armourType::CHEST:

                if(getData()->getActiveCharacter()->getActiveChest() != nullptr){


                if(dynamic_cast<Armour&>(*wv).getDefence() > getData()->getActiveCharacter()->getActiveChest()->getDefence()){

                        ops[i] += " *";
                    }
                }
                else{

                    ops[i] += " *";
                }
                    break;


            case armourType::ARMS:

                  if(getData()->getActiveCharacter()->getActiveArms() != nullptr){


                if(dynamic_cast<Armour&>(*wv).getDefence() > getData()->getActiveCharacter()->getActiveArms()->getDefence()){

                        ops[i] += " *";
                    }
                  }
                  else{

                    ops[i] += " *";
                }
                    break;

            case armourType::LEGS:

                if(getData()->getActiveCharacter()->getActiveArms() != nullptr){

                if(dynamic_cast<Armour&>(*wv).getDefence() > getData()->getActiveCharacter()->getActiveLegs()->getDefence()){

                        ops[i] += " *";
                    }
                }
                else{

                    ops[i] += " *";
                }
                    break;

            default:
                ops[i] += " *";
                break;
            }
        }   //EMD ARMOUR CHECK
    }
}

CharacterMenu::~CharacterMenu(){

//    State::~State();
//    menu.reset();

    ops.clear();

    //getMainText()->setFontSize(24);
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
    ///checkItemStrength();
}

void CharacterMenu::updateEvents(SDL_Event& e){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN) && e.key.repeat == 0){

        menu->scrollText(0);
    }

      if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP) && e.key.repeat == 0){

        menu->scrollText(1);
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(menu->isSelected() && menu->getActive() && ops[0] != "You have no items"){

//            if(invMenu->getChoice() == 0){
//
//                Engine::GetInstance()->PopPopState();
//
//                return;
//            }

            if(ops[0] == "You have no armour" || ops[0] == "You have no weapons"){

                return;
            }

                choice = menu->getChoice();
                std::vector<std::string> ops2;
                ops2.push_back("Equip Item");
                ops2.push_back("Drop Item");

                menu->setActive(false);
                invMenu2->setMenuOptions(ops2, true);
                invMenu2->setActive(true);


                std::string msg;
                if(mButtons["ARMOURS"]->getSelected()){

                        msg = getActiveCharacter()->getArmAsString(choice);
                        initButtons();
                }
                else if(mButtons["WEAPONS"]->getSelected()){

                    msg = getActiveCharacter()->getWepAsString(choice);
                    initButtons();
                }
                else{

                    msg = StateData::GetInstance()->getActiveCharacter()->getInvItemAsString(choice);
                }

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

                    if(mButtons["WEAPONS"]->getSelected()){

                        getActiveCharacter()->equipWeapon(choice);
                    }
                    else if(mButtons["ARMOURS"]->getSelected()){

                        getActiveCharacter()->equipArmour(choice);
                    }
                    else{

                        StateData::GetInstance()->getActiveCharacter()->equipItem(choice);
                    }
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
                 //mButtons["SKILLS"]->setSelected(false);
                //mButtons["ATTRIBUTES"]->setSelected(true);
            //mButtons["INVENTORY"]->setSelected(false);
                //mButtons["FACTIONS"]->setSelected(false);
                //}
            ///}

            ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
            checkItemStrength();
            if(ops[0] == "You have no items"){

                menu->setMenuOptions(ops, false, false);
            }
            else{

                menu->setMenuOptions(ops, true, true);
            }
            menu->setActive(true);
            invMenu2->setActive(false);
    }



        //BUTTONS START HERE
        if (mButtons["WEAPONS"]->isPressed(e.button)) {

            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, 420);

            menu->setActive(true);
            invMenu2->setActive(false);

            mButtons["WEAPONS"]->setSelected(true);
            mButtons["ARMOURS"]->setSelected(false);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["ALL"]->setSelected(false);

            ops = getActiveCharacter()->getWepAsVec();
            if(ops[0] != "You have no weapons"){

                checkItemStrength();
                menu->setMenuOptions(ops, true, true);
            }
            else{

                menu->setMenuOptions(ops, false, false);
            }
        }

        if (mButtons["ALL"]->isPressed(e.button)) {

            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, 420);

            mButtons["WEAPONS"]->setSelected(false);
            mButtons["ARMOURS"]->setSelected(false);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["ALL"]->setSelected(true);

            menu->setActive(true);
            invMenu2->setActive(false);
            ops = getActiveCharacter()->getInvAsVec();
            if(ops[0] != "You have no items"){

                checkItemStrength();
                menu->setMenuOptions(ops, true, true);
            }
            else{
                menu->setMenuOptions(ops, false, false);
            }
        }

        if (mButtons["ARMOURS"]->isPressed(e.button)) {

            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, 420);

            mButtons["WEAPONS"]->setSelected(false);
            mButtons["ARMOURS"]->setSelected(true);
            //mButtons["INVENTORY"]->setSelected(false);
            mButtons["ALL"]->setSelected(false);

            menu->setActive(true);
            invMenu2->setActive(false);
            ops = getActiveCharacter()->getArmAsVec();
            if(ops[0] != "You have no armour"){

                checkItemStrength();
                menu->setMenuOptions(ops, true, true);
            }
            else{

                menu->setMenuOptions(ops, false, false);
            }

            //std::cout << "Attrib pressed\n\n\n\n\n";

           /// StateData::GetInstance()->getActiveCharacter()->getAttributes();
           /// getMainText()->setString("ATTRIBUTES");

//            getMainText()->setFontSize(10);
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
//            getMainText()->setFontSize(10);
        }
    }
}

void CharacterMenu::render(){

    getMainText()->render();

    if(getDynamicText()->getString() != ""){

        getDynamicText()->render();
    }

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

    unsigned int charSize = GUI::calcCharSize(125);


    mButtons["WEAPONS"] = new GUI::Button(27.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["WEAPONS"]->setRenderText("Weapons");

    mButtons["ARMOURS"] = new GUI::Button(42.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["ARMOURS"]->setRenderText("Armour");

    mButtons["ALL"] = new GUI::Button(57.f, 65.5f, 11.8f, 4.1f, charSize);
    mButtons["ALL"]->setRenderText("All");

    mButtons["WEAPONS"]->setSelected(false);
    mButtons["ARMOURS"]->setSelected(false);
    mButtons["ALL"]->setSelected(true);

}
