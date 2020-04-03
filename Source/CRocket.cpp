#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CWeapon.h"
#include "CBullet.h" //在weapon.h不是編譯過了嗎
#include "CBomb.h"
#include "CRocketBullet.h"
#include "CGasoline.h"
#include "CRocket.h"


namespace game_framework {
	CRocket::CRocket()
	{
		ms = 1000;
		addNum = nBullets = 30;
		factor = 2;
		type= ROCKET;
		LoadBitMap();
	}
	void CRocket::LoadBitMap()
	{
		int weapons[4] = { IDB_ROCKET1, IDB_ROCKET2, IDB_ROCKET3, IDB_ROCKET4 };
		for (int i = 0; i < 4; i++)
			weapon[i].LoadBitmap(weapons[i], RGB(255, 255, 255));
		icon.LoadBitmapA(IDB_ROCKET4, RGB(255, 255, 255));
	}
	void CRocket::Attack()
	{
		if (Delay(ms) && --nBullets >= 0) {
			CAudio::Instance()->Play(AUDIO_SHOT, false);
			bullets.emplace_back(new CRocketBullet(direction, wx, wy));
		}
	}
}