#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//¤l¼uclass
	/////////////////////////////////////////////////////////////////////////////
	class CBullet;
	class CGasoline;
	class CRocketBullet :public CBullet
	{
	public:
		CRocketBullet(int direction, int x, int y);
		void LoadBitMap();
		void HitEnemy(CEnemy& enemy);
		void HitPlayer(CPlayer &) {};
		void OnMove(CGameMap& map);
		void OnShow(CGameMap& map);
		~CRocketBullet();
	private:
		CAnimation RocketBoom;
		bool isBoom;

	};
}
