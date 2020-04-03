#pragma once
namespace game_framework {
	class CWeapon;
	class CMachinegun :public CWeapon
	{
	public:
		CMachinegun();
		void LoadBitMap();
		void Attack();
		void HitPlayer(CPlayer &) {};
	};
}
