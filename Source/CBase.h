#pragma once
namespace game_framework {
	class CHealthPoints;
	class CGameMap;
	class CDifferentTime;
	class CBase {
	public:
		CBase();
		~CBase();
		void LoadBitMap(CGameMap& map);
		void OnShow(CGameMap& map);
		void OnMove();
		void Damage(int damage);
		void Initialize();
		int GetBlood();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
	private:
		CAnimation diamond;
		CMovingBitmap base;
		CHealthPoints *hp;
		int blood;
		static int x, y;
		int dx, dy, distance, direction;
		CDifferentTime *time;
	};
}
