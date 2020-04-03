#pragma once
namespace game_framework {
	class CHealthPoints {
	public:
		CHealthPoints(int width, int height, int frameColor, int bkColor, int bloodColor);
		void ShowHP(int x,int y,int percent); //��ܼg���A�ó]�m��m�M�ʤ���
	private:
		int bar_width;
		int bar_height;
		int percent;
		int frame;
		int background;
		int blood;
	};
}
