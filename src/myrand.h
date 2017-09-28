#ifndef _MYRAND_
#define _MYRAND_

#include <cstdlib>
#include <time.h>       /* time */

struct Random {

	Random() {
	}

	int Range(int min, int max) //range : [min, max)
	{
		if (min < 0 || max < 0 || (max == 0 && min == 0)) return 0;
		static bool firsttime = true;
		if (firsttime){
			srand(time(NULL)); //seeds (generates rnadom number) on first time
			firsttime = false;
		}
		return min + rand() % (max + 1 - min) ;
	}


};

#endif

