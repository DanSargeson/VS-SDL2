#pragma once
#include "Component.h"

class DialogueComponent : public Component{

    public:

        DialogueComponent(Entity* owner);
        virtual ~DialogueComponent();

        bool getTextBoxActive(){ if(text != nullptr) { return text->getActive(); } else return false; }

        void setTextBoxActive(bool n) { text->setActive(n); }

        void render();

    private:

        std::unique_ptr<GUI::textBox> text;
};
