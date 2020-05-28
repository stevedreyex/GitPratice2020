#ifndef ABOSS_H
#define ABOSS_H

#include "Maps.h"
#include "Character.h"
#include "BossBloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѥ@�ӼĤH													   //
	//		 																	//
	/////////////////////////////////////////////////////////////////////////////

	class ABoss :public Enemy
	{
	public:
		ABoss();						//�غc�l�A�ǵ�Character����W��
		ABoss(int x, int y, Hero *h);	//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		~ABoss();
		void LoadBitmap();					//�[���ĤHBitmap
		void OnShow(Maps *m) override;		//��ܼĤH��e���W
		void OnMove(Maps *m);				//�ĤH����

		int GetX1();						//�^�ǳ̥���X��
		int GetY1();						//�^�ǳ̤W��Y��
		int GetX2();						//�^�ǳ̥k��X��
		int GetY2();						//�^�ǳ̤U��Y��

		void Initialize()override;			//��l��
											//�^���O�_�M���ĤH�Ҧb�P�@��m�A�e���OcannotPass
		bool intersect(int x1, int x2, int y1, int y2) override;

		/////////////////////////////////////////////////////////////////////////////
		// �]�wEnemy���y�Ъ��禡��												   //
		/////////////////////////////////////////////////////////////////////////////

		void SetMovingDown(bool b);		//
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//
		void movement(Maps *m);

		//void attacked(int n, ELEMENT_ATTRIBUTE a);		//�W�Enemy����q(enemys->at->heroExistingArea(�������d��@�W��))
		CRect * GetRect();					//�ثe�٨S�Ψ쪺�U��(�i��n�P�ɦbmygame.cpp�P���a��I�s�ɥΡAHero�]���@��)
		//�Ψӧ�����
		void attack();
		void iceAttack();
		void iceAttackMove(Maps *m);
		void iceAttackShow(Maps *m);
	private:
		BossBloodBar boss_blood_bar;
		CAnimation walkingLeft;
		CAnimation walkingRight;
		CAnimation normalAttackL;
		CAnimation normalAttackR;
		CAnimation prepare_attackL;
		CAnimation prepare_attackR;
		CAnimation back_to_walkL;
		CAnimation back_to_walkR;
		enum status {
			WALKING,
			PREPARE,
			ATTACK,
			BACK_TO_WALK
		};
		int status;
		int step_size;
		int attack_damage;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		bool isAttacking;
		int attack_cool_down;
		int status_counter;
		int move_or_not;
		int time_bump_into_sth;
		int attack_target_location_x, attack_target_location_y;
		Attack q_attack;
		Attack ice_attack[18];
		int skillTimes;
		bool isUsingQ;

	};
}

#endif 