
#include "character.h"
#include "position.h"

#include <iostream>

Character::Character(Position pos) {
	this->setPosition(pos);
}

Character::~Character() {}


int Character::CalculateDamage(Stats attacker, Stats defender) {
	float atk =  attacker.Atk;
	float def = defender.Def;
	float damage = (ceil((100 / (100 + def) ) * atk));
	return static_cast<int>(damage);

}

//Basic combat:

bool Character::Move(Position pos) {
	this->position = pos;
	return true;
}

bool Character::Attack(Character & target) {
	target.beStruckBy(*this);
	int TargetHP = target.getStats().HP;
	if (TargetHP <= 0) {
		this->addGold(target.getGold());
	}
	return true;
}

bool Character::beStruckBy(Character & attacker) {
	int damage = this->CalculateDamage(attacker.getStats(), this->getStats());
	this->stats.addHP(-damage);
	std::cout << attacker.getName().name << " dealt " << damage << " damage to " << this->getName().name << std::endl;
	return true;
}

bool Character::TurnStart() {
	return true;
	//Does nothing special
}

//Getters/Setters

Stats Character::getStats() {
	return stats;
}
void Character::setStats(Stats stat) {
	stats = stat;
}

Position Character::getPosition() {
	return position;
}

void Character::setPosition(Position pos) {
	this->position = pos;
}

Name Character::getName() {
	return name;
}

void Character::setName(Name nam) {
	name = nam;
}

int Character::getGold() {
	return goldValue;
}

void Character::setGold(int set) {
	goldValue = set;
}

void Character::addGold(int add) {
	goldValue += add;
}

