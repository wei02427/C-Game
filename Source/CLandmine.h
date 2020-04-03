#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 地雷class
	/////////////////////////////////////////////////////////////////////////////
	class CBullet;
	class CLandmine :public CBullet
	{
	public:
		CLandmine(int px, int py);
		void LoadBitMap();			// 載入圖形
		void HitEnemy(CEnemy&enemy);
		void HitPlayer(CPlayer&);
		~CLandmine();
	};
}
