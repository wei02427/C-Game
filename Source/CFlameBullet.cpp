#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBullet.h"
#include "CGasoline.h"
#include "CFlameBullet.h"
#include "CPlayer.h"
#include "CMap.h"
#include "CDifferentTime.h"

namespace game_framework {

	void CFlameBullet::LoadBitMap()
	{
		animation.AddBitmap(IDB_FLAME, RGB(255, 255, 255));
	}

	void CFlameBullet::HitPlayer(CPlayer & player)
	{
		if (player.GetX1() <= x && x <= player.GetX2() && player.GetY1() <= y && y <= player.GetY2() && player.Getblood() > 0)
		{
			isHit = true;
			player.Damage(damage);
		}
	}



	CFlameBullet::CFlameBullet(int px,int py,int x, int y)
	{
		sx = this->x = x;
		sy = this->y = y;
		desX = px;
		desY = py;
		damage = 5;
		range = 150;
		fdistance = 0;
		time = new CDifferentTime();
		isLeft = desX < x ? true : false;
		isUp = desY < y ? true : false;

		if (desX < x) 
			m = -(desY - y) / (float)(desX - x);
		
		else if (desX - x==0) 
			m = FLT_MAX;
		
		else if (desY - y == 0)
			m = 0;
		else 
			m = (desY - y) / (float)(desX - x);
		
		if (m != FLT_MAX) {
			fvelocity = roundf(sqrtf(9 / (pow(m, 2) + 1)));
			if (fabs(fvelocity) - 1 < 0)
				fvelocity = 1;
		}
		else if (m == 0)
			fvelocity = 3;

		TRACE("sx=%d desx=%d sy=%d desy=%d m=%f vel=%f\n", sx,desX,sy,desY,m,fvelocity);
		LoadBitMap();
	}

	void CFlameBullet::OnMove(CGameMap & map)
	{
	
		if(pow((x - sx), 2) + pow((y - sy), 2) >= pow(range, 2) )
			isHit = true;

		else if (map.IsEmpty(x, y) != 1 && map.IsEmpty(x, y) != 3) {

			if (isLeft)
				x -= fvelocity;
			else
				x += fvelocity;

			if (m != FLT_MAX && fvelocity != 1)
				y = m * abs(sx - x) + sy;
			else
				if (isUp)
					y -= 3;
				else
					y += 3;
		}
		else
			isHit = true;;
		
	}

	CFlameBullet::~CFlameBullet()
	{
		delete time;
	}

}