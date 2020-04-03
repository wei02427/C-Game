#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CWeapon.h"
#include "CBomb.h"
namespace game_framework {
	CWeapon::CWeapon()
	{
		ms = 0;
		direction = 0;
		tstart = tend = 0;
		factor = 1;
		cx = 40;
		cy = 43;
		nBullets = 0;
	}
	CWeapon::~CWeapon()
	{
		for (auto it = bullets.begin(); it != bullets.end(); ++it)
		{
			delete (*it);
		}
		bullets.clear();
		TRACE("Bullete delete\n");
	}
	void CWeapon::OnMove(CGameMap & map, CPlayer &player)
	{
		direction = player.GetDirection();
		int px = player.GetX1();
		int py = player.GetY1();
		switch (direction) {
		case U:
			wx = (px + 23);
			wy = (py + 25);
			break;
		case D:
			wx = (px + 20);
			wy = (py + 30);
			break;
		case L:
			wx = (px - 5);
			wy = (py + 30);
			break;
		case R:
			wx = (px + 25);
			wy = (py + 30);
			break;
		}
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
	void CWeapon::OnMove(CGameMap & map,CEnemy &enemy)
	{
		wx = (enemy.GetX1() + enemy.GetX2()) / 2 - 20;
		wy = (enemy.GetY1() + enemy.GetY2()) / 2 - 15;
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
	void CWeapon::OnShowBullet(CGameMap & map)
	{
		for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++)
			(*bullet)->OnShow(map);
	}
	void CWeapon::OnShowGun(CGameMap & map)
	{
		weapon[direction].SetTopLeft(map.ScreenX(wx), map.ScreenY(wy));
		weapon[direction].ShowBitmap();
	}
	void CWeapon::OnShowInfo()
	{

		icon.SetTopLeft(cx, cy);
		icon.ShowBitmap(factor);
		num.LoadBitmap();
		num.SetTopLeft(90, 40);
		num.SetInteger(nBullets);
		num.ShowBitmap();

	}
	void CWeapon::HitEnemy(vector<CEnemy*>& enemies)
	{
		for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
			for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++)
				(*bullet)->HitEnemy(*(*enemy));
		}
	}
	void CWeapon::HitPlayer(CPlayer & player)
	{
		for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++)
			(*bullet)->HitPlayer(player);
	}
	void CWeapon::HitGasonline(CBomb & gasoline)
	{
		vector<CBullet*> gasolines = gasoline.GetGasonline();

		for (auto item = gasolines.begin(); item != gasolines.end(); item++) {
			//GAME_ASSERT(false, "----343------");

			for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
				//GAME_ASSERT(false, "----------");
				(*bullet)->HitGasoline((CGasoline*)(*item));
			}
		}
	}
	void CWeapon::AddBullet()
	{
		nBullets += addNum;
	}
	int CWeapon::GetBulletsNum()
	{
		return nBullets;
	}
	string CWeapon::GetType()
	{
		return type;
	}
	bool CWeapon::Delay(int ms)
	{
		if (tstart == 0)
			tstart = clock();
		else if (tstart != 0)
			tend = clock();

		if (difftime(tend, tstart) > ms) {
			tend = tstart = 0;
			return true;
		}
		else
			return false;
	}
}