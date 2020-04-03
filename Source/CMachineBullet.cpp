#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBullet.h"
#include "CGasoline.h"
#include "CMachineBullet.h"
#include "CMap.h"
#include "CEnemy.h"

namespace game_framework {

	int CMachineBullet::num = 0;
	void CMachineBullet::LoadBitMap()
	{
		int MachinegunBullet[4] = { IDB_MACHINEGUN_BULLET_UP ,IDB_MACHINEGUN_BULLET_DOWN, IDB_MACHINEGUN_BULLET_LEFT, IDB_MACHINEGUN_BULLET_RIGHT };
		for (int i = 0; i < 4; i++)
			bulletsBmp[i].LoadBitmapA(MachinegunBullet[i], RGB(255, 255, 255));
	}
	void CMachineBullet::OnMove(CGameMap& map)
	{
		
		if (isHit == false && distance <= range && map.IsEmpty(x, y) != 1 && map.IsEmpty(x, y) != 3)
		{
			switch (direction)
			{
			case U:
				y -= velocity;
				x += bulleteDir;
				break;
			case D:
				y += velocity;
				x += bulleteDir;
				break;
			case L:
				x -= velocity;
				y += bulleteDir;
				break;
			case R:
				x += velocity;
				y += bulleteDir;
				break;
			}
			distance += velocity;

		}
		else
		{
			isHit = true;
		}

	}
	void CMachineBullet::OnShow(CGameMap & map)
	{
		if (isHit == false && distance <= range) {
			bulletsBmp[direction].SetTopLeft(map.ScreenX(x), map.ScreenY(y));
			bulletsBmp[direction].ShowBitmap();
		}
		
	}


	CMachineBullet::CMachineBullet(int direction, int x, int y)
	{
		this->x = x;
		this->y = y;
		this->direction = direction;
		damage = 5;
		range = 500;
		velocity = 10;
		LoadBitMap();
		switch (num++)
		{
		case 0:
			bulleteDir = 0.2*velocity;
			break;
		case 1:
			bulleteDir = 0;
			break;
		case 2:
			bulleteDir = -0.2*velocity;
			num = 0;
			break;
		}
	}

	CMachineBullet::~CMachineBullet()
	{

	}

}