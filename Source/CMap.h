#pragma once
namespace game_framework {
	class CGameMap
	{
	public:
		CGameMap();
		void LoadBitMap();
		void OnShow();
		void OnMove();
		int ScreenX(int);
		int ScreenY(int);
		void SetIsleft(bool);
		void SetIsRight(bool);
		void SetIsDown(bool);
		void SetIsUp(bool);
		void SetValue(int x,int y,char value);
		void Initialize();
		int IsEmpty(int x, int y);	//是否該點為障礙物
	private:
		CMovingBitmap map;
		vector<vector<char>> data; //存放地圖目前的障礙物和其他資訊
		const int MH, MW;
		bool isLeft;	//是否碰到左邊界
		bool isRight;	//是否碰到右邊界
		bool isDown;  //是否碰到下邊界
		bool isUp;//是否碰到上邊界
		int sx, sy;
	};
}

