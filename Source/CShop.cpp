#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <typeInfo>
#include <array>
#include "CShop.h"
#include "CWeapon.h"
#include "CBomb.h"
#include "CRocket.h"
#include "CMachinegun.h"
#include "CGrenade.h"
#include "CGun.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CBackpack.h"
#include "CDifferentTime.h"

namespace game_framework {
	CShop::CShop(int *pcoin) :time(new CDifferentTime())
	{
		coins = pcoin;
		show = false;
		kind = 0;
	}
	CShop::~CShop()
	{
		delete time;
		TRACE("Shop delete\n");
	}
	void CShop::LoadBitMap()
	{
		CMovingBitmap coin;
		CInteger num;
		coin.LoadBitmapA(IDB_COINS, RGB(255, 255, 255));
		icon.emplace_back(make_pair(coin, num));
		select.LoadBitmapA(IDB_SELECT, RGB(255, 201, 14));
		//*改武器數量 -> WEAPONS_NUM
		//*goodImg 彩色、黑白、介紹、價格
		int goodsImg[WEAPONS_NUM][5] = { {IDB_SHOP_MINE,IDB_SHOP_MINEB,IDB_SHOP_MINE_INTRO,10} ,{IDB_SHOP_GAS,IDB_SHOP_GASB,IDB_SHOP_GAS_INTRO,10},{IDB_SHOP_MACHINEGUN,IDB_SHOP_MACHINEGUNB,IDB_SHOP_MACHINEGUN_INTRO,50},{IDB_SHOP_ROCKET,IDB_SHOP_ROCKETB,IDB_SHOP_ROCKET_INTRO,50},{IDB_SHOP_GRENADE,IDB_SHOP_GRENADE_B,IDB_GRENADE_INTRO,10} };
		//*武器名字
		string name[WEAPONS_NUM] = { LANDMINE,GASONLINE,MACHINEGUN,ROCKET,GRENADE };

		for (int i = 0; i < WEAPONS_NUM; i++) {
			goods item;
			for (int j = 0; j < 3; j++) {

				item[j].LoadBitmapA(goodsImg[i][j], RGB(18, 21, 29));
			}
			icon.emplace_back(make_pair(item[0], num));
			icon.back().second.SetInteger(0);
			weapons.emplace_back(make_pair(name[i], make_pair(item, goodsImg[i][3])));
		}
		shop.LoadBitmapA(IDB_SHOP);

	}
	void CShop::OnShow()
	{
		int goodsPos[WEAPONS_NUM][2] = { {150,340},{215,336},{267,349},{329,345},{393,345} }; //*設定介紹頁面位置
		for (int i = 0; i < WEAPONS_NUM; i++) {
			weapons[i].second.first[0].SetTopLeft(goodsPos[i][0], goodsPos[i][1]);
			weapons[i].second.first[1].SetTopLeft(goodsPos[i][0], goodsPos[i][1]);
			weapons[i].second.first[2].SetTopLeft(534, 383);
		}
		shop.SetTopLeft(80, 150);
		if (show == true) {
			shop.ShowBitmap();
			for (int i = 0; i < WEAPONS_NUM; i++) {
				if (*coins >= weapons[i].second.second) {
					weapons[i].second.first[0].ShowBitmap();
					//goods[i][2].ShowBitmap();
				}
				else
					weapons[i].second.first[1].ShowBitmap();

				//TRACE("*************************x=%d   y=%d\n", p.x, p.y);

			}
			if (kind != -1) {
				weapons[kind].second.first[2].ShowBitmap(); //武器intro
				select.SetTopLeft(135 + kind * 60, 322);
				static bool flicker = false;
				if (time->Delay(700))
					flicker = !flicker;
				if (flicker)
					select.ShowBitmap(0.4);
			}
			icon[0].first.SetTopLeft(550, 550);  //目前coin數量
			icon[0].first.ShowBitmap(0.25);
			icon[0].second.SetTopLeft(600, 550);
			icon[0].second.SetInteger(*coins);
			icon[0].second.ShowBitmap();
			if (kind != -1) { //武器數量
				icon[kind + 1].first.SetTopLeft(700, 550);
				icon[kind + 1].first.ShowBitmap();
				icon[kind + 1].second.SetTopLeft(750, 550);
				icon[kind + 1].second.ShowBitmap();
			}
		}
	}
	void CShop::SetShowKind(UINT nChar) {
		if (nChar == KEY_LEFT && kind - 1 >= 0)
			kind--;
		else if (nChar == KEY_RIGHT && kind + 1 <= WEAPONS_NUM-1)
			kind++;
	}
	void CShop::OnMove(vector<CWeapon*>&weapons)
	{
		if (kind != -1) {
			const std::type_info& bomb = typeid(CBomb);
			auto item = weapons.begin();
			for (item; item != weapons.end(); item++) {
				string type = (*item)->GetType();
				if (type == this->weapons[kind].first) {
					icon[kind + 1].second.SetInteger((*item)->GetBulletsNum());
				}
				
			}
		}
	}
	void CShop::BuyWeapon(bool confirm, vector<CWeapon*>&weapons)
	{
		if (kind != -1) {
			if (show && confirm && *coins >= this->weapons[kind].second.second) {
				CAudio::Instance()->Play(AUDIO_BUY, false);
				auto item = weapons.begin();
				for (item; item != weapons.end(); item++) {
					string type = (*item)->GetType();
					if (this->weapons[kind].first == type){
						(*item)->AddBullet();
						*coins -= this->weapons[kind].second.second;
						break;
					}
				}
				if (item == weapons.end()) {
					if (kind == 0 || kind == 1) 
						weapons.emplace_back(new CBomb(kind));
					else if(kind ==2)
						weapons.emplace_back(new CMachinegun());
					else if (kind == 3) 
						weapons.emplace_back(new CRocket());
					else if (kind == 4)
						weapons.emplace_back(new CGrenade());
					//*如果還沒買過在這加
					*coins -= this->weapons[kind].second.second;
				}
			}
		}
	}
}