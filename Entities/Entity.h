#ifndef ENTITY_H
#define ENTITY_H

#include <memory>

class AttributeComponent;
class SkillComponent;
class FactionComponent;
class DialogueComponent;
class AttackComponent;
//DEFENCE COMPONENT HERE
class Item;
#include "Inventory.h"

class Entity{

private:

	void InitVariables();

protected:


	//EQUIPPED ITEMS
	std::shared_ptr<class Weapon> activeWeapon;
	std::shared_ptr<class Armour> activeHead;
	std::shared_ptr<class Armour> activeChest;
	std::shared_ptr<Armour> activeArms;
	std::shared_ptr<Armour> activeLegs;
	std::shared_ptr<Armour> activeTool;

	std::shared_ptr<AttributeComponent> attributeComponent;
	std::shared_ptr<SkillComponent> skillComponent;
	std::shared_ptr<FactionComponent> factionComponent;
	std::shared_ptr<DialogueComponent> dialogueComponent;
	std::shared_ptr<AttackComponent> attackComponent;

	int faction;

	std::vector<class Component*> mComponents;
	class Inventory inv;

	std::string m_name;

	static std::vector<std::string> entityNames;

public:

	Entity();
	virtual ~Entity();

	//Component Functions

	//Attribute functions

	void initNames();

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

	int getExp();
	int getExpNext();


	int getLevel();

	int getHP();
	int getHPMax();

	void loseDurability();


	//bool checkEntityCollision(Entity* entity);

	std::string getFactionStr();
	std::string getFactionStrSave();
	std::string getFactionName(int faction);

	void calculateSkills();

	void updateStats(bool s);

	//std::vector<std::string> getDialogueOptions();

	void setCharacterName(std::string name);

	std::string getItemString(int index);

	int getRep(int faction);

	bool isAlive();

	void setHP(int l);

//	virtual int getCurrentMapID() = 0;
//	virtual void setMapID(int id);

	void createAttributeComponent(const unsigned level, const bool reset, bool enemy = false);
	void createSkillComponent();
	void createFactionComponent();
	void createDialogueComponent();
	void createAttackComponent();

    std::shared_ptr<AttributeComponent> getAttributeComponent() { return this->attributeComponent; }
	std::shared_ptr<SkillComponent> getSkillComponent() { return skillComponent; };
	std::shared_ptr<FactionComponent> getFactionComponent() { return factionComponent; }
	std::shared_ptr<DialogueComponent> getDialogueComponent() { return dialogueComponent; };
	std::shared_ptr<AttackComponent> getAttackComponent() { return attackComponent; }


	std::string displaySkills();

	void resetHP();

    std::string getName() { return m_name; }

	int getDamage();
	int getDefence();

	int getMaxDamageWithWeapon();
	int getMinDamageWithWeapon();

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

	bool getDialogueActive();
	void setDialogueActive(bool n);
	void setDialogueText(std::string);
	void renderDialogue();

	//virtual int getDirection() = 0;

	std::shared_ptr<Weapon> getActiveWeapon();

	std::shared_ptr<Armour> getActiveHead();
	std::shared_ptr<Armour> getActiveChest();
	std::shared_ptr<Armour> getActiveArms();
	std::shared_ptr<Armour> getActiveLegs();

	virtual void update();
	virtual void render();
};

#endif

