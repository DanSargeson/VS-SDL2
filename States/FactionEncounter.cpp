#include "FactionEncounter.h"
#include "LoadFiles.h"

int FactionEncounter::position = 1;

FactionEncounter::FactionEncounter(int faction){

    firstEncounter = true;

    textBuildCounter = 0;

    textThreadRunning = true;

    getEnemyText()->setString("");

    getDynamicText()->setString("");

    m_fileName = "Assets/factionQuests.txt";

    ///"Assets/newDialogue.txt"

    json_file = "Assets/diag.json";

    npc = std::make_shared<NPC>(faction, 1); // TODO:: NEED TO FIX THIS
    file = std::make_shared<LoadFiles>(m_fileName, 1);

    npc->createDialogueComponent();
    npc->createFactionComponent();
    file->readJsonFile2(json_file);
   // std::pair msg1 = file->getDialogueAndResponses(npc->getFactionStr(), 1, 0);
   std::string check = npc->getFactionStr();
    getMainText()->setString(file->getDialogue(check, 1));
    copyText = getMainText()->getString();
    menu = std::make_shared<GUI::Menu>();

    menu->setMenuOptions(file->getFirstResponses(check, 1), true);

}

void FactionEncounter::startTextThread(){

    textThreadRunning = true;
    textThread = std::thread(&FactionEncounter::updateText, this);
}

FactionEncounter::~FactionEncounter(){

    //getMainText()->setString("Select an option: ");
//    npc.reset();

    if(textThread.joinable()){

        textThread.join();
    }
    //State::~State();
}

void FactionEncounter::update(const float& dt){

    if(textThreadRunning){

        updateText();
    }

    if(textThread.joinable()){

        textThread.join();
    }
}

void FactionEncounter::updateText(){

    if(builderText != copyText){

            menu->setActive(false);

    // loop through each character in the text
        // output one character
        // flush to make sure the output is not delayed
        builderText.push_back(copyText[textBuildCounter]);
        //mTextTexture->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), copy_text, mTextColour, *mFont, true, 80);

        //mTextTexture->render(Engine::GetInstance()->GetRenderer(),  mOutline.x + offsetX, mOutline.y + offsetY);
        // sleep 60 milliseconds
        ///std::this_thread::sleep_for(std::chrono::milliseconds(600));
        getMainText()->setString(builderText);
        //getMainText()->render();
       // std::this_thread::sleep_for(std::chrono::milliseconds(60));
       //L_Deay(700);
        textBuildCounter++;
    }

    else{

        builderText = "";
        textBuildCounter = 0;
        textThreadRunning = false;
        menu->setActive(true);
    }
}

void FactionEncounter::updateEvents(SDL_Event& e)
{

    menu->update(e);


    if(e.type == SDL_MOUSEBUTTONDOWN){


        if(menu->isSelected()){

//            if(menu->getChoice() == 0){
//                Engine::GetInstance()->PopState();
//            }
           // else{

                firstEncounter = false;

                file->selectResponse(npc->getFactionStr(), 1, (menu->getChoice() + 1));
                std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
                getMainText()->setString(msg2);
                copyText = msg2;
                textThreadRunning = true;
                menu->setMenuOptions(file->getPlayerOps(), true);
 //           }
        }
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN)){

        getEnemyText()->clearText();
        getDynamicText()->clearText();

        if(!menu->getActive() && !textThreadRunning){

            Engine::GetInstance()->PopState();
        }

        return;
    }

    State::updateEvents(e);
}

void FactionEncounter::refreshGUI(){

    State::refreshGUI();

    if(firstEncounter){

    std::string check = npc->getFactionStr();
    getMainText()->setString(file->getDialogue(check, 1));
    copyText = getMainText()->getString();
    //textThreadRunning = true;
    menu->setMenuOptions(file->getFirstResponses(check, 1), true);
    }
    else{

        std::string msg2 = file->getDialogue(npc->getFactionStr(), file->getCurrDiagID());
        getMainText()->setString(msg2);
        copyText = msg2;
      //  textThreadRunning = true;
        menu->setMenuOptions(file->getPlayerOps(), true);
    }
}

void FactionEncounter::render()
{

    menu->render();
    if(textThreadRunning){

        getMainText()->setString(builderText);
        getMainText()->render();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        //return;
    }else{

        getMainText()->setString(copyText);
        getMainText()->render();
    }

    if(getEnemyText()->getString() != ""){

        getEnemyText()->render();
    }
    if(getDynamicText()->getString() != ""){

        getDynamicText()->render();
    }
}

