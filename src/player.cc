#include "player.h"
#include "potion.h"
#include "stats.h"

#include <iostream>
using namespace std;

Player::Player(Position pos) : Character{ pos } { this->goldValue = 0; }
Player::~Player() {}

void Player::usePotion(Potion & pot) {
	this->stats = this->stats + pot;
	cout << this->name.name << " used a " << pot.getName().name << " potion!" << endl;
	this->stats.CheckNoBelowZero();
}

Stats Player::getBaseStats() {
	return this->baseStats;
}

void Player::revertToBaseStats() {
	//Stats & playerStats = this->getStats();

	stats.Atk = baseStats.Atk;
	stats.Def = baseStats.Def;
}
