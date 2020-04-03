#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBase.h"
#include "CMap.h"
#include "CHealthPoints.h"
#include "CDifferentTime.h"

namespace game_framework {
	int CBase::x = 450;
	int CBase::y = 300;
	CBase::CBase() :hp(new CHealthPoints(200, 10, RGB(0, 255, 127), RGB(255, 255, 255), RGB(0, 255, 127))), blood(150),time(new CDifferentTime()),distance(0),direction(0)
	{
		dx = x + 80;
		dy = y - 50;
	}
	CBase::~CBase()
	{
		delete hp;
		delete time;
	}
	void CBase::LoadBitMap(CGameMap& map)
	{
		base.LoadBitmap(IDB_BASE, RGB(255, 255, 255));
		int diamondBmp[4] = {IDB_DIAMOND1,IDB_DIAMOND2,IDB_DIAMOND3,IDB_DIAMOND4 };
		for (int i = 0; i < 4; i++)
			diamond.AddBitmap(diamondBmp[i], RGB(255, 255, 255));
		for (int y = this->y ; y < this->y+base.Height(); y++)
			for (int x = this->x; x < this->x+base.Width(); x++)
				map.SetValue(x, y, '3');
	}
	void CBase::OnShow(CGameMap& map)
	{
		base.SetTopLeft(map.ScreenX(x),map.ScreenY(y));
		diamond.SetTopLeft(map.ScreenX(dx), map.ScreenY(dy));
		base.ShowBitmap();
		hp->ShowHP(map.ScreenX(x), map.ScreenY(y - 80), (int)(blood/150.0*100));
		diamond.OnShow();
	}
	void CBase::OnMove()
	{
		diamond.OnMove();
		switch (direction) {
		case 0:
			if (time->Delay(50))
				dy -= (distance+= 1);
			if (distance == 8) {
				direction = 1;
				distance = 0;
			}
			break;
		case 1:
			if (time->Delay(50))
				dy += (distance += 1);
			if (distance == 8) {
				direction = 0;
				distance = 0;
			}
			break;
		}
		
	}
	void CBase::Damage(int damage)
	{
		blood -= damage;
	}
	void CBase::Initialize()
	{
		blood = 150;
	}
	int CBase::GetBlood()
	{
		return blood;
	}
	int CBase::GetX1()
	{
		return x;
	}
	int CBase::GetY1()
	{
		return y;
	}
	int CBase::GetX2()
	{
		return x + base.Width();
	}
	int CBase::GetY2()
	{
		return y + base.Height();
	}
}