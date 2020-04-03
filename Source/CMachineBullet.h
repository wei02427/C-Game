#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//¤l¼uclass
	/////////////////////////////////////////////////////////////////////////////
	class CBullet;
	class CGasoline;
	class CMachineBullet :public CBullet
	{
	public:
		CMachineBullet(int direction, int x, int y);
		void LoadBitMap();
		void HitPlayer(CPlayer&) {};
		void OnMove(CGameMap& map);
		void OnShow(CGameMap& map);
		~CMachineBullet();
	private:
		static int num;
		int bulleteDir;
	};
}

