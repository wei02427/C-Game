#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEnemy.h"
#include "CBug.h"
#include "CPlayer.h"
#include "CBase.h"
#include "CHealthPoints.h"
#include "CMap.h"
#include "aStar.h"
#define w 0
#define a 1
#define e 2
namespace game_framework {
	CBug::CBug(int X_POS, int Y_POS)
	{
		x = X_POS;
		y = Y_POS;
		blood = 60;
		LoadBitMap();
	}
	void CBug::LoadBitMap()
	{
		int walk[3] = { IDB_MONSTER1,IDB_MONSTER2,IDB_MONSTER3 };
		int attack[5] = { IDB_MONSTER4,IDB_MONSTER5,IDB_MONSTER6,IDB_MONSTER7,IDB_MONSTER8 };
		int explode[3] = { IDB_M_EXPLODE1,IDB_M_EXPLODE2,IDB_M_EXPLODE3 };
		for (int i = 0; i < 3; i++)
			animation[w].AddBitmap(walk[i], RGB(255, 255, 255));
		for (int i = 0; i < 5; i++)
			animation[a].AddBitmap(attack[i], RGB(255, 255, 255));
		for (auto i = 0; i < 3; i++)
			animation[e].AddBitmap(explode[i], RGB(255, 255, 255));
	}
	void CBug::Hit(CPlayer &player)
	{
		int ex = (x + x + animation[w].Width()) / 2;
		int ey = (y + y + animation[w].Height()) / 2;

		if (player.GetY1() <= ey && ey <= player.GetY2() && player.GetX1() <= ex && ex <= player.GetX2()) {
			if (!isHit)
				player.Damage(5);
			isHit = true;
		}
	}
	void CBug::Hit(CBase& base)
	{
		int ex = (x + x + animation[w].Width()) / 2;
		int ey = (y + y + animation[w].Height()) / 2;
		if (base.GetY1() <= ey && ey <= base.GetY2() && base.GetX1() <= ex && ex <= base.GetX2()) {
			CAudio::Instance()->Play(AUDIO_ALA, false);
			if (!isHit)
				base.Damage(5);
			isHit = true;
		}
	}
	void CBug::OnShow(CGameMap &map)
	{
		if (blood > 0 && !isHit) {
			hp->ShowHP(map.ScreenX(x - 25) + 2, map.ScreenY(y - 25), (int)((blood / 60.0) * 100));
			animation[w].SetTopLeft(map.ScreenX(x - 22), map.ScreenY(y - 30));
			animation[w].OnShow();
		}
		else if (blood <= 0) {
			animation[e].SetTopLeft(map.ScreenX(x - 25), map.ScreenY(y - 35));
			animation[e].OnShow();
		}
		else if (isHit) {
			animation[a].SetTopLeft(map.ScreenX(x - 25), map.ScreenY(y - 25));
			animation[a].OnShow();
		}
		if (animation[e].IsFinalBitmap() || animation[a].IsFinalBitmap())
			is_alive = false;
	}
	void CBug::OnMove(CPlayer &player, CBase &base, CGameMap &map)
	{

		int px = (player.GetX1() + player.GetX2()) / 2, py = (player.GetY1() + player.GetY2()) / 2;
		int bx = (base.GetX1() + base.GetX2()) / 2, by = (base.GetY1() + base.GetY2()) / 2;
		const int STEP_SIZE = 1;
		animation[w].OnMove();
		//----------------------------------------------------------------
		nenemy.x = x / 30;
		nenemy.y = y / 30;
		nplayer.x = px / 30;
		nplayer.y = py / 30;
		nbase.x = bx / 30;
		nbase.y = by / 30;

		static bool target = pow(x - px, 2) + pow(y - py, 2) <= pow(x - bx, 2) + pow(y - by, 2);

		if (! Cordinate::aStar(nenemy, nplayer, map).empty())
			target = pow(x - px, 2) + pow(y - py, 2) <= pow(x - bx, 2) + pow(y - by, 2);

		if (!isHit) {

			if (target == BASE)
			{
				path = Cordinate::aStar(nenemy, nbase, map);
				if (!path.empty())
					isSearch = true;
				else
					target = PLAYER;
			}

			if (target == PLAYER)
			{
				path = Cordinate::aStar(nenemy, nplayer, map);
				if (!path.empty())
					isSearch = true;
				else
					target = BASE;
			}

			if (blood > 0 && isHit == false) {
				static auto node = path.begin();

				if (isSearch == true && path.size() != 0) {
					node = path.begin();
					isSearch = false;
				}

				if (!path.empty() && node != path.end()) {
					if (x / 30 == (*node).x && y / 30 == (*node).y)
						node = path.erase(node);

					if (x / 30 < (*node).x)
						x += STEP_SIZE;

					else if (x / 30 > (*node).x)
						x -= STEP_SIZE;

					if (y / 30 > (*node).y)
						y -= STEP_SIZE;

					else if (y / 30 < (*node).y)
						y += STEP_SIZE;
				}

			}
		}

		//-----------------------------------------------------------------
		if (isHit && animation[a].IsFinalBitmap() == false)
			animation[a].OnMove();
		if (blood <= 0 && animation[e].IsFinalBitmap() == false)
			animation[e].OnMove();

	}
	int CBug::GetX1()
	{
		return x - 25;
	}
	int CBug::GetY1()
	{
		return y - 20;
	}
	int CBug::GetX2()
	{
		return x - 27 + animation[w].Height();
	}
	int CBug::GetY2()
	{
		return y - 20 + animation[w].Height();
	}
	CBug::~CBug()
	{
		
	}
}
