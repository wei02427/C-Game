#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CWeapon.h"
#include "CBullet.h" //在weapon.h不是編譯過了嗎
#include "CBomb.h"
#include "CLandmine.h"
#include "CGasoline.h"
#include "CPlayer.h"
#include "CMap.h"
namespace game_framework {

	CBomb::CBomb(int kind)
	{
		ms = 200;
		this->kind = kind;
		addNum = nBullets = 10;
		if (kind == 0) {
			cx = 35;
			cy = 30;
			type = LANDMINE;
		}
		else {
			cx = 45;
			cy = 35;
			type = GASONLINE;
		}
		LoadBitMap();
	}

	CBomb::~CBomb()
	{
		for (auto it = bullets.begin(); it != bullets.end(); ++it)
		{
			delete (*it);
		}
		bullets.clear();
	}

	void CBomb::LoadBitMap()
	{
		if (kind == 0)
			icon.LoadBitmapA(IDB_LANDMINE, RGB(255, 255, 255));
		else
			icon.LoadBitmapA(IDB_GASONLINE, RGB(255, 255, 0));
	}

	void CBomb::OnMove(CGameMap & map, CPlayer & player)
	{
		px = player.GetX1() / 30 * 30;
		py = player.GetY1() / 30 * 30;

		switch (player.GetDirection())
		{
		case U:
			py += 31;
			px += 31;
			break;
		case D:
			py -= 31;
			px += 31;
			break;
		case L:
			px += 31;
			break;
		case R:
			px -= 31;
			break;
		}
		validY = py > 800 ? map.IsEmpty(px, py + 31) == 0 : map.IsEmpty(px, py) == 0;
		validX = px > 1000 ? map.IsEmpty(px + 31, py) == 0 : map.IsEmpty(px, py) == 0;
		for (auto bullet = bullets.begin(); bullet != bullets.end();) {
			if ((*bullet)->GetIsHit()) {

				delete (*bullet);
				bullet = bullets.erase(bullet);
			}
			else {
				(*bullet)->OnMove(map);
				++bullet;
			}
		}
	}
	void CBomb::OnShowBullet(CGameMap & map)
	{
		for (auto bullet = bullets.rbegin(); bullet != bullets.rend(); bullet++)
			(*bullet)->OnShow(map);
	}

	void CBomb::Attack()
	{

		if (Delay(ms) && validY && validX && --nBullets >= 0) {
			if (kind == 0)
			{
				CAudio::Instance()->Play(AUDIO_MINE, false);
				bullets.emplace_back(new CLandmine(px, py));
			}
			else if (kind == 1) {
				CAudio::Instance()->Play(AUDIO_GAS, false);
				bullets.emplace_back(new CGasoline(px, py));
			}
		}

	}
}