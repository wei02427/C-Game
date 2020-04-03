#pragma once
namespace game_framework {
	class CWeapon;
	class CBomb;
	class CGun :public CWeapon
	{
	public:
		CGun();
		void LoadBitMap();
		void Attack();
	};
}