#pragma once
namespace game_framework {
	class CWeapon;
	class CRocket :public CWeapon
	{
	public:
		CRocket();
		void LoadBitMap();
		void HitPlayer(CPlayer &) {};
		void Attack();
	};
}
