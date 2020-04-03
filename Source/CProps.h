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
		bool IsTimesUp(); //�^�ǬO�_�W�L�Q��A�Y�W�L�D��N�|����
		CProps* IsGot(CPlayer &player);  //�^�Ǩ�������A�P�_�O�ߨ���عD��
	protected:
		int x, y;
		virtual CProps* ReturnType() = 0;
		CAnimation props;
		CDifferentTime *timer;
		int second;
	};
}