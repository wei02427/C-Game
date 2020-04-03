#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CWeapon.h"
#include "CBullet.h" //在weapon.h不是編譯過了嗎
#include "CBomb.h"
#include "CGrenadeBullet.h"
#include "CGasoline.h"
#include "CGrenade.h"
#include <string>

namespace game_framework {
	CGrenade::CGrenade()
	{
		ms = 40;
		factor = 2;
		addNum = nBullets = 10;
		type = GRENADE;
		LoadBitMap();
	}
	void CGrenade::LoadBitMap()
	{
		int weapons[4] = { IDB_GRENADE1, IDB_GRENADE1, IDB_GRENADE1, IDB_GRENADE1 };
		for (int i = 0; i < 4; i++)
			weapon[i].LoadBitmap(weapons[i], RGB(255, 255, 255));
		icon.LoadBitmapA(IDB_GRENADE1, RGB(255, 255, 255));
	}
	void CGrenade::Attack()
	{
		if (Delay(ms) && --nBullets >= 0) {
			CAudio::Instance()->Play(AUDIO_SHOT, false);
			bullets.emplace_back(new CGrenadeBullet(direction, wx, wy));
			
		}
	}
	void CGrenade::HitGasonline(CBomb & gasoline)
	{
		vector<CBullet*> gasolines = gasoline.GetGasonline();
		for (auto item = gasolines.begin(); item != gasolines.end(); item++) {
			//GAME_ASSERT(false, "----343------");

			for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
				//GAME_ASSERT(false, "----------");
				((CGrenadeBullet*)(*bullet))->HitGasoline((CGasoline*)((*item)));
			}
		}
	}
}