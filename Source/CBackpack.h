#pragma once
namespace game_framework {
	class CWeapon;
	class CGameMap;
	class CPlayer;
	class CEnemy;
	class CBackpack {
	public:
		CBackpack();
		~CBackpack();
		vector<CWeapon*>& AddWeapon();  //�W�[�Z���A�V�ө��^�ǪZ����vactor
		CWeapon** GetWeapon();  //���o�Z���A�ǰe�����a�@��Z��
		void LoadBitMap();
		void OnShow(CGameMap &map);
		void OnMove(CGameMap &map, CPlayer &player, vector<CEnemy*> &enemies);
		void Initialize();
		CBomb* GetPlayerGasonline();
	private:
		vector<CWeapon*> weapons;  //�s�񪱮a�֦����Z��
		CWeapon* item;
		int coins;
		int kind;
	};
}