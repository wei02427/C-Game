#pragma once
namespace game_framework {
	class CWeapon;
	class CPlayer;
	class CBomb;
	class CZombieFlame :public CWeapon
	{
	public:
		CZombieFlame();
		void LoadBitMap();
		void HitEnemy(CEnemy&) {};
		void Attack(CPlayer &player , CBomb *gasoline);
		void Attack() {};
	};
}