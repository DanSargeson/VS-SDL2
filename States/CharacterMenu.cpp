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
    //getMainText()->setPosition(GUI::p2pXi(5), GUI::p2pYi(5), GUI::p2pXi(80), GUI::p2pYi(80));
    getMainText() = std::make_shared<GUI::Text>(5, 5, 89, 60, true);

    getMainText()->setString(StateData::GetInstance()->getActiveCharacter()->printPlayerDetails(), true, GUI::p2pY(120));

    initButtons();

    mButtons["ATTRIBUTES"]->setSelected(true);

    std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
    getMainText()->setString(mmm, true, 420);
}

CharacterMenu::~CharacterMenu(){

    State::~State();
    invMenu.reset();
    invMenu2.reset();
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

    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(invMenu->isSelected() && invMenu->getActive()){

//            if(invMenu->getChoice() == 0){
//
//                Engine::GetInstance()->PopPopState();
//
//                return;
//            }

                choice = invMenu->getChoice();
                std::vector<std::string> ops;
                ops.push_back("Equip Item");
                ops.push_back("Drop Item");

                invMenu->setActive(false);
                invMenu2->setMenuOptions(ops, true);
                invMenu2->setActive(true);

                std::string msg = StateData::GetInstance()->getActiveCharacter()->getInvItemAsString(choice);
                getMainText()->setString(msg, true, 420);
                //mStateData::getInstane
                    std::cout << invMenu->getChoice() << std::endl;

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
                std::vector<std::string> ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
                invMenu->setMenuOptions(ops, true, true);
                 std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
                getMainText()->setString(mmm, true, 420);
                 mButtons["SKILLS"]->setSelected(false);
                mButtons["ATTRIBUTES"]->setSelected(true);
            //mButtons["INVENTORY"]->setSelected(false);
                mButtons["FACTIONS"]->setSelected(false);
                //}
            ///}

            ops = StateData::GetInstance()->getActiveCharacter()->getInvAsVec();
            invMenu->setMenuOptions(ops, true, true);
            invMenu->setActive(true);
            invMenu2->setActive(false);
    }



        //BUTTONS START HERE
        if (mButtons["SKILLS"]->isPressed(e.button)) {

            invMenu->setActive(false);
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

            invMenu->setActive(false);
            invMenu2->setActive(false);
            std::string fact = StateData::GetInstance()->getActiveCharacter()->getFactionStr();
            getMainText()->setString(fact, true, 420);
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
            invMenu->setActive(true);
            std::string mmm = StateData::GetInstance()->getActiveCharacter()->getStatsAttributeScreen();
            getMainText()->setString(mmm, true, 420);
        }
    }
}

void CharacterMenu::render(){

    getMainText()->render();

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
