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
	// �o��class���Ѥ@�ӼĤH													   //
	//  												   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Enemy :public Character
	{
	public:
		Enemy();						//�غc�l�A�ǵ�Character����W��
		Enemy(int x, int y, int hp, string name, Hero *h, ELEMENT_ATTRIBUTE a);			//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		virtual ~Enemy();
		virtual void LoadBitmap() = 0;				//�[���ĤHBitmap
		virtual void OnShow(Maps *m) = 0;	//��ܼĤH��e���W
		virtual void OnMove(Maps *m) = 0;			//�ĤH����

		virtual int GetX1() = 0;					//�^�ǳ̥���X��
		virtual int GetY1() = 0;					//�^�ǳ̤W��Y��
		virtual int GetX2() = 0;					//�^�ǳ̥k��X��
		virtual int GetY2() = 0;					//�^�ǳ̤U��Y��
		string GetName();

		virtual void Initialize() = 0;				//��l��
										//�^���O�_�M���ĤH�Ҧb�P�@��m�A�e���OcannotPass
		virtual bool intersect(int x1, int x2, int y1, int y2) = 0;
		int distanceToHero();
		/////////////////////////////////////////////////////////////////////////////
		// �]�wEnemy���y�Ъ��禡��												   //
		/////////////////////////////////////////////////////////////////////////////

		void SetMovingDown(bool b);		//
		void SetMovingUp(bool b);		//
		void SetMovingLeft(bool b);		//
		void SetMovingRight(bool b);	//
		void SetXY(int x, int y);		//

		void offsetHP(int offset, ELEMENT_ATTRIBUTE attribute);		//�W�Enemy����q(enemys->at->heroExistingArea(�������d��@�W��))
		//void showHp(Maps *m, int x, int y);
		void itemsOnMove(Maps *m);
		void itemsOnShow(Maps *m);
		bool isAlive();
		CRect * GetRect();				//�ثe�٨S�Ψ쪺�U��(�i��n�P�ɦbmygame.cpp�P���a��I�s�ɥΡAHero�]���@��)
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