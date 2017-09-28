#include "enemy.h"

#include "myrand.h"

#include <iostream>

#include "level.h"

Enemy::Enemy(Position pos, Level * thisLevel) : Character{ pos } {
	this->isHostile = true;
	this->level = thisLevel;
}

Enemy::~Enemy() {
	if (!this->level->getWon()) {
		std::cout << this->getName().name << " has been destroyed!" << std::endl;
		if (this->goldValue > 0) {
			std::cout << this->goldValue << " gold was stolen from " << this->getName().name << "!" << std:: endl;
		}
	}
}

bool Enemy::getIsHostile() {
	return this->isHostile;
}

void Enemy::setIsHostile(bool status) {
	this->isHostile = status;
}

//Note that Randomly moving is based on Level, because you need to check for walls.
int Enemy::getRandomDefaultGoldValue() {
	Random r;
	//int randNum = r.Range(1, 2);
    int randNum = r.Range(1, 2);
	return randNum;
}

bool Enemy::hasHit() {
	Random r;
	//int randNum = r.Range(0, 1);
    int randNum = r.Range(1, 2);

	if (randNum == 2) {
		return false;
	}
	return true;

}

bool Enemy::Attack(Character & target) {
	if (this->hasHit()) {
		target.beStruckBy(*this);
		int TargetHP = target.getStats().HP;
		if (TargetHP <= 0) {
			this->addGold(target.getGold());
		}
	}
	else {
		std::cout << this->name.name << " has missed its attack!" << std::endl;
	}
	return true;
}
