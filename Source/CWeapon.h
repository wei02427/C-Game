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
		virtual void OnShowBullet(CGameMap &map); //因換武器時，子彈還需要繼續飛行顯示，故分開實作
		virtual void OnShowGun(CGameMap &map);  //顯示武器
		virtual void Attack() = 0; //發射子彈
		virtual void HitEnemy(vector<CEnemy*> &enemies); //攻擊敵人
		virtual void HitPlayer(CPlayer &player);  //有可能傷害會波擊到自己
		virtual void HitGasonline(CBomb & gasoline); //攻擊汽油桶
		virtual string GetType(); //回傳武器類型
		void AddBullet();  //增加子彈數量
		void OnShowInfo();  //顯示武器資訊
		int GetBulletsNum(); //取得剩餘子彈數量
	protected:
		bool Delay(int ms); //武器發射的延遲時間
		string type;
		vector<CBullet*> bullets; //武器的子彈
		int wx, wy, direction, ms;
		int nBullets; //剩餘子彈數量
		int factor; //圖片放大大小
		int cx, cy; //武器icon位置
		int addNum; //每次增加的子彈數
		CMovingBitmap weapon[4];
		CMovingBitmap icon;
		CInteger num;
	private:
		time_t tstart, tend;
	};
}