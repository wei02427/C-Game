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
		int  GetX1();					// 左上角 x 座標
		int  GetY1();					// 左上角 y 座標
		int  GetX2();					// 右下角 x 座標
		int  GetY2();					// 右下角 y 座標
		void Initialize();				// 初始player
		void LoadBitMap();				// 載入圖形
		void OnMove(CGameMap&, vector<CEnemy*> &enemies);					// 移動玩家
		void OnShow(CGameMap&);//CGameMap &map);					// 將玩家圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetIsAttack(bool flag);  //設定是否攻擊
		void SetDirection(int);  //設定移動方向
		void Attack(); //武器攻擊(武器OnMove)
		void Damage(int damage); //受到傷害
		void GetScore(int point); //得分
		void GetProps(vector<CProps*> &props); //得到道具
		void OnShowInfo();  //顯示武器、分數、金錢資訊
		void SwitchWeapon(); //換武器
		int Getblood() { return blood; }; //取得血量
		int *GetCoins() { return &coins; }; //取得金幣
		int GetDirection();  //取得玩家方向
		int CurrentScore(); //取得目前分數
		CBackpack& GetBackpack(); //獲得玩家背包
	protected:
		CAnimation animation[4];		// 玩家的動畫
		CHealthPoints *hp;
		CWeapon **weapon;
		CBackpack *backpack;  //玩家擁有背包，並可存取武器
		CMovingBitmap icon[2];
		CInteger num[2];
		int x, y;				// 玩家左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isAttack;		
		int blood;
		int direction;
		int score;
		int coins;
		time_t tstart, tend;
	};

}
