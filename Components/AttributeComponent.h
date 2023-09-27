#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Component.h"

enum ATTRIBUTE {

	VITALITY = 0,
	STRENGTH,
	DEXTERITY,
	AGILITY,
	INTELLIGENCE,
	CHARISMA,
	LUCK,
	TOTAL_ATTRIBUTES
};

class AttributeComponent : public Component{

public:

	AttributeComponent(class Entity* owner, unsigned level, bool reset, bool enemy = false);
	virtual ~AttributeComponent();

	void increaseAttribute(int attr);
	void decreaseAttribute(int attr);

	void loadAttribute(int level, float xp, int hp, int vit, int str, int dex, int agi, int intel, int charis, int luck);

	//Accessors
	int getHP();
	int getHPMax();

	float getEXP();
	float getEXPNext();

	unsigned getLevel();

	//Functions
	void gainEXP(const float exp);
	void loseEXP(const float exp);

	inline void setHP(int hp) { mHp = hp; }

	void gainHP(const int hp);
	void loseHP(const int hp);

	void calculateNextEXP();
	void updateStats(const bool reset);
	void updateLevel();
	void update();

	void assignRandomAttributes(int level);

	inline bool levelUp() { return mHasLevelled; }
	inline void turnLevelOff() { mHasLevelled = false; }

	std::string debugPrint();

	int getAttribute(const int attr);

private:

	unsigned mLevel;
	float mExp;
	float mExpNext;
	unsigned mAttributePoints;

	float baseEXP;

	std::vector<int> mAttributes;

	int mHp;
	int mHpMax;

	bool mHasLevelled;

};

#endif
