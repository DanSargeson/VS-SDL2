#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Player.h"
#include "Enemy.h"
#include "GUI.h"
#include "Camera.h"
//#include "SaveData.h"

class StateData{

public:

    static StateData* GetInstance(){       //Checks if object is created, if true returns object if false create object

            return s_Instance = (s_Instance != nullptr) ?  s_Instance : new StateData();
        }

    //SHOULD COME UNDER THE ENGINE
///    SDL_Window* window;
///    SDL_Renderer* renderer;
    //std::unordered_map<std::string, int>* supportedKeys;


    //int cameraVelocity;

    //Camera, same as old or use a new method??
    std::unique_ptr<Camera> camera;

    void initFonts();



    void push_state(std::shared_ptr<class State> s);
    void pop_state();

    inline std::shared_ptr<Player> getActiveCharacter(){ if(!characters.empty()) return characters[activeCharacter]; }

    //TO BE DETERMINED
    void createCamera(int maxSize);
    void moveCamera(int direction, int axis);
    void moveCam2(int dir, float time);
    void stopCam2(int dir, float time);

    void clearCharacters();

    void updateCamera();

    SDL_Rect getCamera();



    std::string saveName;

    int activeCharacter;
    std::vector<std::shared_ptr<Player>> characters;

    std::vector<std::shared_ptr<class State>>* states;

    //SDL_Rect camera;

    bool gameEvent = false;
    int menuType = -1;
    int gridSize = 64;
    float gridSizeF = 64.0;

    int currentState = 0;

    TTF_Font* font;

  ///  std::unique_ptr<class SaveData> saveData;

    std::shared_ptr<class TileMap> currentMap;

    inline void setTutorial(bool t) { tutorial = t; }
    inline bool getTutorial() { return tutorial; }

    std::vector<Enemy*> enemies;

    std::string mainTextStr;
    bool clickToNext = false;

   //Need to think how best to get text to work
    std::shared_ptr<GUI::Text> mainText;
    std::shared_ptr<GUI::Text> dynamicText;
    std::shared_ptr<GUI::Text> enemyText;

    bool next = false;
    bool quit = false;
    bool gameOver = false;
    bool tutorial = false;

private:
    StateData() { };

     static StateData* s_Instance;



};

class State{

public:

    friend StateData;

    State();
    virtual ~State();

    void setData(StateData& StateData);

    virtual void update(const float &dt) = 0;
   virtual void updateEvents(SDL_Event &e) = 0;
    virtual void render() = 0;


    bool getQuit();
    const bool getKeyTime();
    inline void endState() { quit = true; }
    inline void pauseState() { paused = true; }
    inline void unpauseState() { paused = false; }
    inline bool isPaused() { return paused; }

    void saveCharacters();

private:

protected:

   // StateData* mStateData;
    std::unordered_map<std::string, int> keyBinds;
    bool quit;
    bool paused;
    float keyTime;
    float keyTimeMax;

    bool gameOver;
    bool resolutionChange;
};

#endif // STATE_H

