#include "State.h"
#include "Engine.h"

//Input* Input::s_Instance = nullptr;
StateData* StateData::s_Instance = nullptr;


void StateData::initFonts(){

    try{

        font = TTF_OpenFont("Fonts/SF Atarian System.ttf", 24);

    }
    catch(std::exception e){

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
}

State::~State(){

}

void State::setData(StateData& stateData){

    StateData::GetInstance()->currentState = 0;
}

bool State::getQuit(){

    return this->quit;
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

void StateData::clearCharacters(){

    ///characters.clear();
}

void State::saveCharacters()
{
    std::string fileName = "characters.txt";
 //   void Game::saveCharacters(){
    ofstream outFile(fileName);
    if(outFile.is_open()){
        for(int i = 0; i < StateData::GetInstance()->characters.size(); i++){
            outFile << StateData::GetInstance()->characters[i]->getStatsAsString() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getEquippedWeapon() << "\n";
			outFile << StateData::GetInstance()->characters[i]->getEquippedArmour() << "\n";
			outFile <<	StateData::GetInstance()->characters[i]->getInvAsStringSave() << "\n";
		}
    }

    outFile.close();
	cout << "Game Saved!\n\n";
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


