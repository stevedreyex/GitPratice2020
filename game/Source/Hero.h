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
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
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

		int GetX1();					//�^�ǳ̥���X��
		int GetY1();					//�^�ǳ̤W��Y��
		int GetX2();					//�^�ǳ̥k��X��
		int GetY2();					//�^�ǳ̤U��Y��
		
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
		// �]�wHero���y�Ъ��禡��													   //
		/////////////////////////////////////////////////////////////////////////////
		void SetMovingDown(bool b);
		void SetMovingUp(bool b);
		void SetMovingLeft(bool b);
		void SetMovingRight(bool b);
		void SetXY(int num_x, int num_y);
		/////////////////////////////////////////////////////////////////////////////
		// �]�wHero�ϥΧޯ઺�禡��												   //
		/////////////////////////////////////////////////////////////////////////////
		void SetUsingA(bool b);
		void SetUsingQ(bool b);
		void SetUsingW(bool b);
		void SetUsingE(bool b);
		void SetUsingR(bool b);
		void SetElementAttribute(ELEMENT_ATTRIBUTE e);
		void SetAllCoolDownToZero();
		/////////////////////////////////////////////////////////////////////////////
		// �e���OcantPass�A���ӬO���{���̭��n���禡���@
		// 1. ����I��ĤH�|����
		// 2. �p�G�ĤH�b�����d�򤺡A�B�b�������A�U�A�ĤH�|�Q����
		/////////////////////////////////////////////////////////////////////////////
		bool gonnaBleeding(vector<Enemy*> * enemys, int x1, int x2, int y1, int y2);
		void offsetHp(int n);
		void addHp(int n);
		void addAttack(int n, ELEMENT_ATTRIBUTE attribute);
		void addItem(Item * item);
		void slide(Maps *m);
		/////////////////////////////////////////////////////////////////////////////
		bool isMoving();					// �b��
		bool isAlive();
		bool isInFinishArea(Maps *m);
		bool isUsingSkill();			// �p�G�b�Χޯ�Areturn true	
		void heroShow(Maps *m);
		bool intercect(int x1, int x2, int y1, int y2);
		/////////////////////////////////////////////////////////////////////////////
		void normalAttackMove();		// ���\��Move
		void normalAttackShow(Maps *m);		// ���\��Show
		void showHeroStatus();			//���hp �ޯ�N�o�ɶ�
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
		CAnimation normalAttackL; // �V�����\�ʵe
		CAnimation normalAttackR; // �V�k���\�ʵe
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
		bool directionLR; // 0���� 1���k
		bool directionUD; // 0���W 1���U
		int skillTimes;   // �ΨӼƶ]�F�X��CAnimation�C
		Attack q_attack;
		///�N�o�ɶ�
		int skill_q_cool_down; //cool down�b�C��skill��move function�̨C��-30
		int skill_w_cool_down;
		int skill_e_cool_down;

		//�ư_��
		int slide_right, slide_left, slide_up, slide_down;
		bool isSlide;
	};
}

#endif // !HERO_H
