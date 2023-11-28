#include "LoadFiles.h"


LoadFiles::LoadFiles(std::string filename) : m_filename(filename){

    //Open a file from

    ifstream inFile(m_filename);

    int fact = -1;
    std::string dialogue;

    std::string line = "";
    stringstream strs;

    if(inFile.is_open()){

        while(getline(inFile, line)){

            strs.str(line);
            strs >> m_faction;
            strs.clear();
            line.clear();

            getline(inFile, line);
            strs.str(line);
            strs >> m_name;
            strs.clear();
            line.clear();

            getline(inFile, line);
            strs.str(line);
            // Replace "\n" with actual newline characters
            size_t found = line.find("\\n");
            while (found != std::string::npos) {
                line.replace(found, 2, "\n");
                found = line.find("\\n", found + 1);
            }
            m_dialogue = line;
            strs.clear();
            line.clear();
        }

        inFile.close();
    }
}

int LoadFiles::loadFaction(){

    return m_faction;
}

std::string LoadFiles::loadDialogue(){

    return m_dialogue;
}

string LoadFiles::loadName(){

    return m_name;
}

