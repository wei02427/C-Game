#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//¤l¼uclass
	/////////////////////////////////////////////////////////////////////////////
	class CBullet;
	class CGasoline;
	class CDifferentTime;
	class CGrenadeBullet :public CBullet
	{
	public:
		CGrenadeBullet(int direction, int x, int y);
		void LoadBitMap();
		void HitEnemy(CEnemy& enemy);
		void HitPlayer(CPlayer& player);
		void HitGasoline(CGasoline *gasoline);
		void OnMove(CGameMap& map);
		void OnShow(CGameMap& map);
		int GetY1();
		int GetY2();
		int GetX1();
		int GetX2();
		~CGrenadeBullet();
	private:
		CAnimation GrenadeBoom;
		CAnimation GrenadeAnimation;
		CDifferentTime *time;
		int y_n, x_n;
		int TimeStart, TimeEnd;
		bool isBoom;
		bool isStop;
	};
}
