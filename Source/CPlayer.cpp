#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <typeinfo>
#include "CPlayer.h"
#include "CBackpack.h"
#include "CMap.h"
#include "CHealthPoints.h"
#include "CWeapon.h"
#include "CGun.h"
#include "CProps.h"
#include "CCoin.h"
#include "CHeal.h"

#define NUM 2
namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// Player class
/////////////////////////////////////////////////////////////////////////////

	CPlayer::CPlayer():hp(new CHealthPoints(70,10,RGB(0,255,127), RGB(255, 255, 255), RGB(0, 255, 127))), weapon(NULL),backpack(new CBackpack())
	{
		Initialize();
	}

	int CPlayer::GetX1()
	{
		return x;
	}

	int CPlayer::GetY1()
	{
		return y;
	}

	int CPlayer::GetX2()
	{
		return x + animation[direction].Width();
	}

	int CPlayer::GetY2()
	{
		return y + animation[direction].Height();
	}

	void CPlayer::Initialize()
	{
		static bool init = false;
		const int X_POS = 200;
		const int Y_POS = 550;
		x = X_POS;
		y = Y_POS;
		isAttack=isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		direction = R;
		blood = 100;
		coins = 50;
		score = 0;
		tstart = tend = 0;
		if(init)
			backpack->Initialize();
		weapon = backpack->GetWeapon();
		init = true;
	}
	void CPlayer::LoadBitMap()
	{
		int side[4][4] = { 	IDB_UP1,IDB_UP2,IDB_UP3,IDB_UP4,
							IDB_DOWN1,IDB_DOWN2,IDB_DOWN3,IDB_DOWN4,
							IDB_LSIDE1,IDB_LSIDE2,IDB_LSIDE3,IDB_LSIDE4,
							IDB_SIDE1,IDB_SIDE2,IDB_SIDE3,IDB_SIDE4};
		for(int i=U;i<=R;i++)
			for (int j = 0; j < 4; j++) {
				animation[i].AddBitmap(side[i][j], RGB(255, 255, 255));
				animation[i].SetDelayCount(4);
			}
		backpack->LoadBitMap();
		icon[0].LoadBitmapA(IDB_STAR, RGB(255, 255, 255));
		icon[1].LoadBitmapA(IDB_COINS, RGB(255, 255, 255));
	}


	void CPlayer::OnMove(CGameMap &map, vector<CEnemy*>& enemies)
	{ 
		const int STEP_SIZE = 5;
		if((isMovingDown||isMovingLeft||isMovingRight||isMovingUp)==true)
			animation[direction].OnMove();
		else
			animation[direction].Reset();
		static int px, py;
		bool vaildX = true, vaildY = true;

		if (isMovingUp) {
			for (px = x+10; px < x + animation[U].Width()-10 && vaildY == true; px++)
				vaildY = map.IsEmpty(px, y - STEP_SIZE) == 0 || map.IsEmpty(px, y - STEP_SIZE) == 4;
			if (vaildY)
				y -= STEP_SIZE;
		
		}
			
		if (isMovingDown) {
			for (px = x+10; px < x + animation[D].Width()-10 && vaildY == true; px++)
				vaildY = map.IsEmpty(px, y + animation[D].Height() + STEP_SIZE ) == 0 || map.IsEmpty(px, y + animation[D].Height() + STEP_SIZE) == 4;
			if (vaildY)
				y += STEP_SIZE;
	
		}
		
		if (isMovingLeft) {
			for (py = y; py < y + animation[L].Height()  && vaildX == true; py++)
				vaildX = map.IsEmpty(x - STEP_SIZE +5 , py) == 0 || map.IsEmpty(x - STEP_SIZE + 5, py) == 4;
			if (vaildX)
				x -= STEP_SIZE;
		}

		if (isMovingRight) {
			for (py = y; py < y + animation[R].Height() && vaildX == true; py++)
				vaildX = map.IsEmpty(x + animation[R].Width() + STEP_SIZE -5 , py) == 0 || map.IsEmpty(x + animation[R].Width() + STEP_SIZE - 5, py) == 4;
			if (vaildX)
				x += STEP_SIZE;
		}

		backpack->OnMove(map, *this, enemies);
		
	}
	void CPlayer::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CPlayer::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CPlayer::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CPlayer::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CPlayer::SetIsAttack(bool flag)
	{
		isAttack = flag;
	}



	void CPlayer::SetDirection(int dir)
	{
		direction = dir;
	}

	void CPlayer::Attack()
	{

		if (isAttack) {
			(*weapon)->Attack();
		}
	}

	void CPlayer::Damage(int damage)
	{
		if (blood > 0)
		{
			CAudio::Instance()->Play(AUDIO_CRY, false);
			blood -= damage;
		}
	}



	void CPlayer::GetScore(int point)
	{
		score += point;
	}

	void CPlayer::GetProps(vector<CProps*> & props)
	{
		for (auto item = props.begin(); item != props.end(); ) {
			const std::type_info& prop = (*item)->IsGot(*this)== nullptr ?typeid(nullptr): typeid(*((*item)->IsGot(*this)));
			const std::type_info& coin = typeid(CCoin);
			const std::type_info& heal = typeid(CHeal);
			const std::type_info& null = typeid(nullptr);
			if (prop != null) {
				if (prop == coin)
				{
					CAudio::Instance()->Play(AUDIO_GOLD, false);
					coins += ((CCoin*)(*item))->GetValue();
				}
				else if (prop == heal) {
					CAudio::Instance()->Play(AUDIO_HEAL, false);
					if (100 - blood >= 10)
						blood += 10;
					else
						blood = 100;
				}
				delete * item;
				item = props.erase(item);
				
			}
			else {
				(*item)->OnMove();
				++item;
			}
		}
	}

	void CPlayer::OnShowInfo()
	{
		
		icon[0].SetTopLeft(190, 40);
		icon[1].SetTopLeft(320, 40);
		icon[0].ShowBitmap(0.03);
		icon[1].ShowBitmap(0.25);

		num[0].LoadBitmapA();
		
		num[0].SetTopLeft(240, 40);
		num[1].SetTopLeft(370, 40);
		num[0].SetInteger(score);
		num[1].SetInteger(coins);

		(*weapon)->OnShowInfo();
		num[0].ShowBitmap();
		num[1].ShowBitmap();
	}


	void CPlayer::SwitchWeapon()
	{
		*weapon = *backpack->GetWeapon();
	}


	CBackpack& CPlayer::GetBackpack()
	{
		return *backpack;
	}

	int CPlayer::GetDirection()
	{
		return direction;
	}

	int CPlayer::CurrentScore()
	{
		return score;
	}

	void CPlayer::OnShow(CGameMap &map)
	{
		if (map.ScreenX(x)>=650)
			map.SetIsRight(true);
		else
			map.SetIsRight(false);

		if (map.ScreenX(x) <= 600)
			map.SetIsleft(true);
		else
			map.SetIsleft(false);

		if (map.ScreenY(y) >= 450)
			map.SetIsDown(true);
		else
			map.SetIsDown(false);

		if (map.ScreenY(y) <= 400)
			map.SetIsUp(true);
		else
			map.SetIsUp(false);
		animation[direction].SetTopLeft(map.ScreenX(x), map.ScreenY(y));
		backpack->OnShow(map);
		animation[direction].OnShow();
		hp->ShowHP(map.ScreenX(x)-15, map.ScreenY(y)-20,blood);
		

	}
	CPlayer::~CPlayer()
	{
		delete hp;
		delete backpack;
	}
}