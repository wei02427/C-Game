#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CDifferentTime.h"

namespace game_framework {
	bool CDifferentTime::Delay(int ms)
	{
		if (tstart == 0)
			tstart = clock();
		else if (tstart != 0)
			tend = clock();

		if (difftime(tend, tstart) > ms) {
			tend = tstart = 0;
			return true;
		}
		else
			return false;
	}
}