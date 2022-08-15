#pragma once

#include <cstdlib>
#include <ctime>

namespace GEP
{
	static bool isFirstTimeSeed = false;

	int RandomRange(int min, int max)
	{
		if (!isFirstTimeSeed)
		{
			srand(time(0));
			isFirstTimeSeed = true;
		}

		return (rand() % (max - min + 1)) + min;
	}
}