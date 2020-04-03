#pragma once
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//�l�uclass
	/////////////////////////////////////////////////////////////////////////////
	class CEnemy;
	class CGameMap;
	class CPlayer;
	class CGasoline;
	class CBullet
	{
	public:
		CBullet();
		virtual void LoadBitMap() = 0;		
		virtual void OnMove(CGameMap&);			
		virtual void OnShow(CGameMap&);			
		virtual void HitEnemy(CEnemy&);
		virtual void HitPlayer(CPlayer&) = 0; 
		virtual void HitGasoline(CGasoline *gasoline);
		virtual bool GetIsHit(); //�O�_�w�g�]�쪫��
		virtual ~CBullet();
	protected:
		int x, y;			
		int velocity;			
		int damage; //�l�u���ˮ`
		int direction; //��V
		int distance; //�ثe����Z��
		int range;  //�̤j����Z��
		int vaule; //���P�l�u�����P�o��
		float fvelocity, fdistance;
		bool isHit;
		CAnimation animation;	
		CMovingBitmap bulletsBmp[4];
	};
}
