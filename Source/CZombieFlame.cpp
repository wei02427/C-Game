#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CWeapon.h"
#include "CBullet.h" //在weapon.h不是編譯過了嗎
#include "CZombieFlame.h"
#include "CFlameBullet.h"
#include "CPlayer.h"
namespace game_framework {
	CZombieFlame::CZombieFlame()
	{
		ms = 2000;
		factor = 2;
		LoadBitMap();
	}
	void CZombieFlame::LoadBitMap()
	{
	}
	void CZombieFlame::Attack(CPlayer & player, CBomb *gasoline)
	{
		int px = (player.GetX1() + player.GetX2()) / 2, py = (player.GetY1() + player.GetY2()) / 2;
		if (Delay(ms)) {
			//CAudio::Instance()->Play(AUDIO_SHOT, false);
			bullets.emplace_back(new CFlameBullet(px,py,wx, wy));
		}
		HitPlayer(player);
		if(gasoline!=nullptr)
			HitGasonline(*gasoline);
	}

}