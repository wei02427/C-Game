#pragma once
namespace game_framework {
	class CBullet;
	class CGasoline;
	class CDifferentTime;
	class CFlameBullet :public CBullet
	{
	public:
		CFlameBullet(int px, int py,int x, int y);
		void LoadBitMap();
		void HitPlayer(CPlayer &player);
		void HitEnemy(CEnemy&){}; //�L�ͤ��ॴ�ۤv�P��A�G����
		void OnMove(CGameMap &map);
		~CFlameBullet();
	private:
		int desX, desY,sx,sy;
		float m;
		bool isUp, isLeft;
		CDifferentTime *time;
	};
}
