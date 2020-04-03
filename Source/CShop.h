#pragma once
namespace game_framework {
	class CWeapon;
	class CGameMap;
	class CPlayer;
	class CDifferentTime;
	class CShop {
	public:
		CShop(int *pcoin);
		~CShop();
		void LoadBitMap();
		void OnShow();
		void OnMove(vector<CWeapon*>&weapons);
		void SetOnShow(bool state) { show = state; };
		void SetShowKind(UINT nChar);
		bool IsShow() { return show; };
		void BuyWeapon(bool confirm, vector<CWeapon*>&weapons);
	private:
		typedef  std::array<CMovingBitmap, 3> goods;
		vector<pair<string,pair<goods, int>>> weapons; //名字、圖片及售價
		vector<pair<CMovingBitmap, CInteger>> icon; 
		CMovingBitmap shop, select;
		CDifferentTime *time;
		bool show;
		int kind;
		int *coins;
	};
}
