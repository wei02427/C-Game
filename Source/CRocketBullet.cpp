#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBullet.h"
#include "CGasoline.h"
#include "CRocketBullet.h"
#include "CEnemy.h"
#include "CMap.h"


namespace game_framework {
	void CRocketBullet::LoadBitMap()
	{
		
		int RocketBullet[4] = { IDB_ROCKET_BULLET_UP ,IDB_ROCKET_BULLET_DOWN, IDB_ROCKET_BULLET_LEFT, IDB_ROCKET_BULLET_RIGHT };
		for (int i = 0; i < 4; i++)
			bulletsBmp[i].LoadBitmapA(RocketBullet[i], RGB(255, 255, 255));

		int RocketBoomAnimation[7] = { IDB_GASBOOM1 ,IDB_GASBOOM2,IDB_GASBOOM3,IDB_GASBOOM4,IDB_GASBOOM5,IDB_GASBOOM6,IDB_GASBOOM7 };
		for (int i = 0; i < 7; i++)
			RocketBoom.AddBitmap(RocketBoomAnimation[i], RGB(255, 255, 255));
		RocketBoom.SetDelayCount(7);
	}

	void CRocketBullet::OnMove(CGameMap& map)
	{
		if (isBoom == true)
		{	
			if (!RocketBoom.IsFinalBitmap())
			{
				RocketBoom.OnMove();
			}
			else
				isHit = true;
			
		}
		if (isBoom == false && distance <= range && map.IsEmpty(x, y) != 1 && map.IsEmpty(x, y) != 3)
		{
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
		else
		{
			isBoom = true;
		}

	}
	void CRocketBullet::OnShow(CGameMap & map)
	{
		if (isBoom == true && !RocketBoom.IsFinalBitmap()) {
			RocketBoom.SetTopLeft(map.ScreenX(x-30), map.ScreenY(y-30));
			RocketBoom.OnShow();
		}
		else if(!isBoom){
			bulletsBmp[direction].SetTopLeft(map.ScreenX(x), map.ScreenY(y));
			bulletsBmp[direction].ShowBitmap();
		}
	}
	void  CRocketBullet::HitEnemy(CEnemy& enemy)
	{
		if (enemy.GetX1() <= x && x <= enemy.GetX2() && enemy.GetY1() <= y && y <= enemy.GetY2() && enemy.GetBlood() > 0)
		{
			CAudio::Instance()->Play(AUDIO_BOOM, false);
			isBoom = true;
			enemy.Damage(damage);
			if (enemy.GetBlood() <= 0)
				enemy.SetValue(vaule);
		}
	}

	
	CRocketBullet::CRocketBullet(int direction, int x, int y)
	{
		this->x = x;
		this->y = y;
		this->direction = direction;
		damage = 50;
		range = 500;
		velocity = 12;
		vaule = 35;
		LoadBitMap();
		isBoom = false;
	}

	CRocketBullet::~CRocketBullet( )
	{
		
	}

}