#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

class Enemy{

private:
	string name;
    int hp;
    int hpMax;
    int level;
    int damageMin;
    int damageMax;
    float dropChance;
    int defence;
    int accuracy;

public:
    Enemy(int level = 0);
    virtual ~Enemy();

    inline bool isAlive() { return this->hp > 0;}
    string getAsString() const;
	int takeDamage(int damage);

	inline int getLevel() const { return this->level; }
    inline int getDamage() const { return this->damageMin + rand() % ((this->damageMax + 1) - this->damageMin); }
	inline int getDamageMin() const { return this->damageMin; }
	inline int getDamageMax() const { return this->damageMax; }
	inline int getExp() const { return this->level * 100; }
	inline int getHp() const { return this->hp; }
	inline int getHpMax() const { return this->hpMax; }
	inline int getDefence() const { return this->defence; }
	inline int getAccuracy() const { return this->accuracy; }
	inline string getName() { return this->name; }

	static vector<string> enemyNames;
	static void initNames();
};

#endif // ENEMY_H
