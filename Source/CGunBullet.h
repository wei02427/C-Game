#pragma once
namespace game_framework {
	class CBullet;
	class CGasoline;
	class CGunBullet:public CBullet
	{
	public:
		CGunBullet(int direction, int x, int y);
		void LoadBitMap();	
		void HitPlayer(CPlayer &) {};
		~CGunBullet();
	};
}
