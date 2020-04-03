#pragma once
namespace game_framework {
	class CDifferentTime;
	class CGameMenu {
	public:
		CGameMenu();
		void LoadBitMap();
		void OnShow(bool result = false);
		int SwitchMenu(UINT nChar); //¤Á´«µæ³æ
		~CGameMenu();
	private:
		int x ;
		int y ;
		bool IsStart;
		CMovingBitmap menu[7];
		CMovingBitmap select[2];
		CDifferentTime *timer;
		int page;
	};
}
