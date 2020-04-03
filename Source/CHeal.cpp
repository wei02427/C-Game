#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
//#include "CPlayer.h"
#include "CProps.h"
#include "CHeal.h"

namespace game_framework {
	CHeal::CHeal(int px, int py)
	{
		this->x = px;
		this->y = py;
		LoadBitMap();
	}

	CHeal::~CHeal()
	{
	}

	void CHeal::LoadBitMap()
	{
		int power[4] = { IDB_HEAL,IDB_HEAL2,IDB_HEAL3,IDB_HEAL4};
		for (int i = 0; i < 4; i++)
			props.AddBitmap(power[i], RGB(255, 255, 255));
	}
}