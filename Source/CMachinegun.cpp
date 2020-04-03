#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CWeapon.h"
#include "CBullet.h" //在weapon.h不是編譯過了嗎
#include "CBomb.h"
#include "CMachineBullet.h"
#include "CGasoline.h"
#include "CMachinegun.h"
#include <string>

namespace game_framework {
	CMachinegun::CMachinegun()
	{
		ms = 40;
		addNum =  nBullets = 1000;
		factor = 2;
		type = MACHINEGUN;
		LoadBitMap();
	}
	void CMachinegun::LoadBitMap()
	{
		int weapons[4] = { IDB_MACHINEGUN_UP, IDB_MACHINEGUN_DOWN, IDB_MACHINEGUN_LEFT, IDB_MACHINEGUN_RIGHT };
		for (int i = 0; i < 4; i++)
			weapon[i].LoadBitmap(weapons[i], RGB(255, 255, 255));
		icon.LoadBitmapA(IDB_MACHINEGUN_RIGHT, RGB(255, 255, 255));
	}
	void CMachinegun::Attack()
	{
		if (Delay(ms) && --nBullets>=0) {
			CAudio::Instance()->Play(AUDIO_SHOT, false);
			bullets.emplace_back(new CMachineBullet(direction, wx, wy));
			bullets.emplace_back(new CMachineBullet(direction, wx, wy));
			bullets.emplace_back(new CMachineBullet(direction, wx, wy));
		}
	}
}