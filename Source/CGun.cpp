#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CWeapon.h"
#include "CBullet.h" //在weapon.h不是編譯過了嗎
#include "CBomb.h"
#include "CGunBullet.h"
#include "CGasoline.h"
#include "CGun.h"
#include <string>

namespace game_framework {
	CGun::CGun()
	{
		ms = 200;
		nBullets = INT_MAX;
		factor = 2;
		type = GUN;
	}
	void CGun::LoadBitMap()
	{
		int weapons[4] = { IDB_SHOTGUN1, IDB_SHOTGUN2, IDB_SHOTGUN3, IDB_SHOTGUN4 };
		for (int i = 0; i < 4; i++) 
			weapon[i].LoadBitmap(weapons[i],RGB(255,255,255));
		icon.LoadBitmapA(IDB_SHOTGUN4, RGB(255, 255, 255));
	}
	void CGun::Attack()
	{
		if (Delay(ms)) {
			CAudio::Instance()->Play(AUDIO_SHOT, false);
			bullets.emplace_back(new CGunBullet(direction, wx, wy));
		}
	}
}