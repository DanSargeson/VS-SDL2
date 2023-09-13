#ifndef COMPONENT_H
#define COMPONENT_H

#include "Engine.h"

class Component{

public:

	Component(class Entity* owner, int updateOrder = 100);
	~Component();

	virtual void update();
	virtual void processInput();

	virtual void render(SDL_Renderer* target);

	int getUpdateOrder() { return mUpdateOrder; }

private:

	class Entity* mOwner;
	int mUpdateOrder;
};

#endif
