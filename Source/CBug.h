#pragma once
namespace game_framework {
	class CEnemy;
	class CBug :public CEnemy 
	{
	public:
		CBug(int X_POS, int Y_POS);
		void Hit(CPlayer& player);
		void Hit(CBase& base);
		void OnShow(CGameMap &map);
		void OnMove(CPlayer &player, CBase &base, CGameMap &map);
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		~CBug();
	protected:
		void LoadBitMap();
	};
}
