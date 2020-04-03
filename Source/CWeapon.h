#pragma once
#define GUN "gun"
#define MACHINEGUN "machinegun"
#define ROCKET "rocket"
#define LANDMINE "landmine"
#define GASONLINE "gasonline"
#define GRENADE "grenade"
#define WEAPONS_NUM 5
namespace game_framework {
	class CEnemy;
	class CBullet;
	class CGameMap;
	class CPlayer;
	class CBomb;
	class CWeapon {
	public:
		CWeapon();
		virtual ~CWeapon();
		virtual void LoadBitMap() = 0;
		virtual void OnMove(CGameMap & map, CPlayer &player);
		virtual void OnMove(CGameMap & map,CEnemy &enemy);
		virtual void OnShowBullet(CGameMap &map); //�]���Z���ɡA�l�u�ٻݭn�~�򭸦���ܡA�G���}��@
		virtual void OnShowGun(CGameMap &map);  //��ܪZ��
		virtual void Attack() = 0; //�o�g�l�u
		virtual void HitEnemy(vector<CEnemy*> &enemies); //�����ĤH
		virtual void HitPlayer(CPlayer &player);  //���i��ˮ`�|�i����ۤv
		virtual void HitGasonline(CBomb & gasoline); //�����T�o��
		virtual string GetType(); //�^�ǪZ������
		void AddBullet();  //�W�[�l�u�ƶq
		void OnShowInfo();  //��ܪZ����T
		int GetBulletsNum(); //���o�Ѿl�l�u�ƶq
	protected:
		bool Delay(int ms); //�Z���o�g������ɶ�
		string type;
		vector<CBullet*> bullets; //�Z�����l�u
		int wx, wy, direction, ms;
		int nBullets; //�Ѿl�l�u�ƶq
		int factor; //�Ϥ���j�j�p
		int cx, cy; //�Z��icon��m
		int addNum; //�C���W�[���l�u��
		CMovingBitmap weapon[4];
		CMovingBitmap icon;
		CInteger num;
	private:
		time_t tstart, tend;
	};
}