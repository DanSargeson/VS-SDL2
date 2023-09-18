#ifndef SKILLS_H
#define SKILLS_H

#include "Component.h"

enum SKILLS {

	MELEE = 0,
	RANGED,
	DEFENCE,
	ACCURACY,
	MAGIC,
	STEALTH,
	LOCKPICKING,
	PERSUASION,
	PERCEPTION
};

class SkillComponent : public Component{

public:

	SkillComponent(Entity* owner);
	~SkillComponent();

	int getSkill(const unsigned int skill);
	void gainExp(const unsigned int skill, const int xp);

	void increaseSkill(int skill);
	void loadSkills(int skill, int value);

	std::string getSkillName(int skill);

	void assignRandomSkills(int level);
	void calculateSkills(class AttributeComponent& ac);

private:

	class Skill {

	private:
		int skillType;
		int level;
		int levelCap;
		float exp;
		float expNext;

	public:
		Skill(int type) {

			skillType = type;
			level = 1;
			level = 100;
			exp = 0;
			expNext = 100;
		}

		~Skill() {}

		//Accessors
		const int& getType() { return skillType; }
		const int& getLevel() { return level; }
		const float& getExp() { return exp; }
		const float& getExpNext() { return expNext; }

		//Modifiers
		void setLevel(int lvl) { level = lvl; }
		void setLevelCap(int cap) { levelCap = cap; }

		void gainExp(const int xp) {

			exp += xp;
			updateLevel();
		}

		void loseExp(const int xp) {

			exp -= xp;

			if (exp < 0) {

				exp = 0;
			}
		}

		void updateLevel() {

			if (level < levelCap) {

				while (exp < expNext) {

					if (level < levelCap) {

						level++;
						exp = 0.f;
						expNext = static_cast<float>(std::pow(level, 2)) + static_cast<float>(level * 10) + static_cast<float>(level * 2);
					}
				}
			}
		}

		void update() {}
	};

	std::vector<Skill> mSkills;
};

#endif

