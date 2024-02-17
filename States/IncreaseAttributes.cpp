#include "IncreaseAttributes.h"
#include "Game.h"
#include "AttributeComponent.h"

//void IncreaseAttributes::initFonts(){
//
//    try{
//
//        font = TTF_OpenFont("Assets/Fonts/SF Atarian System.ttf", 24);
//
//    }
//    catch(exception e){
//
//        std::ofstream outFile;
//
//        outFile.open("errorLog.txt");
//
//        if(outFile.is_open()){
//
//            outFile << e.what() << endl;
//
//            outFile.close();
//        }
//    }
//}

void IncreaseAttributes::initKeyBinds(){


    std::ifstream ifs("Config/gameStateKeyBinds.ini");

    if(ifs.is_open()){

        std::string key = " ";
        std::string key2 = " ";

        while(ifs >> key >> key2){

            //this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void IncreaseAttributes::initGUI(){

    pointsMessage = std::make_unique<GUI::Text>(60, 20, 0, 0, false);

    this->spriteAddTexture = std::make_shared<Texture>();
    spriteAddTexture->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());

    spriteMinusTexture = std::make_shared<Texture>();
    spriteMinusTexture->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());


    this->spriteAddAgility= std::make_shared<Texture>();
    spriteAddAgility->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusAgility = std::make_shared<Texture>();
    spriteMinusAgility->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddCha = std::make_shared<Texture>();
    spriteAddCha->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusCha = std::make_shared<Texture>();
    spriteMinusCha->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddDex = std::make_shared<Texture>();
    spriteAddDex->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusDex = std::make_shared<Texture>();
    spriteMinusDex->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddInt = std::make_shared<Texture>();
    spriteAddInt->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusInt = std::make_shared<Texture>();
    spriteMinusInt->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddLuck= std::make_shared<Texture>();
    spriteAddLuck->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusLuck = std::make_shared<Texture>();
    spriteMinusLuck->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddStrength = std::make_shared<Texture>();
    spriteAddStrength->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusStrength = std::make_shared<Texture>();
    spriteMinusStrength->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());

    this->spriteAddVit = std::make_shared<Texture>();
    spriteAddVit->loadFromFile("Assets/GUI/arrowPlus.png", Engine::GetInstance()->GetRenderer());
    spriteMinusVit = std::make_shared<Texture>();
    spriteMinusVit->loadFromFile("Assets/GUI/arrowMinus.png", Engine::GetInstance()->GetRenderer());


    menuPos = MENU_POS::ATTRIBUTES;

    SDL_Window* vm = Engine::GetInstance()->GetWindow();

    unsigned int charSize = GUI::calcCharSize(80);

    this->buttons["ATTRIBUTES"] = std::make_unique<GUI::Button>(4.f, 4.f, 18.8f, 8.3f, charSize);
    this->buttons["ATTRIBUTES"]->setRenderText("Attributes");

    this->buttons["DONE"] = std::make_unique<GUI::Button>(44.f, 4.f, 18.8f, 8.3f, charSize);
    this->buttons["DONE"]->setRenderText("Done");

    mSprites["AGILITY_PLUS"] = spriteAddAgility;
    mSprites["AGILITY_MINUS"] = spriteMinusAgility;
    mSprites["CHA_PLUS"] = spriteAddCha;
    mSprites["CHA_MINUS"] = spriteMinusCha;
    mSprites["DEX_PLUS"] = spriteAddDex;
    mSprites["DEX_MINUS"] = spriteMinusDex;
    mSprites["INT_PLUS"] = spriteAddInt;
    mSprites["INT_MINUS"] = spriteMinusInt;
    mSprites["LUCK_PLUS"] = spriteAddLuck;
    mSprites["LUCK_MINUS"] = spriteMinusLuck;
    mSprites["STR_PLUS"] = spriteAddStrength;
    mSprites["STR_MINUS"] = spriteMinusStrength;
    mSprites["VIT_PLUS"] = spriteAddVit;
    mSprites["VIT_MINUS"] = spriteMinusVit;


    mSprites["AGILITY_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(32.f));
    mSprites["AGILITY_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(32.f));

    mSprites["CHA_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(41.5f));
    mSprites["CHA_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(41.5f));

    mSprites["DEX_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(51.f));
    mSprites["DEX_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(51.f));

    mSprites["INT_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(60.f));
    mSprites["INT_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(60.f));

    mSprites["LUCK_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(69.5f));
    mSprites["LUCK_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(69.5f));

    mSprites["STR_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(79.f));
    mSprites["STR_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(79.f));

    mSprites["VIT_PLUS"]->setPositionFloat(GUI::p2pX(36.f), GUI::p2pY(88.f));
    mSprites["VIT_MINUS"]->setPositionFloat(GUI::p2pX(12.f), GUI::p2pY(88.f));
}

void IncreaseAttributes::initText(){

    unsigned charSize = GUI::calcCharSize(80);

    this->charCreatorText = std::make_unique<GUI::Text>(18, 22, 0, 0, false);

    //charCreatorText->setPositionF(18, 22);

    strengthText->setString("STRENGTH : " + to_string(getActiveCharacter()->getAttribute(STRENGTH)));

    std::string msg = strengthText->getString();
    dexText->setString("DEXTERITY : " + to_string(getActiveCharacter()->getAttribute(DEXTERITY)));
    agiText->setString("AGILITY : " + to_string(getActiveCharacter()->getAttribute(AGILITY)));
    intText->setString("INTELLIGENCE : " + to_string(getActiveCharacter()->getAttribute(INTELLIGENCE)));
    charText->setString("CHARISMA : " + to_string(getActiveCharacter()->getAttribute(CHARISMA)));
    luckText->setString("LUCK : " + to_string(getActiveCharacter()->getAttribute(LUCK)));
    vitText->setString("VITALITY : " + to_string(getActiveCharacter()->getAttribute(VITALITY)));

    strengthText->setPositionF(18, 78);
    agiText->setPositionF(18, 31);
    charText->setPositionF(18, 40);
    dexText->setPositionF(18, 50);
    intText->setPositionF(18, 59);
    vitText->setPositionF(18, 87);
    luckText->setPositionF(18, 69);
}

IncreaseAttributes::IncreaseAttributes() : State(){


    strengthText = std::make_shared<GUI::Text>();
    dexText = std::make_shared<GUI::Text>();
    agiText = std::make_shared<GUI::Text>();
    intText = std::make_shared<GUI::Text>();
    charText = std::make_shared<GUI::Text>();
    luckText = std::make_shared<GUI::Text>();
    vitText = std::make_shared<GUI::Text>();


    lastMenuPos = MENU_POS::ATTRIBUTES;

    maxPoints = getActiveCharacter()->getAttributePoints();
    pointsToSpend = maxPoints;

    const char* fontFile = "Assets/Fonts/SF Atarian System.ttf";

    if(this->font = TTF_OpenFont(fontFile, 26)){

        std::cout << "WORKED";
    }


 //   initFonts();
    this->initGUI();
    this->initText();

    pointsMessage->setString("POINTS AVAILABLE:  " + std::to_string(pointsToSpend));

    menuPos = lastMenuPos;

///    SDL_SetTextInputRect(&textBox);

///    StateData::GetInstance()->currentMap->LoadFromFile("Data/Map1.txt");
}

IncreaseAttributes::~IncreaseAttributes(){

   /// State::~State();
   mainScreen = true;
}

void IncreaseAttributes::updateButtons(const float &dt){

    for(auto &it : this->buttons){

        it.second->update();
    }
}

void IncreaseAttributes::updateInput(const float& dt){


        //DECREASE
        if(pointsToSpend > getActiveCharacter()->getAttributePoints()){

            pointsToSpend = getActiveCharacter()->getAttributePoints();
        }
        if(pointsToSpend <= 0){

            pointsToSpend = 0;
//            textInput = true;
        }
}

void IncreaseAttributes::updateText(const float& dt){

    if(this->menuPos == MENU_POS::ATTRIBUTES){

        std::string msg = " ";
//        msg = getAttributeSheet();

        charCreatorText->setString(msg, true, 250);

        pointsMessage->setString("Points available: " + std::to_string(pointsToSpend));
    }
}

void IncreaseAttributes::update(const float& dt){


    if(pointsToSpend > 0){

        buttons["DONE"]->setActive(false);
    }
    else{

        buttons["DONE"]->setActive(true);
    }

    updateButtons(dt);
    updateInput(dt);
    updateText(dt);
}

void IncreaseAttributes::updateEvents(SDL_Event& e){

//    if(textInput){
//
//       /// if(e.key.keysym.sym == SDLK_BACKSPACE && e.key.repeat != 0 && name.length() > 0){
//
//        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_BACKSPACE) && name.length() > 0){
//
//            name.pop_back();
//            ///SDL_Delay(60);
//
//            return;
//        }
//       /// }
//        if(e.key.keysym.sym == SDLK_RETURN){
//
//
//        }
//
//        if(e.type == SDL_TEXTINPUT){
//
//            this->updateTextInput(e);
//        }
//    }




    ///MOUSE EVENTS
    if(e.type == SDL_MOUSEBUTTONDOWN){

        if(buttons["ATTRIBUTES"]->isPressed(e.button)){

            menuPos = MENU_POS::ATTRIBUTES;
        }

        if(buttons["DONE"]->isPressed(e.button)){

            getActiveCharacter()->setAttributePoints(0);
            getActiveCharacter()->updateStats(true);
            getActiveCharacter()->calculateSkills();
            saveCharacters();
            Engine::GetInstance()->PopState();

            return;
        }

        if(menuPos == MENU_POS::ATTRIBUTES && pointsToSpend > 0){          ///TODO Took this out

            int x, y;

            SDL_GetMouseState(&x, &y);

            if(e.button.button == SDL_BUTTON_LEFT){

                if(mSprites["AGILITY_PLUS"]->intersects(x, y)){

                    //Increase Skill
                        getActiveCharacter()->increaseAttribute(AGILITY);
                        pointsToSpend--;
                        std::string m = "AGILITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::AGILITY));
                        agiText->setString(m);
                }

                if(mSprites["CHA_PLUS"]->intersects(x, y)){

                    //Increase Skill


                        getActiveCharacter()->increaseAttribute(CHARISMA);
                        pointsToSpend--;
                        std::string m = "CHARISMA : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::CHARISMA));
                        charText->setString(m);
                }

                if(mSprites["DEX_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(DEXTERITY);
                        pointsToSpend--;
                        std::string m = "DEXTERITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::DEXTERITY));
                        dexText->setString(m);

                }

                if(mSprites["INT_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(INTELLIGENCE);
                        pointsToSpend--;
                        std::string m = "INTELLIGENCE : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::INTELLIGENCE));
                        intText->setString(m);

                }

                if(mSprites["LUCK_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(LUCK);
                        pointsToSpend--;
                        std::string m = "LUCK : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::LUCK));
                        luckText->setString(m);
                }

                if(mSprites["STR_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(STRENGTH);
                        pointsToSpend--;
                        std::string m = "STRENGTH : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::STRENGTH));
                        strengthText->setString(m);
                }

                if(mSprites["VIT_PLUS"]->intersects(x, y)){

                        getActiveCharacter()->increaseAttribute(VITALITY);
                        pointsToSpend--;
                        std::string m = "VITALITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::VITALITY));
                        vitText->setString(m);
                }
            }
        }

//        //DECREASE
//        if(menuPos == MENU_POS::ATTRIBUTES && pointsToSpend <= 20){
//
//            int x, y;
//
//            SDL_GetMouseState(&x, &y);
//
//            if(e.button.button == SDL_BUTTON_LEFT){
//
//                if(mSprites["AGILITY_MINUS"]->intersects(x, y)){
//
//                    //Increase Skill
//                    if(getActiveCharacter()->getAttribute(AGILITY) > 0){
//
//                        getActiveCharacter()->decreaseAttribute(AGILITY);
//                        pointsToSpend++;
//                        std::string m = "AGILITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::AGILITY));
//                        agiText->setString(m);
//                    }
//                }
//
//                if(mSprites["CHA_MINUS"]->intersects(x, y)){
//
//                    //Increase Skill
//                    if(getActiveCharacter()->getAttribute(CHARISMA) > 1){
//
//                        getActiveCharacter()->decreaseAttribute(CHARISMA);
//                        pointsToSpend++;
//                        std::string m = "CHARISMA : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::CHARISMA));
//                        charText->setString(m);
//                    }
//                }
//
//                if(mSprites["DEX_MINUS"]->intersects(x, y)){
//
//                    if(getActiveCharacter()->getAttribute(DEXTERITY) > 1){
//
//                        getActiveCharacter()->decreaseAttribute(DEXTERITY);
//                        pointsToSpend++;
//                        std::string m = "DEXTERITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::DEXTERITY));
//                        dexText->setString(m);
//                    }
//                }
//
//                if(mSprites["INT_MINUS"]->intersects(x, y)){
//
//                    if(getActiveCharacter()->getAttribute(INTELLIGENCE) > 1){
//
//                        getActiveCharacter()->decreaseAttribute(INTELLIGENCE);
//                        pointsToSpend++;
//                        std::string m = "INTELLIGENCE : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::INTELLIGENCE));
//                        intText->setString(m);
//                    }
//                }
//
//                if(mSprites["LUCK_MINUS"]->intersects(x, y)){
//
//                    if(getActiveCharacter()->getAttribute(LUCK) > 1){
//
//                        getActiveCharacter()->decreaseAttribute(LUCK);
//                        pointsToSpend++;
//                        std::string m = "LUCK : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::LUCK));
//                        luckText->setString(m);
//                    }
//                }
//
//                if(mSprites["STR_MINUS"]->intersects(x, y)){
//
//                    if(getActiveCharacter()->getAttribute(STRENGTH) > 1){
//
//                        getActiveCharacter()->decreaseAttribute(STRENGTH);
//                        pointsToSpend++;
//                        std::string m = "STRENGTH : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::STRENGTH));
//                        strengthText->setString(m);
//                    }
//                }
//
//                if(mSprites["VIT_MINUS"]->intersects(x, y)){
//
//                    if(getActiveCharacter()->getAttribute(VITALITY) > 1){
//
//                        getActiveCharacter()->decreaseAttribute(VITALITY);
//                        pointsToSpend++;
//                        std::string m = "VITALITY : " + std::to_string(getActiveCharacter()->getAttribute(ATTRIBUTE::VITALITY));
//                        vitText->setString(m);
//                    }
//                } //END MINUS???
//            }
//        }
    }

    State::updateEvents(e);
}

void IncreaseAttributes::updateMouseEvents(SDL_MouseButtonEvent& e){


}

void IncreaseAttributes::updateTextInput(SDL_Event& e){

//    if(textInput && !textEditDone){
//
//       /// name += e.text.text;
//        name.push_back(*e.text.text);
//        std::cout << name << std::endl;
//        SDL_Delay(10);
//    }
}

void IncreaseAttributes::updateGUI(){

    initGUI();
}

void IncreaseAttributes::render(){


SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
 SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    for(auto &it : buttons){

        it.second->renderButtons();
    }

    if(menuPos == MENU_POS::ATTRIBUTES){


        if(pointsToSpend > 0){

            pointsMessage->render();
        }
        std::string name = charCreatorText->getString();
        strengthText->render();
        agiText->render();
        dexText->render();
        intText->render();
        charText->render();
        vitText->render();
        luckText->render();

        for(auto &it : mSprites){

            it.second->render(Engine::GetInstance()->GetRenderer(), it.second->getTextureRect().x, it.second->getTextureRect().y);
        }
    }
}
