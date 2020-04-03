#pragma once
namespace game_framework {
	class CHealthPoints {
	public:
		CHealthPoints(int width, int height, int frameColor, int bkColor, int bloodColor);
		void ShowHP(int x,int y,int percent); //顯示寫條，並設置位置和百分比
	private:
		int bar_width;
		int bar_height;
		int percent;
		int frame;
		int background;
		int blood;
	};
}
