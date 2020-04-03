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
		vector<CWeapon*>& AddWeapon();  //增加武器，向商店回傳武器的vactor
		CWeapon** GetWeapon();  //取得武器，傳送給玩家一把武器
		void LoadBitMap();
		void OnShow(CGameMap &map);
		void OnMove(CGameMap &map, CPlayer &player, vector<CEnemy*> &enemies);
		void Initialize();
		CBomb* GetPlayerGasonline();
	private:
		vector<CWeapon*> weapons;  //存放玩家擁有的武器
		CWeapon* item;
		int coins;
		int kind;
	};
}