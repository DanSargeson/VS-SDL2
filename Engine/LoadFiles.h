#pragma once
#include "Engine.h"

class LoadFiles{

    public:

        LoadFiles(std::string filename, int type = -1);
       // virtual ~LoadFiles();

        int loadFaction();
        std::string loadDialogue();
        std::string loadRandomDialogue();
        std::string loadFactionDialogue(int id);
        std::string loadQuestDialogue();
        std::vector<std::string> loadPlayerOptions();
        std::string loadName();

    private:

        std::string m_filename;
        int m_faction;
        std::string m_name;
        std::string m_dialogue;
        std::vector<std::string> m_dialogueArray;
};
