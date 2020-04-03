#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//子彈class
	/////////////////////////////////////////////////////////////////////////////
	class CEnemy;
	class CGameMap;
	class CPlayer;
	class CGasoline;
	class CBullet
	{
	public:
		CBullet();
		virtual void LoadBitMap() = 0;		
		virtual void OnMove(CGameMap&);			
		virtual void OnShow(CGameMap&);			
		virtual void HitEnemy(CEnemy&);
		virtual void HitPlayer(CPlayer&) = 0; 
		virtual void HitGasoline(CGasoline *gasoline);
		virtual bool GetIsHit(); //是否已經設到物體
		virtual ~CBullet();
	protected:
		int x, y;			
		int velocity;			
		int damage; //子彈的傷害
		int direction; //方向
		int distance; //目前飛行距離
		int range;  //最大飛行距離
		int vaule; //不同子彈有不同得分
		float fvelocity, fdistance;
		bool isHit;
		CAnimation animation;	
		CMovingBitmap bulletsBmp[4];
	};
}
