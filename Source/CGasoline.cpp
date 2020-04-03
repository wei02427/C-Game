#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBullet.h"
#include "CWeapon.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CGasoline.h"
#include "CDifferentTime.h"
#include "CMap.h"
namespace game_framework {

	CGasoline::CGasoline(int px, int py) :tmpX(px), tmpY(py), time(new CDifferentTime())
	{
		this->x = px;
		this->y = py;
		damage = 50;
		vaule = 50;
		tmpIsBoom = isBoom = false;
		LoadBitMap();
	}
	void CGasoline::LoadBitMap()
	{
		int booms[7] = { IDB_GASBOOM1 ,IDB_GASBOOM2,IDB_GASBOOM3,IDB_GASBOOM4,IDB_GASBOOM5,IDB_GASBOOM6,IDB_GASBOOM7 };
		animation.AddBitmap(IDB_GASONLINE, RGB(255, 255, 0));
		for (int i = 0; i < 7; i++)
			boom.AddBitmap(booms[i], RGB(255, 255, 255));
		boom.SetDelayCount(7);
	}
	int CGasoline::GetX1()
	{
		return x / 30 * 30;
	}
	int CGasoline::GetX2()
	{
		return x / 30 * 30 + 29;
	}
	void CGasoline::HitEnemy(CEnemy &enemy)
	{
		int ex = (enemy.GetX1() + enemy.GetX2()) / 2;
		int ey = (enemy.GetY1() + enemy.GetY2()) / 2;
		if (isBoom && x <= ex && ex <= x + boom.Width() && y <= ey && ey <= y + boom.Height())
		{
			enemy.Damage(damage);
			if (!(enemy.GetBlood() <= 0))
				enemy.SetValue(vaule);
		}
	}
	void CGasoline::HitPlayer(CPlayer &player)
	{
		int px = (player.GetX1() + player.GetX2()) / 2;
		int py = (player.GetY1() + player.GetY2()) / 2;
		if (isBoom && x <= px && px <= x + boom.Width() && y <= py && py <= y + boom.Height())
		{
			isHit = true;
			player.Damage(damage);
		}
	}
	void CGasoline::OnMove(CGameMap &map)
	{

		if (!isBoom) {
			for (int gx = -1; gx <= 1 && !tmpIsBoom; gx++) {
				if (gx == -1)
					tmpIsBoom = map.IsEmpty(GetX1() - 30, GetY1()) == 4;
				else if (gx == 0)
					tmpIsBoom = map.IsEmpty(GetX1(), GetY1() + 30) == 4 || map.IsEmpty(GetX1(), GetY1() - 30) == 4;
				else if (gx == 1)
					tmpIsBoom = map.IsEmpty(GetX1() + 30, GetY1()) == 4;
			}

		}
		if (time->Delay(1000) && tmpIsBoom)
			isBoom = tmpIsBoom;

		if (boom.IsFinalBitmap() == false && isBoom) {
			boom.OnMove();
		}


	}
	void CGasoline::OnShow(CGameMap & map)
	{

		if (isBoom) {
			//CAudio::Instance()->Play(AUDIO_BOOM, true);
			for (int y = GetY1(); y < GetY1() + 30; y++)
				for (int x = GetX1(); x <= GetX2(); x++)
					map.SetValue(x, y, '4');
			if (boom.IsFinalBitmap() == false) {
				boom.SetTopLeft(map.ScreenX(x), map.ScreenY(y));
				boom.OnShow();

			}
			else {
				for (int y = GetY1(); y < GetY1() + 30; y++)
					for (int x = GetX1(); x <= GetX2(); x++)
						map.SetValue(x, y, '0');
				isHit = true;
			}

		}
		else if (!isBoom) {
			for (int y = GetY1(); y < GetY1() + 30; y++)
				for (int x = GetX1(); x <= GetX2(); x++)
					map.SetValue(x, y, '2');
			animation.SetTopLeft(map.ScreenX(GetX1()), map.ScreenY(GetY1()));
			animation.OnShow();
		}

	}
	int CGasoline::GetY1()
	{
		return y / 30 * 30;
	}
	int CGasoline::GetY2()
	{
		return y / 30 * 30 + animation.Height();
	}
	CGasoline::~CGasoline()
	{
		delete time;
		TRACE("Gasoline delete\n");
	}
}