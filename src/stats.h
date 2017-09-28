#ifndef  _STATS_
#define _STATS_
//Struct for carrying Base stats
struct Stats {
	int HP;
	int MaxHP;
	int Atk;
	int Def;

	Stats() : HP{ 0 }, MaxHP{ 0 }, Atk{ 0 }, Def{ 0 } {}
	Stats(int hp, int maxhp, int atk, int def) : HP{ hp }, MaxHP{ maxhp }, Atk{ atk }, Def{ def } {}


	void reset() {
		HP = 0;
		MaxHP = 0;
		Atk = 0;
		Def = 0;
	}


	void CheckNoBelowZero() {
		if (HP < 0) {
			HP = 0;
		}
		if (MaxHP < 0) {
			MaxHP = 0;
		}
		if (Atk < 0) {
			Atk = 0;
		}
		if (Def < 0) {
			Def = 0;
		}
	}

	void addHP(int set) { //Sets with limits
		HP += set;
		if (HP <= 0) {
			HP = 0;
		}
		if (HP >= MaxHP) {
			HP = MaxHP;
		}
	}


	Stats  operator* (const int amount) const {
		Stats newStats;
		newStats.MaxHP = MaxHP * amount;
		newStats.HP = HP * amount;
		newStats.Atk = Atk * amount;
		newStats.Def = Def * amount;
		return  newStats;
	}
	Stats  operator* (const float amount) const {
		Stats newStats;
		newStats.MaxHP = static_cast<int> (MaxHP * amount);
		newStats.HP = static_cast<int> (HP * amount);
		newStats.Atk = static_cast<int> (Atk * amount);
		newStats.Def = static_cast<int> (Def * amount);
		return  newStats;
	}



};

#endif





