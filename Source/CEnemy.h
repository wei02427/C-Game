#pragma once
#include "aStar.h"
#define PLAYER 1
#define BASE 0
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �ĤHClass
	/////////////////////////////////////////////////////////////////////////////
	class CGameMap;
	class CPlayer;
	class CBase;
	class CHealthPoints;
	class CDifferentTime;
	class Cordinate;
	struct Node;
	class CEnemy
	{
	public:
		CEnemy();
		int GetValue(); //�^�������o���Ǫ����o��
		int GetBlood(); //���o��q
		void Damage(int dam); //����ˮ`
		bool GetIsAlive(); //�O�_�٬���
		void SetValue(int val); //���P�Z������ �����P����
		virtual int  GetX1();
		virtual int  GetY1();
		virtual int  GetX2();
		virtual int  GetY2();
		virtual void Hit(CPlayer& player) = 0; //�������a
		virtual void Hit(CBase& base) = 0; //�����ĤH
		virtual void OnMove(CPlayer &player, CBase &base, CGameMap &map) = 0; // ���ʼĤH
		virtual void OnShow(CGameMap &map) = 0;			// �N�ĤH�ϧζK��e��
		virtual ~CEnemy();
	protected:
		virtual void LoadBitMap() = 0;				// ���J�ϧ�
		CAnimation animation[3];		// �ĤH���ʵe
		CHealthPoints *hp;
		Cordinate *route;
		vector<Node> path, tmppath; //�ĤH���ʸ`�I���|
		Node nenemy, nplayer, nbase; //�ۨ��M�ؼи`�I
		bool isSearch = false;  //�O�_�����|
		bool is_alive, isHit;				// �O�_����
		int x, y;					
		int blood;
		int value = 0; //�o��
	};
}
