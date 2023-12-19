#include "Enemy.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include <random>

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


Enemy::Enemy(int lvl) : Entity(){
    initNames();
	this->name = Enemy::enemyNames[rand() % Enemy::enemyNames.size()];
    //this->level = rand() % (level - 2);
    level = lvl;

    unsigned seed;
    std::default_random_engine generator;
    seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
     generator.seed(seed);
//    std::uniform_int_distribution<int> numEnemiesDistribution(lvl-2, lvl);
//     this->level = numEnemiesDistribution(generator);
     if(level <= 0){

        level = 1;
     }
//     attributeComponent
//    this->hpMax = level * 3;
//    this->hp = this->hpMax;
//    this->damageMin = this->level * 1;
//    this->damageMax = this->level * 2;
//    this->dropChance = rand() % 100 + 1;
//    this->defence = rand() % this->level*2 + 1;
//    this->accuracy = rand() % this->level*2 + 1;

    this->createAttributeComponent(this->level, true, true);
    //attributeComponent->updateLevel();
    createSkillComponent();
    skillComponent->calculateSkills(attributeComponent);
    createAttackComponent(skillComponent, attributeComponent);
}

Enemy::~Enemy(){

 //   attributeComponent.re
 //removeComponent(attributeComponent);
 //removeComponent(skillComponent);
}

int Enemy::getExp() const{

    return attributeComponent->getEXPNext();
}

string Enemy::getAsString() const{
    return name + " Level: " + to_string(this->level) + "\n" +
           "HP: " + to_string(this->hp) + "/" + to_string(this->hpMax) + "\n" +
           "Damage: " + to_string(this->damageMin) + " - " + to_string(this->damageMax) + "\n" +
           "Defence: " + to_string(this->defence) + "\n" +
           "Accuracy: " + to_string(this->accuracy) + "\n" +
           "Drop Chance: " + to_string(this->dropChance) + "\n" +
           "EXP Next: " + std::to_string(attributeComponent->getEXPNext()) + "\n";
}

int Enemy::takeDamage(int damage) {
	damage -= this->defence;

	if(damage <= 0){
        damage = 1;
	}
	this->hp -= damage;
	if (this->hp <= 0) {
		this->hp = 0;
	}

	return damage;
}
