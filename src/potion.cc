#include "potion.h"
#include "position.h"

#include <string>
using namespace std;

#include "myrand.h"
#include <iostream>

//Indicates amount
Potion::Potion(Position pos) : Item{ pos } {
	this->name.symbol = 'P';
	this->makeRandomPotion();
}
Potion::Potion(Position pos, PotionType pot) : Item{ pos } {
	this->name.symbol = 'P';
	AssignThisPotion(pot);
}

Potion::~Potion() { }

void Potion::makeRandomPotion() {
	Random r;
	int i = (int) PotionType::Count - 1;
	this->AssignThisPotion( static_cast<PotionType>(r.Range(0, i+1)));

}

//NOTE: To add a new potion type, add it to the PotionType enum, and write its implementation here
void Potion::AssignThisPotion(PotionType pot) {


	if (pot == PotionType::RestoreHealth) {
		this->name.name = "Restore Health";
		buff.HP = 10;
	}
	else if (pot == PotionType::BoostAtk) {
		this->name.name = "Boost Atk";
		buff.Atk = 5;
	}
	else if (pot == PotionType::BoostDef) {
		this->name.name = "Boost Def";
		buff.Def = 5;
	}
	else if (pot == PotionType::PoisonHealth) {
		this->name.name = "Poison Health";
		buff.HP = -10;
	}
	else if (pot == PotionType::WoundAtk) {
		this->name.name = "Wound Atk";
		buff.Atk = -5;
	}
	else if (pot == PotionType::WoundDef) {
		this->name.name = "Wound Def";
		buff.Def = -5;
	}

}

Stats Potion::getStats() const {
	return this->buff;
}

void Potion::setStats(Stats stats) {
	this->buff = stats;
}

Stats  operator+ (const Potion &can, Stats & stat)  {
	Stats newStats;
	Stats potStats = can.getStats();

	Stats temp = stat;
	temp.addHP(potStats.HP);
	newStats.HP = temp.HP;

	newStats.MaxHP = potStats.MaxHP + stat.MaxHP;
	newStats.Atk = potStats.Atk + stat.Atk;
	newStats.Def = potStats.Def + stat.Def;
	return newStats;

}

Stats  operator+ (Stats & stat, const Potion &can)  {
	Stats newStats;
	Stats potStats = can.getStats();

	Stats temp = stat;
	temp.addHP(potStats.HP);
	newStats.HP = temp.HP;

	newStats.MaxHP = potStats.MaxHP + stat.MaxHP;
	newStats.Atk = potStats.Atk + stat.Atk;
	newStats.Def = potStats.Def + stat.Def;
	return newStats;
}
