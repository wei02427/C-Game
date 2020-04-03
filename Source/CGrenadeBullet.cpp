#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBullet.h"
#include "CGasoline.h"
#include "CGrenadeBullet.h"
#include "CEnemy.h"
#include "CMap.h"
#include "CDifferentTime.h"
#include "math.h"
#include "CPlayer.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBouncingBall: BouncingBall class
	/////////////////////////////////////////////////////////////////////////////


	void CGrenadeBullet::LoadBitMap()
	{

		int RocketBulletAnimation[6] = { IDB_GRENADE1 ,IDB_GRENADE2 ,IDB_GRENADE3, IDB_GRENADE4, IDB_GRENADE5, IDB_GRENADE6 };
		for (int i = 0; i < 6; i++)
			GrenadeAnimation.AddBitmap(RocketBulletAnimation[i], RGB(255, 255, 255));
		GrenadeAnimation.SetDelayCount(7);

		int GrenadeBoomAnimation[6] = { IDB_GRENADE_BOOM1 ,IDB_GRENADE_BOOM2,IDB_GRENADE_BOOM3,IDB_GRENADE_BOOM4,IDB_GRENADE_BOOM5,IDB_GRENADE_BOOM6 };
		for (int i = 0; i < 6; i++)
			GrenadeBoom.AddBitmap(GrenadeBoomAnimation[i], RGB(255, 255, 255));
		//GrenadeBoom.SetDelayCount(7);
	}

	void CGrenadeBullet::OnMove(CGameMap& map)
	{
		if (isBoom == true)
		{
			if (!GrenadeBoom.IsFinalBitmap())
			{
				GrenadeBoom.OnMove();
			}
			else {
				for (int y = GetY1(); y < GetY2(); y++) {
					for (int x = GetX1(); x <= GetX2(); x++)
						map.SetValue(x, y, '0');
				}
				isHit = true;
			}
		}
		
		else {
			if (!isStop && !isBoom && distance < range && map.IsEmpty(x, y) != 1 && map.IsEmpty(x, y) != 3)
			{
				GrenadeAnimation.OnMove();
				y_n = y;
				x_n = x;
				switch (direction)
				{
				case U:
					y -= velocity;
					break;
				case D:
					y += velocity;
					break;
				case L:
					x -= velocity;

					break;
				case R:
					x += velocity;
					break;
				}
				distance += velocity;
			}
			if (time->Delay(2000))
			{
				isBoom = true;
				for (int y = GetY1(); y < GetY2(); y++) {
					for (int x = GetX1(); x <= GetX2(); x++)
						map.SetValue(x, y, '4');
				}
			}
		}

		
	}
	void CGrenadeBullet::OnShow(CGameMap & map)
	{
		if (isBoom && !GrenadeBoom.IsFinalBitmap()) {	
			GrenadeBoom.SetTopLeft((map.ScreenX(x-45)), map.ScreenY(y-45));
			GrenadeBoom.OnShow();
		}
		else {
			GrenadeAnimation.SetTopLeft(map.ScreenX(x), map.ScreenY(y));
			GrenadeAnimation.OnShow();
		}
	}
	int CGrenadeBullet::GetY1()
	{
		return y-45;
	}
	int CGrenadeBullet::GetY2()
	{
		return y - 45 + GrenadeBoom.Height();
	}
	int CGrenadeBullet::GetX1()
	{
		return x - 45;
	}
	int CGrenadeBullet::GetX2()
	{
		return x - 45+ GrenadeBoom.Width();
	}
	void  CGrenadeBullet::HitEnemy(CEnemy& enemy)
	{
		int ex = (enemy.GetX1() + enemy.GetX2()) / 2;
		int ey = (enemy.GetY1() + enemy.GetY2()) / 2;
		if (isBoom && x-45 <= ex && ex <= x + GrenadeBoom.Width()-45 && y-45 <= ey && ey <= y + GrenadeBoom.Height()-45)
		{
			enemy.Damage(damage);
			if (!enemy.GetBlood() <= 0)
				enemy.SetValue(vaule);
		}
		if (enemy.GetX1() <= x && x <= enemy.GetX2() && enemy.GetY1() <= y && y <= enemy.GetY2())
		{
			isStop = true;
		}
	}
	void  CGrenadeBullet::HitPlayer(CPlayer& player)
	{
		int ex = (player.GetX1() + player.GetX2()) / 2;
		int ey = (player.GetY1() + player.GetY2()) / 2;
		if (isBoom && x - 45 <= ex && ex <= x + GrenadeBoom.Width() - 45 && y - 45 <= ey && ey <= y + GrenadeBoom.Height() - 45)
		{
			player.Damage(damage-2);
		}
		
	}
	void CGrenadeBullet::HitGasoline(CGasoline * gasoline)
	{
		
		if (gasoline->GetY1() <= y && y <= gasoline->GetY2() && gasoline->GetX1() <= x && x <= gasoline->GetX2() && !gasoline->IsBoom())
		{
			isStop = true;
		}
	}


	CGrenadeBullet::CGrenadeBullet(int direction, int x, int y)
	{
		time= new CDifferentTime();
		this->x = x;
		this->y = y;
		this->direction = direction;
		damage = 20;
		range = 300;
		velocity = 5;
		vaule = 30;
		LoadBitMap();
		isBoom = false;
		isStop = false;
	}

	CGrenadeBullet::~CGrenadeBullet()
	{
		delete time;
	}

}