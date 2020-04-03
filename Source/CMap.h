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
		int IsEmpty(int x, int y);	//�O�_���I����ê��
	private:
		CMovingBitmap map;
		vector<vector<char>> data; //�s��a�ϥثe����ê���M��L��T
		const int MH, MW;
		bool isLeft;	//�O�_�I�쥪���
		bool isRight;	//�O�_�I��k���
		bool isDown;  //�O�_�I��U���
		bool isUp;//�O�_�I��W���
		int sx, sy;
	};
}

