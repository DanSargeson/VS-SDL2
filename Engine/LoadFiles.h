#pragma once
#include "Engine.h"

class LoadFiles{

    public:

        LoadFiles(std::string filename);

        int loadFaction();
        std::string loadDialogue();
        std::string loadName();

    private:

        std::string m_filename;
        int m_faction;
        std::string m_name;
        std::string m_dialogue;
};
