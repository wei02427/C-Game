#pragma once
namespace game_framework {
	class CProps;
	class CCoin :public CProps
	{
	public:
		CCoin(int px, int py);
		~CCoin();
		int GetValue();
		void LoadBitMap();
	protected:
		CCoin* ReturnType() { return this; };
	};
}