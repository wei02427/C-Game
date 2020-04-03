#pragma once
namespace game_framework {
	class CPlayer;
	class CGameMap;
	class CDifferentTime;
	class CProps {
	public:
		CProps();
		~CProps();
		virtual void LoadBitMap() = 0;
		void OnShow(CGameMap &map);
		void OnMove();
		bool IsTimesUp(); //回傳是否超過十秒，若超過道具就會消失
		CProps* IsGot(CPlayer &player);  //回傳到具類型，判斷是撿到哪種道具
	protected:
		int x, y;
		virtual CProps* ReturnType() = 0;
		CAnimation props;
		CDifferentTime *timer;
		int second;
	};
}