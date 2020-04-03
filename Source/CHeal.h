#pragma once
namespace game_framework {
	class CProps;
	class CHeal :public CProps
	{
	public:
		CHeal(int px, int py);
		~CHeal();
		void LoadBitMap();
	protected:
		CHeal* ReturnType() { return this; };
	};
}