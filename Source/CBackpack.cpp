#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <typeInfo>
#include "CWeapon.h"
#include "CGun.h"
#include "CGrenade.h"
#include "CRocket.h"
#include "CMachinegun.h"
#include "CBomb.h"
#include "CBackpack.h"
namespace game_framework {
	CBackpack::CBackpack()
	{	
		weapons.emplace_back(new CGun());
		coins = 0;
		kind = 0;
		item = nullptr;
		
	}
	CBackpack::~CBackpack()
	{
		for (auto it = weapons.begin(); it != weapons.end(); it++)
			delete *it;
		weapons.clear();
		
	}
	vector<CWeapon*>& CBackpack::AddWeapon()
	{
		return weapons;
	}
	CWeapon ** CBackpack::GetWeapon()
	{
		kind = kind < weapons.size() - 1 ? kind + 1 : 0;
		item = weapons[kind];
		return &item;
	}
	void CBackpack::LoadBitMap()
	{
		weapons[0]->LoadBitMap();
	}
	void CBackpack::OnShow(CGameMap &map)
	{
		for (auto item = weapons.rbegin(); item!=weapons.rend(); item++)
			(*item)->OnShowBullet(map);
		weapons[kind]->OnShowGun(map);
	}
	void CBackpack::OnMove(CGameMap &map,CPlayer &player, vector<CEnemy*> &enemies)
	{
	
		for (auto i = 0; i < weapons.size(); i++) {
			weapons[i]->OnMove(map, player);
			weapons[i]->HitEnemy(enemies);
			weapons[i]->HitPlayer(player);

			if (weapons[kind]->GetBulletsNum()==0)
				GetWeapon();
			
			else if (weapons[i]->GetType() == GASONLINE )
				weapons[kind]->HitGasonline(*(CBomb*)(weapons[i]));
		}
	}
	void CBackpack::Initialize()
	{
		for (auto it = weapons.begin(); it != weapons.end(); ++it)
			delete *it;
		weapons.clear();
		weapons.emplace_back(new CGun());
		LoadBitMap();
	}
	CBomb * CBackpack::GetPlayerGasonline()
	{
		for (auto i = 0; i < weapons.size(); i++) {
			if (weapons[i]->GetType() == GASONLINE)
				return (CBomb*)weapons[i];
		}
		return nullptr;
	}
}
