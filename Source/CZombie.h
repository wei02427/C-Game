#pragma once
namespace game_framework {
	class CEnemy;
	class CWeapon;
	class CDifferentTime;
	class CZombie :public CEnemy
	{
	public:
		CZombie(int X_POS, int Y_POS);
		void Hit(CPlayer& player); //�������a
		void Hit(CBase& base) {};  //�L�ͤ�������A�ҥH����
		void OnMove(CPlayer &player, CBase &base, CGameMap &map); 
		void OnShow(CGameMap &map);			
		int  GetX2();
		int GetY2();
		~CZombie();
	protected:
		void LoadBitMap();
	private:
		int dir;
		CWeapon* flame;
		CDifferentTime *time;
	};
}