#pragma once
namespace game_framework {

	class CGameMap;
	class CBullet;
	class CBomb;
	class CEnemy;
	class CHealthPoints;
	class CWeapon;
	class CProps;
	class CBackpack;
	class CPlayer
	{
	public:
		CPlayer();
		~CPlayer();
		int  GetX1();					// ���W�� x �y��
		int  GetY1();					// ���W�� y �y��
		int  GetX2();					// �k�U�� x �y��
		int  GetY2();					// �k�U�� y �y��
		void Initialize();				// ��lplayer
		void LoadBitMap();				// ���J�ϧ�
		void OnMove(CGameMap&, vector<CEnemy*> &enemies);					// ���ʪ��a
		void OnShow(CGameMap&);//CGameMap &map);					// �N���a�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetIsAttack(bool flag);  //�]�w�O�_����
		void SetDirection(int);  //�]�w���ʤ�V
		void Attack(); //�Z������(�Z��OnMove)
		void Damage(int damage); //����ˮ`
		void GetScore(int point); //�o��
		void GetProps(vector<CProps*> &props); //�o��D��
		void OnShowInfo();  //��ܪZ���B���ơB������T
		void SwitchWeapon(); //���Z��
		int Getblood() { return blood; }; //���o��q
		int *GetCoins() { return &coins; }; //���o����
		int GetDirection();  //���o���a��V
		int CurrentScore(); //���o�ثe����
		CBackpack& GetBackpack(); //��o���a�I�]
	protected:
		CAnimation animation[4];		// ���a���ʵe
		CHealthPoints *hp;
		CWeapon **weapon;
		CBackpack *backpack;  //���a�֦��I�]�A�åi�s���Z��
		CMovingBitmap icon[2];
		CInteger num[2];
		int x, y;				// ���a���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isAttack;		
		int blood;
		int direction;
		int score;
		int coins;
		time_t tstart, tend;
	};

}
