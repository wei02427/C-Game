#pragma once
namespace game_framework {
	class CWeapon;
	class CGameMap;
	class CPlayer;
	class CBomb :public CWeapon
	{
	public:
		CBomb(int kind);
		~CBomb();
		void LoadBitMap();
		void OnShowBullet(CGameMap &map);
		void OnShowGun(CGameMap &map) {};
		void OnMove(CGameMap & map, CPlayer &player);
		void HitGasonline(CBomb & gasoline) {};
		void Attack();
		vector<CBullet*> GetGasonline() { if (kind == 1)return bullets; }; 
	private:
		int kind; //�]�wbomb�������A�����a�p�M�T�o��
		int px, py;
		bool validX, validY; 
	};
}