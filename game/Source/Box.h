#ifndef BOX_H
#define BOX_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���Ѥ@�ӼĤH													   //
	//  												   //
	/////////////////////////////////////////////////////////////////////////////

	class Box :public Enemy
	{
	public:
		Box();						//�غc�l�A�ǵ�Character����W��
		Box(int x, int y, Hero *h);			//�غc�l�A�]�w�����l��m��Character()�A��Kvector�@���إ�
		~Box();
		void LoadBitmap();				//�[���ĤHBitmap
		void OnShow(Maps *m) override;	//��ܼĤH��e���W
		void OnMove(Maps *m);			//�ĤH����

		int GetX1();					//�^�ǳ̥���X��
		int GetY1();					//�^�ǳ̤W��Y��
		int GetX2();					//�^�ǳ̥k��X��
		int GetY2();					//�^�ǳ̤U��Y��

		void Initialize()override;				//��l��
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

		//void offsetHP(int offset) override;		//�W�Enemy����q(enemys->at->heroExistingArea(�������d��@�W��))
		CRect * GetRect();				//�ثe�٨S�Ψ쪺�U��(�i��n�P�ɦbmygame.cpp�P���a��I�s�ɥΡAHero�]���@��)
		//�Ψӧ�����
		void attack();
		void attackShow(Maps *m);
	private:
		CMovingBitmap box;
		CMovingBitmap damaged_box;
		int rand_num;
		int attack_damage;
		bool isMovingRight;
		bool isMovingLeft;
		bool isMovingUp;
		bool isMovingDown;
		int attack_cool_down;

	};
}

#endif // !Scarecrow_H