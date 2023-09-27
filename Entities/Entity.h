#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

class AttributeComponent;
class SkillComponent;
class FactionComponent;
//#include "DialogueComponent.h"
class AttackComponent;
//DEFENCE COMPONENT HERE
class Item;
#include "Inventory.h"

class Entity{

private:

	void InitVariables();

protected:


	//EQUIPPED ITEMS
	std::shared_ptr<class Item> activeWeapon;
	std::shared_ptr<class Item> activeHead;
	std::shared_ptr<class Item> activeChest;
	std::shared_ptr<Item> activeArms;
	std::shared_ptr<Item> activeLegs;
	std::shared_ptr<Item> activeTool;

	std::shared_ptr<AttributeComponent> attributeComponent;
	std::shared_ptr<SkillComponent> skillComponent;
	std::shared_ptr<FactionComponent> factionComponent;
	//std::shared_ptr<DialogueComponent> dialogueComponent;
	std::shared_ptr<AttackComponent> attackComponent;

	int faction;

	std::vector<class Component*> mComponents;
	class Inventory inv;

public:

	Entity();
	virtual ~Entity();

	//Component Functions

	//Attribute functions
	void loseHP(int hp);
	void gainHP(int hp);
	void loseXP(float xp);
	void gainXP(float xp);

	void loseRep(int faction, int rep);
	void gainRep(int faction, int rep);

	int getSkill(int skill);
	int getFaction(int faction);
	int getAttribute(int attribute);
	int checkDurability();
	float getAttributeFloat(int attribute);


	int getLevel();

	int getHP();
	int getHPMax();

	void loseDurability();


	//bool checkEntityCollision(Entity* entity);

	std::string getFactionStr();
	std::string getFactionName(int faction);

	//std::vector<std::string> getDialogueOptions();

	std::string getItemString(int index);

	bool isAlive();

//	virtual int getCurrentMapID() = 0;
//	virtual void setMapID(int id);

	void createAttributeComponent(const unsigned level, const bool reset, bool enemy = false);
	void createSkillComponent();
	void createFactionComponent();
//	void createDialogueComponent();
	void createAttackComponent(std::shared_ptr<SkillComponent> skillComponent, std::shared_ptr<AttributeComponent> attributeComponent);

    std::shared_ptr<AttributeComponent> getAttributeComponent() { return this->attributeComponent; }
	std::shared_ptr<SkillComponent> getSkillComponent() { return skillComponent; };
	std::shared_ptr<FactionComponent> getFactionComponent() { return factionComponent; }
	//std::shared_ptr<DialogueComponent> dialogueComponent;
	std::shared_ptr<AttackComponent> getAttackComponent() { return attackComponent; }

	void resetHP();


	int getDamage();
	int getDefence();

	//const virtual sf::Vector2f& getPosition() const;
	float getPositionXSave();
	float getPositionYSave();
	//const virtual sf::Vector2f getCentre() const;
	//const virtual sf::Vector2i getGridPosition(const int gridSizeI) const;
	//const virtual sf::FloatRect getGlobalBounds() const;
	//const virtual sf::FloatRect getNextPositionBounds(const float& dt) const;

	/*TODO - Refactor at some point*/
	//void createSpriteFromSheet(sf::Texture* texture, float startX, float startY, float width, float height);


	//functions

	//virtual void setPosition(const float x, const float y);
	//virtual void move(const float x, const float y, const float& dt);
	//sf::Vector2f getVelocity();
	//sf::Vector2f getPreviousVelocity();
	//virtual void stopVelocity();
	//virtual void stopVelocityY();
	//virtual void stopVelocityX();



	float calculateDefence();

	/*
		INVETORY FUNCTIONS
	*/

	std::shared_ptr<Item> getItem(int index);
	void removeItem(int index);

	void addComponent(class Component* comp);
	void removeComponent(class Component* comp);
	void updateComponents();

	//virtual int getDirection() = 0;

	virtual void update();
	virtual void render();
};

#endif
