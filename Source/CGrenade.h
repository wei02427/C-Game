#pragma once
namespace game_framework {
	class CWeapon;
	class CBomb;
	class CGrenade :public CWeapon
	{
	public:
		CGrenade();
		void LoadBitMap();
		void Attack();
		void HitGasonline(CBomb &gasoline);

	};
}

