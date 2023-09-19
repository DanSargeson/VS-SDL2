#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "Entity.h"



using namespace std;

class Player : public Entity{
private:
	Inventory inventory;
	Weapon weapon;
//	shared_ptr<Item> activeWeapon;
//	shared_ptr<Item> activeHead;
//	shared_ptr<Item> activeChest;
//	shared_ptr<Item> activeArms;
//	shared_ptr<Item> activeLegs;
	Armour armourHead;
	Armour armourChest;
	Armour armourArms;
	Armour armourLegs;
	int gold;
	int distanceTravelled;

//	string name;
//	int level;
//	int exp;
//	int expNext;
//	int hp;
//	int hpMax;
//	int stamina;
//	int staminaMax;
//	int damageMin;
//	int damageMax;
//	int defence;
//	int accuracy;
//	int luck;
//
//	int strength;
//	int vitality;
//	int dexterity;
//	int intelligence;
//
//	int statPoints;
//	int skillPoints;

	int corruption;

public:
    Player();
    Player(string name, int dt);
    Player(string n, int dt, int g, int lvl, int exp, int str, int vit, int dex, int intel, int hp,
              int stam, int stPoint, int skPoint, int corr);
    virtual ~Player();

    //Functions
    void initialise(string name);
    std::string printPlayerDetails();
    string getStatsAsString() const;
    string getStatsAsStringNEW();
	string getInvAsString();
	string getInvAsStringSave();
	std::vector<std::string> getInvAsVec();
    void levelUp();
    void updateStats();
	void addStat(int stat, int value);
	int takeDamage(int damage);
	void equipItem(int index);
	int getDefenceTotal();
	int getDamage();
	int getMinDamageWithWeapon();
	int getMaxDamageWithWeapon();
	string getEquippedWeapon();
	string getEquippedArmour();
	inline shared_ptr<Item> findItem(int index) { index--; return this->inventory.findItemSmart(index); }
	inline void removeItem(shared_ptr<Item> w) { this->inventory.removeItemVectorSmart(w); }
	inline void addItem(shared_ptr<Item>item) { this->inventory.addItemVectorSmart(item); }
	inline void getInv() { this->inventory.debugVector(); }
	inline int getInvSize() { return this->inventory.smrtSize(); }
	inline void setInv(Inventory inv) { this->inventory = inv; }
	inline void setWeapon(shared_ptr<Item> w) { this->activeWeapon = w; }
	inline void setArmourHead(shared_ptr<Item> a) { this->activeHead = a; }
	inline void setArmourChest(shared_ptr<Item> a) { this->activeChest = a; }
	inline void setArmourArms(shared_ptr<Item> a) { this->activeArms = a; }
	inline void setArmourLegs(shared_ptr<Item> a) { this->activeLegs = a; }
	inline void increaseCorruption() { corruption++; }

//Accessors
//    inline const string& getName() const { return this->name;}
//    inline const int& getLevel() const { return this->level;}
//    inline const int& getDistanceTravelled() const { return this->distanceTravelled;}
//    inline const int& getExp() const { return this->exp;}
//    inline const int& getExpNext() const { return this->expNext;}
//    inline const int& getHP() const { return this->hp;}
//    inline const int& getHpMax() const { return this->hpMax;}
//    inline const int& getStamina() const { return this->stamina;}
//	//inline const int& getDamage() const { return rand() % this->damageMax + this->damageMin; }
//	inline const int& getDamageMax() const { return this->damageMax;}
//    inline const int& getDamageMin() const { return this->damageMin;}
//    inline const int& getDefence() const { return this->defence;}
//    inline const int& getAccuracy() const { return this->accuracy;}
//	inline const int& getStatPoints() const { return this->statPoints; }
//	inline const int& getGold() const { return this->gold; }
//	inline const bool isAlive() { return this->hp > 0;  }
	inline const int& getCorruption() { return corruption; }


    //modifiers
    inline void setDistanceTravelled(const int &distance) { this->distanceTravelled += distance; }
    inline void travel() { this->distanceTravelled++; }
//    inline void setExp(int exp) { this->exp += exp;}
//	inline void setGold(int gold) { this->gold += gold; }
//	inline void resetHP() { this->hp = this->hpMax; }


};

#endif // Player_H

