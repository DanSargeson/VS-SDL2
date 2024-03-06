#include "State.h"
#include "Engine.h"

//Input* Input::s_Instance = nullptr;
StateData* StateData::s_Instance = nullptr;


void StateData::initFonts(){

    try{

        ///TODO:- Does nothing
        font = TTF_OpenFont("Fonts/Roboto.ttf", 24);

    }
    catch(std::exception &e){

        std::ofstream outFile;

        outFile.open("errorLog.txt");

        if(outFile.is_open()){

            outFile << e.what() << std::endl;

            outFile.close();
        }
    }
}

State::State() {

this->quit = false;
keyTimeMax = 0.5f;
keyTime = 0.f;

    getData()->mainText = std::make_shared<GUI::Text>(5, 5, 89, 60, true);

    getData()->dynamicText = std::make_shared<GUI::Text>(false);
    getDynamicText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));
    getDynamicText()->clearText();

    getData()->enemyText = std::make_shared<GUI::Text>(false);
    getEnemyText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));
    getEnemyText()->clearText();
    getEnemyText()->setColour(255, 0, 0, 0);

    getMainText()->setFontSize(20);
    getDynamicText()->setFontSize(20);
    getEnemyText()->setFontSize(20);

    getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
    getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));

    menu = std::make_shared<GUI::Menu>();

}

State::~State(){

    //getData()->dynamicText->clearText();
    //getData()->enemyText->clearText();
    if(getActiveCharacter() != nullptr){

        getMainText()->setString(getActiveCharacter()->getStatsAttributeScreen(), true, GUI::p2pY(120));
    }
}

void State::setData(StateData& stateData){

    StateData::GetInstance()->currentState = 0;
}

bool State::getQuit(){

    return this->quit;
}

void State::refreshGUI(){

        getData()->mainText->refreshGUI();
        getDynamicText()->refreshGUI();

        //getData()->enemyText = std::make_shared<GUI::Text>();
        getEnemyText()->refreshGUI();
        getEnemyText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));
        getDynamicText()->setPosition(GUI::p2pX(20), GUI::p2pY(50));

        getMainText()->setFontSize(20);
        getDynamicText()->setFontSize(20);
        getEnemyText()->setFontSize(20);
        //getEnemyText()->clearText();

        getEnemyText()->setPosition(GUI::p2pX(55), GUI::p2pY(40));
    getDynamicText()->setPosition(GUI::p2pX(55), GUI::p2pY(30));

        menu->refreshGUI();

    //TODO Add buttons & menu to state to allow GUI refresh.... OR override
}


const bool State::getKeyTime(){

    if(keyTime > keyTimeMax){

        keyTime = 0.f;

        return true;
    }

    return false;
}


void StateData::push_state(std::shared_ptr<State> s){

    this->states->push_back(s);
    currentState++;
}

void StateData::pop_state(){

    states->pop_back();
    currentState--;
}

void State::updateEvents(SDL_Event& e){

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

        Engine::GetInstance()->PopState();

        return;
    }

    if(e.type == SDL_MOUSEMOTION){

        if(!SDL_ShowCursor(SDL_QUERY)){

            SDL_ShowCursor(SDL_ENABLE);
        }
    }
}

void StateData::clearCharacters(){

    ///characters.clear();
}

int State::getRandomValue(int low, int high){

    // Use std::random_device to obtain a seed for the random number generator
                std::random_device rd;

                // Use std::mt19937 as the random number generator
                std::mt19937 gen(rd());

                // Use std::uniform_int_distribution to generate random indices
                std::uniform_int_distribution<> dis(low, high);

                // Generate a random index
                int randomIndex = dis(gen);

                // Access the corresponding element in the set
//                int randomValue = numbers[randomIndex];

                return randomIndex;
}

void State::loadCharacters(){
    std::string fileName = "characters.txt";
    ifstream inFile(fileName);
    StateData::GetInstance()->characters.clear();


    string name = "";
    int disTravel = 0;
    int gold = 0;
    int level = 0;
    int exp = 0;
    //int str = 0;
    //int vit = 0;
    //int dex = 0;
    //int intel = 0;
    int hp = 0;
    int stamina = 0;
    int statPoints = 0;
    int skillPoints = 0;
    int corrupt = 0;

	//ITEMS
	Inventory tempItems;

	int itemType = -1;
	int defence = 0;
	int type = 0;
	int damageMin = 0;
	int damageMax = 0;
	string itemName = "";
	int itemLevel = 0;
	int buyValue = 0;
	int sellValue = 0;
	int rarity = 0;

	//Factions
	int black = 0;
    int white = 0;
    int red = 0;
    int blue = 0;
    int green = 0;
    int brown = 0;
    int aqua = 0;
    int purple = 0;

    int vit;
    int str;
    int dex;
    int agi;
    int intel;
    int charis;
    int luck;

    string line = "";
    stringstream strs;


    if(inFile.is_open()){
		while (getline(inFile, line)) {
			strs.str(line);
			strs >> name;
			strs >> disTravel;
			strs >> level;
			strs >> hp;
			strs >> exp;
			strs >> gold;
			strs >> corrupt;
			strs >> vit;
			strs >> str;
			strs >> dex;
			strs >> agi;
			strs >> intel;
			strs >> charis;
			strs >> luck;

			auto temp = std::make_shared<Player> (name, disTravel, gold, level, exp,
				vit, str, dex, agi, intel, charis, luck, hp,
                corrupt, true);


			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (

				strs >> black
				>> white
				>> red
				>> blue
				>> green
				>> brown
				>> aqua
				>> purple
				)

				///HERE FAC
				temp->loadFactions(black, white, red, blue, green, brown, aqua, purple);

            strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);

			while (strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> damageMin
				>> damageMax
				>> type) {

				if (itemType == itemTypes::WEAPON) {
					Weapon activeWeapon(type, damageMin, damageMax, itemName, itemLevel, 0, 0, rarity);
					auto awv = make_shared<Weapon>(activeWeapon);
					temp->setWeapon(awv);
				}
			}


			//ACTIVE ITEMS
			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defence
				>> type) {
				if (itemType == itemTypes::ARMOUR) {
					Armour activeArm(type, defence, itemName, itemLevel, 0, 0, rarity);
					auto avv = make_shared<Armour>(activeArm);
					int type = avv->getType();

					switch (type) {
					case HEAD:
						temp->setArmourHead(avv);
						break;

					case CHEST:
						temp->setArmourChest(avv);
						break;

					case ARMS:
						temp->setArmourArms(avv);
						break;

					case LEGS:
						temp->setArmourLegs(avv);
						break;

					default:
						break;
					}
				}

			}

			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (

				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> damageMin
				>> damageMax
				>> type
				) {

				Weapon tempWeapon(type, damageMin, damageMax, itemName, itemLevel, 0, 0, rarity);
				auto wv = make_shared<Weapon>(tempWeapon);
				tempItems.addItemVectorSmart(wv);
				temp->addItem(wv);
			}


			strs.clear();
			line.clear();
			getline(inFile, line);
			strs.str(line);
			while (
				strs >> itemType
				>> itemName
				>> itemLevel
				>> rarity
				>> defence
				>> type
				) {
				Armour tempArmour(type, defence, itemName, itemLevel, 0, 0, rarity);
				auto av = make_shared<Armour>(tempArmour);
				tempItems.addItemVectorSmart(av);
				temp->addItem(av);
			}


                StateData::GetInstance()->characters.push_back(temp);

				///cout << "Character: " << temp->getName() << " loaded" << "\n";
				temp->setInv(tempItems);
				//cout << "Loaded Inv: " << temp.getInvAsString() << "\n";
				//cout << "tempItems: " << tempItems.getInvAsString() << "\n";
				strs.clear();
               /* for(int i = 0; i < characters.size(); i++){
                    cout << this->characters[i].getStatsAsString() << endl;
					cout << "Loaded Character: " << this->characters[i].getName() << endl;
                }*/

            }
    }
    else{

        Engine::GetInstance()->PopState();

        return;
    }
    inFile.close();

    if(StateData::GetInstance()->characters.size() < 0){
        throw "ERROR LOADING FILE!";
    }
}

void State::saveCharacters()
{

    std::string fileName = "characters.txt";

    std::ofstream outFile(fileName);

 //   void Game::saveCharacters(){
    if(outFile.is_open()){
        for(unsigned i = 0; i < StateData::GetInstance()->characters.size(); i++){
            outFile << StateData::GetInstance()->characters[i]->getStatsAsString() << " ";
			outFile << getData()->characters[i]->saveAttributes() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getFactionStrSave() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getEquippedWeapon() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getEquippedArmour() << "\n";
			outFile <<	StateData::GetInstance()->characters[i]->getInvAsStringSave() << "\n";
		}
    }

    outFile.close();
	//cout << "Game Saved!\n\n";
}


void StateData::createCamera(int maxSize){

    int h = 0;
    int w = 0;

    SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, &h);

    this->camera = std::make_unique<Camera>(0,0,w,h, maxSize);
}

void StateData::moveCamera(int direction, int axis){


    switch(direction){

    case LEFT:
        camera->moveCamera(LEFT, axis);
        break;

    case RIGHT:
        camera->moveCamera(RIGHT, axis);
        break;

    case UP:
        camera->moveCamera(UP, axis);
        break;

    case DOWN:
        camera->moveCamera(DOWN, axis);
        break;

    default:
        camera->moveCamera(FREEZE, axis);
        break;
    }

}

void StateData::moveCam2(int dir, float time)
{
    switch(dir){

    case LEFT:
        camera->moveCam2(LEFT, time);
        break;

    case RIGHT:
        camera->moveCam2(RIGHT, time);
        break;

    case UP:
        camera->moveCam2(UP, time);
        break;

    case DOWN:
        camera->moveCam2(DOWN, time);
        break;

    default:
        camera->moveCam2(FREEZE, time);
        break;
}
}

void StateData::stopCam2(int dir, float time){

    switch(dir){

    case LEFT:
        break;
    }
}



SDL_Rect StateData::getCamera(){

    return camera->getCamera();
}

void StateData::updateCamera(){

    this->camera->update();
}


