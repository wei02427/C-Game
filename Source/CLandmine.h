#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �a�pclass
	/////////////////////////////////////////////////////////////////////////////
	class CBullet;
	class CLandmine :public CBullet
	{
	public:
		CLandmine(int px, int py);
		void LoadBitMap();			// ���J�ϧ�
		void HitEnemy(CEnemy&enemy);
		void HitPlayer(CPlayer&);
		~CLandmine();
	};
}
