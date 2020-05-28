#ifndef ENEMY_H
#define ENEMY_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Util.h"
#include "Item.h"
#include "Health.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供一個敵人													   //
	//  												   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Enemy :public Character
	{
	public:
		Enemy();						//建構子，傳給Character角色名稱
		Enemy(int x, int y, int hp, string name, Hero *h, ELEMENT_ATTRIBUTE a);			//建構子，設定角色初始位置給Character()，方便vector一次建立
		virtual ~Enemy();
		virtual void LoadBitmap() = 0;				//加載敵人Bitmap
		virtual void OnShow(Maps *m) = 0;	//顯示敵人於畫面上
		virtual void OnMove(Maps *m) = 0;			//敵人移動

		virtual int GetX1() = 0;					//回傳最左側X值
		virtual int GetY1() = 0;					//回傳最上側Y值
		virtual int GetX2() = 0;					//回傳最右側X值
		virtual int GetY2() = 0;					//回傳最下側Y值
		string GetName();

		virtual void Initialize() = 0;				//初始化
										//英雄是否和此敵人所在同一位置，前身是cannotPass
		virtual bool intersect(int x1, int x2, int y1, int y2) = 0;
		int distanceToHero();
		/////////////////////////////////////////////////////////////////////////////
		// 設定Enemy的座標的函式們												   //
		/////////////////////////////////////////////////////////////////////////////

		void SetMovingDown(bool b);		//
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//

		void offsetHP(int offset, ELEMENT_ATTRIBUTE attribute);		//增減此Enemy的血量(enemys->at->heroExistingArea(的攻擊範圍作增減))
		//void showHp(Maps *m, int x, int y);
		void itemsOnMove(Maps *m);
		void itemsOnShow(Maps *m);
		bool isAlive();
		CRect * GetRect();				//目前還沒用到的垃圾(可能要同時在mygame.cpp同等地位呼叫時用，Hero也有一組)
		bool isAttack();
		bool isCounterAttribute(ELEMENT_ATTRIBUTE a, ELEMENT_ATTRIBUTE b);
		void knockBack();
	protected:
		Hero * hero_on_map;
		BloodBar blood_bar;
		vector<Item *> items;
		CRect EnemyRect;
		int _x, _y;
		int ini_x, ini_y;
		int hp;
		int attack;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;
		int _direction;
		ELEMENT_ATTRIBUTE _attribute;
		
	};
}

#endif // !ENEMY_H