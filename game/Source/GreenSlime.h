#ifndef GREENSLIME_H
#define GREENSLIME_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供一個敵人													   //
	//		 																	//
	/////////////////////////////////////////////////////////////////////////////

	class GreenSlime :public Enemy
	{
	public:
		GreenSlime();						//建構子，傳給Character角色名稱
		GreenSlime(int x, int y, Hero *h);	//建構子，設定角色初始位置給Character()，方便vector一次建立
		~GreenSlime();
		void LoadBitmap();					//加載敵人Bitmap
		void OnShow(Maps *m) override;		//顯示敵人於畫面上
		void OnMove(Maps *m);				//敵人移動

		int GetX1();						//回傳最左側X值
		int GetY1();						//回傳最上側Y值
		int GetX2();						//回傳最右側X值
		int GetY2();						//回傳最下側Y值

		void Initialize()override;			//初始化
											//英雄是否和此敵人所在同一位置，前身是cannotPass
		bool intersect(int x1, int x2, int y1, int y2) override;

		/////////////////////////////////////////////////////////////////////////////
		// 設定Enemy的座標的函式們												   //
		/////////////////////////////////////////////////////////////////////////////

		void SetMovingDown(bool b);		//
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//
		void movement(Maps *m);

		//void attacked(int n, ELEMENT_ATTRIBUTE a);		//增減此Enemy的血量(enemys->at->heroExistingArea(的攻擊範圍作增減))
		CRect * GetRect();					//目前還沒用到的垃圾(可能要同時在mygame.cpp同等地位呼叫時用，Hero也有一組)
		//用來攻擊的
		void attack();
		void attackShow(Maps *m);
	private:
		CAnimation walkingLeft;
		CAnimation walkingRight;
		CAnimation normalAttackL;
		CAnimation normalAttackR;
		int attack_damage;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;
		int attack_cool_down;
		int move_or_not;
		int time_bump_into_sth;

	};
}

#endif // !Scarecrow_H