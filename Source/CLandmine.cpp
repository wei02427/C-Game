#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBullet.h"
#include "CWeapon.h"
#include "CLandmine.h"
#include "CEnemy.h"
#include "CPlayer.h"
namespace game_framework {
	CLandmine::CLandmine(int px, int py)
	{
		this->x = px;
		this->y = py;
		damage = 50;
		vaule = 20;
		LoadBitMap();
	}
	void CLandmine::LoadBitMap()
	{
		animation.AddBitmap(IDB_LANDMINE, RGB(255, 255, 255));
		animation.AddBitmap(IDB_LANDMINE2, RGB(255, 255, 255));

	}
	void CLandmine::HitEnemy(CEnemy &enemy)
	{
		int ex = (enemy.GetX1() + enemy.GetX2()) / 2;
		int ey = (enemy.GetY1() + enemy.GetY2()) / 2;
		if (x <= ex && ex <= x + animation.Width() && y <= ey && ey <= y + animation.Height())
		{
			CAudio::Instance()->Play(AUDIO_MINE_BOOM, false);
			isHit = true;
			enemy.Damage(damage);
			if (enemy.GetBlood() <= 0)
				enemy.SetValue(vaule);
		}
	}

	void CLandmine::HitPlayer(CPlayer &player)
	{
		int px = (player.GetX1() + player.GetX2()) / 2;
		int py = (player.GetY1() + player.GetY2()) / 2;
		if (x + 10 <= px && px <= x + animation.Width() - 10 && y + 10 <= py && py <= y + animation.Height() - 10)
		{
			isHit = true;
			player.Damage(damage);
		}
	}

	CLandmine::~CLandmine()
	{
	}
}