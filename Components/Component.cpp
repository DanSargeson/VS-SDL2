#include "stdafx.h"
#include "Component.h"
#include "Entity.h"

Component::Component(Entity* owner, int updateOrder) : mOwner(owner), mUpdateOrder(updateOrder) {

	mOwner->addComponent(this);
}

Component::~Component(){

//	if (mOwner != nullptr) {
//	if (mOwner) {
//
//		mOwner->removeComponent(this);
//	}
//}
}

void Component::update()
{
}

void Component::processInput()
{
}

void Component::render(SDL_Renderer * target)
{
}
