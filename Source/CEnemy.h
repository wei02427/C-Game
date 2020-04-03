#pragma once
#include "aStar.h"
#define PLAYER 1
#define BASE 0
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 敵人Class
	/////////////////////////////////////////////////////////////////////////////
	class CGameMap;
	class CPlayer;
	class CBase;
	class CHealthPoints;
	class CDifferentTime;
	class Cordinate;
	struct Node;
	class CEnemy
	{
	public:
		CEnemy();
		int GetValue(); //回傳擊殺這隻怪物的得分
		int GetBlood(); //取得血量
		void Damage(int dam); //受到傷害
		bool GetIsAlive(); //是否還活著
		void SetValue(int val); //不同武器擊殺 有不同分數
		virtual int  GetX1();
		virtual int  GetY1();
		virtual int  GetX2();
		virtual int  GetY2();
		virtual void Hit(CPlayer& player) = 0; //攻擊玩家
		virtual void Hit(CBase& base) = 0; //攻擊敵人
		virtual void OnMove(CPlayer &player, CBase &base, CGameMap &map) = 0; // 移動敵人
		virtual void OnShow(CGameMap &map) = 0;			// 將敵人圖形貼到畫面
		virtual ~CEnemy();
	protected:
		virtual void LoadBitMap() = 0;				// 載入圖形
		CAnimation animation[3];		// 敵人的動畫
		CHealthPoints *hp;
		Cordinate *route;
		vector<Node> path, tmppath; //敵人移動節點路徑
		Node nenemy, nplayer, nbase; //自身和目標節點
		bool isSearch = false;  //是否找到路徑
		bool is_alive, isHit;				// 是否活著
		int x, y;					
		int blood;
		int value = 0; //得分
	};
}
