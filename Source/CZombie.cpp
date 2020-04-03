#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEnemy.h"
#include "CWeapon.h"
#include "CZombie.h"
#include "CPlayer.h"
#include "CHealthPoints.h"
#include "CZombieFlame.h"
#include "CDifferentTime.h"
#include "CBackpack.h"
#include "CMap.h"
#include "aStar.h"
#define wr 0
#define wl 1
#define die 2
namespace game_framework {
	CZombie::CZombie(int X_POS, int Y_POS)
	{
		x = X_POS;
		y = Y_POS;
		y = Y_POS;
		blood = 100;
		dir = wr;
		flame = new CZombieFlame();
		time = new CDifferentTime();
		LoadBitMap();
	}
	void CZombie::LoadBitMap()
	{
		int zombieImg[6] = { IDB_ZOMBIE1,IDB_ZOMBIE2,IDB_ZOMBIE3 ,IDB_ZOMBIE4 ,IDB_ZOMBIE5 ,IDB_ZOMBIE6 };
		int zombieImgR[6] = { IDB_ZOMBIE_R1,IDB_ZOMBIE_R2,IDB_ZOMBIE_R3,IDB_ZOMBIE_R4,IDB_ZOMBIE_R5,IDB_ZOMBIE_R6 };
		int zombieDieImg[9] = { IDB_ZOMBIE_DIE1 ,IDB_ZOMBIE_DIE2,IDB_ZOMBIE_DIE3,IDB_ZOMBIE_DIE5,IDB_ZOMBIE_DIE6,IDB_ZOMBIE_DIE7,IDB_ZOMBIE_DIE8,IDB_ZOMBIE_DIE9,IDB_ZOMBIE_DIE10};
		for (int i = 0; i < 6; i++) {
	
			animation[wl].AddBitmap(zombieImg[i], RGB(255, 255, 255));
			animation[wr].AddBitmap(zombieImgR[i], RGB(255, 255, 255));
		}
		for (int i = 0; i < 9; i++) {
			animation[die].AddBitmap(zombieDieImg[i], RGB(255, 255, 255));
		}

	}
	void CZombie::Hit(CPlayer & player)
	{
		int px = (player.GetX1() + player.GetX2()) / 2, py = (player.GetY1() + player.GetY2()) / 2;
		if(px<x && dir==wl ||px >= x && dir == wr && blood>0)
			((CZombieFlame*)flame)->Attack(player,player.GetBackpack().GetPlayerGasonline());
	}

	void CZombie::OnMove(CPlayer & player, CBase & base, CGameMap & map)
	{
		int px = (player.GetX1() + player.GetX2()) / 2, py = (player.GetY1() + player.GetY2()) / 2;
		const int STEP_SIZE = 2;
	
		//----------------------------------------------------------------
		nenemy.x = x / 30;
		nenemy.y = y / 30;
		nplayer.x = px / 30;
		nplayer.y = py / 30;
		animation[dir].OnMove();


		if (blood > 0) {

			if (pow(x - px, 2) + pow(y - py, 2) <= pow(100, 2)) {
				path.clear();
				if (px >= x)
					dir = wr;
				else
					dir = wl;
			}
				

			else if (time->Delay(1500)) {
				path =  Cordinate::aStar(nenemy, nplayer, map);
				if (px >= x)
					dir = wr;
				else 
					dir = wl;
			}

			if (!path.empty())
				isSearch = true;

			static auto node = path.begin();

			if (isSearch == true && path.size() != 0) {
				node = path.begin();
				isSearch = false;
			}

			if (!path.empty() && node+1 != path.end()) {
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

		//-----------------------------------------------------------------

		else if (blood <= 0 && animation[die].IsFinalBitmap() == false)
			animation[die].OnMove();

		flame->OnMove(map,*this);
	}

	void CZombie::OnShow(CGameMap & map)
	{
		flame->OnShowBullet(map);

		if (blood > 0 ) {
			hp->ShowHP(map.ScreenX(x - 25) + 2, map.ScreenY(y - 25), blood);
			animation[dir].SetTopLeft(map.ScreenX(x - 22), map.ScreenY(y - 30));
			animation[dir].OnShow();
		}
		else if (blood <= 0) {
			animation[die].SetTopLeft(map.ScreenX(x - 25), map.ScreenY(y - 35));
			animation[die].OnShow();
			if (animation[die].IsFinalBitmap())
				is_alive = false;
		}
		
	}

	int CZombie::GetX2()
	{
		return x+animation[0].Width()-30;
	}

	int CZombie::GetY2()
	{
		return y + animation[0].Height() - 20;
	}

	CZombie::~CZombie()
	{
		delete flame;
		delete time;
	}

	

	
}