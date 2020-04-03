#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
//#include "CPlayer.h"
#include "CProps.h"
#include "CCoin.h"

namespace game_framework {
	CCoin::CCoin(int px, int py) 
	{
		this->x = px;
		this->y = py;
		LoadBitMap();
	}

	CCoin::~CCoin()
	{
	}

	int CCoin::GetValue()
	{
		return 50;
	}

	void CCoin::LoadBitMap()
	{
		int coins[5] = { IDB_COIN1,IDB_COIN2,IDB_COIN3,IDB_COIN4,IDB_COIN5 };
		for (int i = 0; i < 5; i++) 
			props.AddBitmap(coins[i],RGB(255,255,255));
	}
}