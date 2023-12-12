#include "LoadFiles.h"


LoadFiles::LoadFiles(std::string filename, int type) : m_filename(filename){

    //Open a file from


    ///FUNCTION 1
    if(type == -1){

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
    else if(type <= 3){
            ///FUNCTION 2
             ifstream inFile(m_filename);

            int fact = -1;
            std::string dialogue;

            std::string line = "";
            stringstream strs;

            if(inFile.is_open()){

                while(getline(inFile, line)){

//                    strs.str(line);
//                    strs >> m_faction;
//                    strs.clear();
//                    line.clear();
//
//                    getline(inFile, line);
//                    strs.str(line);
//                    strs >> m_name;
//                    strs.clear();
//                    line.clear();
//
//                    getline(inFile, line);
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

                    m_dialogueArray.push_back(m_dialogue);
                }

                inFile.close();
            }
    }
    else{

        loadFactionDialogue(1);
    }
}

int LoadFiles::loadFaction(){

    return m_faction;
}

std::string LoadFiles::loadDialogue(){

    return m_dialogue;
}

string LoadFiles::loadFactionDialogue(int id)
{
    if(m_filename == "Assets/factionQuests.txt"){

        m_dialogueArray.clear();

        std::ifstream file(m_filename);
        std::vector<std::string> matchingLines;

    std::string line;

     if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return "ERROR";
    }
    while (std::getline(file, line)) {
        // Use a string stream to parse the line
        std::istringstream iss(line);

        // Read the integer at the beginning of the line
        int number = id;
        if (iss >> number) {

        if(number == id){
            // Check if the rest of the line contains the same number
            if (line.find(std::to_string(number)) != std::string::npos) {
                // Store the line in the vector
                m_dialogueArray.push_back(line);
            }
        }
        }
    }

    // Close the file
    file.close();

    return m_dialogueArray[0];
    }
    else{

        return "This is wrong";
    }
}


string LoadFiles::loadQuestDialogue(){

    return m_dialogueArray[0];
}

std::vector<std::string> LoadFiles::loadPlayerOptions()
{

   // New vector excluding the first element
    std::vector<std::string> newVector;

    // Using iterators and insert function
    newVector.insert(newVector.end(), std::next(m_dialogueArray.begin()), m_dialogueArray.end());

    return newVector;
}




std::string LoadFiles::loadRandomDialogue(){

    //m_dialogueArray[];
    return m_dialogueArray[rand() % m_dialogueArray.size()];
}

string LoadFiles::loadName(){

    return m_name;
}

