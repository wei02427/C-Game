#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CProps.h"
#include "CPlayer.h"
#include "CMap.h"
#include "CDifferentTime.h"
namespace game_framework {
	CProps::CProps()
	{
		timer = new CDifferentTime();
		second = 0;
		//LoadBitMap();
	}

	CProps::~CProps()
	{
		delete timer;
		TRACE("Prop delete\n");
	}
	void CProps::OnShow(CGameMap &map)
	{
		props.SetTopLeft(map.ScreenX(x), map.ScreenY(y));
		props.OnShow();
	}
	void CProps::OnMove()
	{
		if (timer->Delay(1000))
			second++;
		props.OnMove();
	}
	bool CProps::IsTimesUp()
	{
		return second==10;
	}
	CProps* CProps::IsGot(CPlayer &player)
	{
		if (player.GetY1() <= y && y <= player.GetY2() && player.GetX1() <= x && x <= player.GetX2())
			return ReturnType();
		else
			return NULL;
	}
}