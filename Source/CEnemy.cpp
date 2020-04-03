#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEnemy.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CBase.h"
#include "CHealthPoints.h"
#include "CDifferentTime.h"
#include "aStar.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Enemy class
	/////////////////////////////////////////////////////////////////////////////
	int fixX = 0;
	CEnemy::CEnemy()
	{
		route = new Cordinate();
		is_alive = true;
		isHit = false;
		hp = new CHealthPoints(50, 10, RGB(227, 13, 13), RGB(255, 255, 255), RGB(227, 13, 13));
	}

	int CEnemy::GetX1()
	{
		return x;
	}

	int CEnemy::GetY1()
	{
		return y;
	}

	int CEnemy::GetX2()
	{
		return x  + animation[1].Width();
	}

	int CEnemy::GetY2()
	{
		return y + animation[1].Height();
	}

	void CEnemy::Damage(int dam)
	{
		if (blood > 0) {
			CAudio::Instance()->Play(AUDIO_MONSTER_CRY, false);
			blood -= dam;
		}
	}

	bool CEnemy::GetIsAlive()
	{
		return is_alive;
	}

	int CEnemy::GetValue()
	{
		return value;
	}

	int CEnemy::GetBlood()
	{
		return blood;
	}

	void CEnemy::SetValue(int val)
	{
		value = val;
	}

	CEnemy::~CEnemy()
	{
		delete hp;
		delete route;
		TRACE("Enemy delete\n");
	}
}