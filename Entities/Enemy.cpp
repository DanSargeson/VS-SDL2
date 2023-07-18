#include "Enemy.h"

vector<string> Enemy::enemyNames;

void Enemy::initNames() {
	Enemy::enemyNames.push_back("Goblin");
	Enemy::enemyNames.push_back("Warlock");
	Enemy::enemyNames.push_back("Wolf");
	Enemy::enemyNames.push_back("Ghost");
	Enemy::enemyNames.push_back("Skeleton");
	Enemy::enemyNames.push_back("Rat");
	Enemy::enemyNames.push_back("Harpy");
	Enemy::enemyNames.push_back("Gremlin");
	Enemy::enemyNames.push_back("Berserker");
}


Enemy::Enemy(int level){
    initNames();
	this->name = Enemy::enemyNames[rand() % Enemy::enemyNames.size()];
    this->level = level; //TODO CHANGE BACK
    this->hpMax = level * 3;
    this->hp = this->hpMax;
    this->damageMin = this->level * 1;
    this->damageMax = this->level * 2;
    this->dropChance = rand() % 100 + 1;
    this->defence = rand() % this->level*2 + 1;
    this->accuracy = rand() % this->level*2 + 1;
}

Enemy::~Enemy(){
}

string Enemy::getAsString() const{
    return name + " Level: " + to_string(this->level) + "\n" +
           "HP: " + to_string(this->hp) + "/" + to_string(this->hpMax) + "\n" +
           "Damage: " + to_string(this->damageMin) + " - " + to_string(this->damageMax) + "\n" +
           "Defence: " + to_string(this->defence) + "\n" +
           "Accuracy: " + to_string(this->accuracy) + "\n" +
           "Drop Chance: " + to_string(this->dropChance) + "\n";
}

int Enemy::takeDamage(int damage) {
	damage -= this->defence;
	this->hp -= damage;
	if (this->hp <= 0) {
		this->hp = 0;
	}

	return damage;
}
