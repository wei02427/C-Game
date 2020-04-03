#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBullet.h"
#include "CGasoline.h"
#include "CGunBullet.h"

namespace game_framework {

	
	void CGunBullet::LoadBitMap()
	{
		animation.AddBitmap(IDB_BULLET, RGB(255, 255, 255));
	}

	CGunBullet::CGunBullet(int direction, int x, int y)
	{
		this->x = x;
		this->y = y;
		this->direction = direction;
		damage = 5;
		range = 500;
		velocity = 10;
		LoadBitMap();
	}

	CGunBullet::~CGunBullet()
	{

	}

}