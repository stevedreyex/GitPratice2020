#ifndef HERO_H
#define HERO_H

#include "Util.h"
#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
#include "Attack.h"
#include "Item.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class Enemy;
	class Item;
	class Hero :public Character
	{
	public:
		Hero();
		~Hero();
		void LoadBitmap();
		void OnShow(Maps *m) override;
		void OnMove(Maps *m, vector<Enemy*> * enemys);

		int GetX1();					//回傳最左側X值
		int GetY1();					//回傳最上側Y值
		int GetX2();					//回傳最右側X值
		int GetY2();					//回傳最下側Y值
		
		int GetQCoolDown();
		int GetECoolDown();
		int getHP();
		int getFullHP();
		int get_attack_fire();
		int get_attack_ice();
		int get_attack_plant();
		ELEMENT_ATTRIBUTE getCurrentAttribute();
		vector<Item *> * getItemsOfPlayer();

		void Initialize();
		/////////////////////////////////////////////////////////////////////////////
		// 設定Hero的座標的函式們													   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);
		void SetMovingUp(bool b);
		void SetMovingLeft(bool b);
		void SetMovingRight(bool b);
		void SetXY(int num_x, int num_y);
		/////////////////////////////////////////////////////////////////////////////
		// 設定Hero使用技能的函式們												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetUsingA(bool b);
		void SetUsingQ(bool b);
		void SetUsingW(bool b);
		void SetUsingE(bool b);
		void SetUsingR(bool b);
		void SetElementAttribute(ELEMENT_ATTRIBUTE e);
		void SetAllCoolDownToZero();
		/////////////////////////////////////////////////////////////////////////////
		// 前身是cantPass，應該是本程式最重要的函式之一
		// 1. 角色碰到敵人會扣血
		// 2. 如果敵人在攻擊範圍內，且在攻擊狀態下，敵人會被扣血
		/////////////////////////////////////////////////////////////////////////////
		bool gonnaBleeding(vector<Enemy*> * enemys, int x1, int x2, int y1, int y2);
		void offsetHp(int n);
		void addHp(int n);
		void addAttack(int n, ELEMENT_ATTRIBUTE attribute);
		void addItem(Item * item);
		void slide(Maps *m);
		/////////////////////////////////////////////////////////////////////////////
		bool isMoving();					// 在動
		bool isAlive();
		bool isInFinishArea(Maps *m);
		bool isUsingSkill();			// 如果在用技能，return true	
		void heroShow(Maps *m);
		bool intercect(int x1, int x2, int y1, int y2);
		/////////////////////////////////////////////////////////////////////////////
		void normalAttackMove();		// 普功的Move
		void normalAttackShow(Maps *m);		// 普功的Show
		void showHeroStatus();			//顯示hp 技能冷卻時間
		void gettingAttackedShow();
		/////////////////////////////////////////////////////////////////////////////
		void skillQ();
		void skillQMove(Maps *m);
		void skillQShow(Maps *m);
		void useItem(int n);

		void skillW();
		void skillWMove(Maps *m);
		//void skillWShow();

		/*void skillE();*/
		void skillEMove();
		void skillEShow();

		/*void skillR();
		void skillRMove();
		void skillRShow();*/
		/////////////////////////////////////////////////////////////////////////////
		

	private:
		CMovingBitmap heroL, heroR;
		CAnimation walkingLeft;
		CAnimation walkingRight;
		CAnimation skillE;
		CAnimation normalAttackL; // 向左普功動畫
		CAnimation normalAttackR; // 向右普功動畫
		CAnimation get_attacked;
		
		BloodBar blood_bar;
		CRect RectHero;
		int x, y;
		int hp;
		int attack_fire;
		int attack_ice;
		int attack_plant;
		ELEMENT_ATTRIBUTE _attribute;
		vector<Item *> items;
		
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttack;
		bool isUsingA;
		bool isUsingQ;
		bool isUsingW;
		bool isUsingE;
		bool isUsingR;
		bool is_getting_attacked;
		int status;
		bool directionLR; // 0為左 1為右
		bool directionUD; // 0為上 1為下
		int skillTimes;   // 用來數跑了幾次CAnimation。
		Attack q_attack;
		///冷卻時間
		int skill_q_cool_down; //cool down在每個skill的move function裡每秒-30
		int skill_w_cool_down;
		int skill_e_cool_down;

		//滑起來
		int slide_right, slide_left, slide_up, slide_down;
		bool isSlide;
	};
}

#endif // !HERO_H
