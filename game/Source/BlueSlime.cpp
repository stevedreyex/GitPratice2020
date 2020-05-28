#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <ctgmath>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"
#include "BlueSlime.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"

namespace game_framework {

	//�Y�bCharacter�MEnemy�������@��hp�A��ܪ�����Character��������

	BlueSlime::BlueSlime()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}

	BlueSlime::BlueSlime(int x, int y, Hero *h) : Enemy(x, y, 1200, "BlueSlime", h, ICE)
	{
		attack_damage = 70;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));
	}

	BlueSlime::~BlueSlime()
	{
	}

	void BlueSlime::LoadBitmap()
	{
		blood_bar.loadBloodBar();
		/////�����D��
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->load();
		}
		/////�Ǫ����ʵe
		char *filename1_1[3] = { ".\\bitmaps\\blueslimeL1.bmp",".\\bitmaps\\blueslimeL2.bmp",".\\bitmaps\\blueslimeL3.bmp" };
		for (int i = 0; i < 3; i++)	// ���J�ʵe(��6�i�ϧκc��)
			walkingLeft.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		char *filename1_2[3] = { ".\\bitmaps\\blueslimeR1.bmp",".\\bitmaps\\blueslimeR2.bmp",".\\bitmaps\\blueslimeR3.bmp"};
		for (int i = 0; i < 3; i++)	// ���J�ʵe(��6�i�ϧκc��)
			walkingRight.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		/////�������ʵe
		char *filename2_1[5] = { ".\\bitmaps\\blueslime_attackL1.bmp",".\\bitmaps\\blueslime_attackL2.bmp",".\\bitmaps\\blueslime_attackL3.bmp", ".\\bitmaps\\blueslime_attackL4.bmp", ".\\bitmaps\\blueslime_attackL5.bmp" };
		for (int i = 0; i < 5; i++)	// ���J�ʵe(��6�i�ϧκc��)
			normalAttackL.AddBitmap(filename2_1[i], RGB(0, 0, 0));
		normalAttackL.SetDelayCount(3);
		char *filename2_2[5] = { ".\\bitmaps\\blueslime_attackR1.bmp",".\\bitmaps\\blueslime_attackR2.bmp",".\\bitmaps\\blueslime_attackR3.bmp", ".\\bitmaps\\blueslime_attackR4.bmp", ".\\bitmaps\\blueslime_attackR5.bmp" };
		for (int i = 0; i < 5; i++)	// ���J�ʵe(��6�i�ϧκc��)
			normalAttackR.AddBitmap(filename2_2[i], RGB(0, 0, 0));
		normalAttackR.SetDelayCount(3);
	}

	void BlueSlime::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		if (isAlive()) {
			attack();
			attack_cool_down -= 1;
			walkingLeft.OnMove();
			walkingRight.OnMove();
			movement(m);
		}
		if (!isAlive()) {
			itemsOnMove(m);
		}
	}

	void BlueSlime::OnShow(Maps *m)
	{
		if (isAlive()) {
			if (_direction == 0)
			{
				if (isAttacking) {
					attackShow(m);
					blood_bar.setXY(GetX1(), GetY1());
					blood_bar.showBloodBar(m, hp);
				}
				else {
					walkingLeft.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					//enemy.SetTopLeft(x, y);
					walkingLeft.OnShow();
					blood_bar.setXY(GetX1(), GetY1());
					blood_bar.showBloodBar(m, hp);
				}
			}
			else
			{
				if (isAttacking) {
					attackShow(m);
					blood_bar.setXY(GetX1(), GetY1());
					blood_bar.showBloodBar(m, hp);
				}
				else {
					walkingRight.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					//enemy.SetTopLeft(x, y);
					walkingRight.OnShow();
					blood_bar.setXY(GetX1(), GetY1());
					blood_bar.showBloodBar(m, hp);
				}
			}
			
		}
		if (!isAlive()) {
			itemsOnShow(m);
		}

	}

	int BlueSlime::GetX1()
	{
		return _x;
	}

	int BlueSlime::GetY1()
	{
		return _y;
	}

	int BlueSlime::GetX2()
	{
		return _x + walkingRight.Width();
	}

	int BlueSlime::GetY2()
	{
		return _y + walkingRight.Height();
	}

	void BlueSlime::Initialize() {
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking =  false;
		hp = 1200;
		blood_bar.setFullHP(hp);
		walkingLeft.SetDelayCount(5);
		walkingRight.SetDelayCount(5);
		///�D��
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->Initialize();
		}
	}

	bool BlueSlime::intersect(int x1, int x2, int y1, int y2)
	{
		//�U�����@�ǥ[��B��O�]���A�_��H��Bitmap������_��H������j�Ӧh�C
		if (isAlive()) {
			if (x2 >= _x + 20 && x1 <= _x + walkingRight.Width() - 20 && y2 >= _y + 30 && y1 <= _y + walkingRight.Height() - 15) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;

	}

	//bool Enemy::cannotPass(Hero * hero)
	//{
	//	// �˴����l�Һc�����x�άO�_�I��y
	//	return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	//}
	////���ڤ����D�쩳�o�Ӽg�bmap�٬Ohero�٬Oenemy�n�A���޿�O�o�Mhero���୫�|
	void BlueSlime::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void BlueSlime::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void BlueSlime::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void BlueSlime::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void BlueSlime::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void BlueSlime::movement(Maps *m)
	{
		int x = GetX1();
		int y1 = GetY1() ;
		int step_size = rand() % 3;
		if (distanceToHero() < 500) {
			if (hero_on_map->GetX1() > x && m->isEmpty(GetX2() + step_size, y1) && m->isEmpty(GetX2() + step_size, GetY2())) {
				_direction = 1;
				_x += step_size;
			}
			if (hero_on_map->GetX1() < x && m->isEmpty(x - step_size, y1) && m->isEmpty(x - step_size, GetY2())) {
				_direction = 0;
				_x -= step_size;
			}
			if (hero_on_map->GetY1() > y1 && m->isEmpty(x, GetY2() + step_size) && m->isEmpty(GetX2(), GetY2() + step_size)) {
				_y += step_size;
			}
			if (hero_on_map->GetY1() < y1 && m->isEmpty(x, y1 - step_size) && m->isEmpty(GetX2(), y1 - step_size)) {
				_y -= step_size;
			}
		}
		
		
	}




	CRect * BlueSlime::GetRect()
	{
		return &EnemyRect;
	}

	void BlueSlime::attack()
	{
		if (intersect(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2()) && attack_cool_down <= 0 && !isAttacking) {
			CAudio::Instance()->Play(AUDIO_HITTING);
			isAttacking = true;
			hero_on_map->offsetHp(attack_damage);
		}
		normalAttackR.OnMove();
		if (!isAttacking) {
			normalAttackR.Reset();
		}
	}

	void BlueSlime::attackShow(Maps * m)
	{
		if (isAttacking) {
			normalAttackR.SetTopLeft(m->screenX(_x), m->screenY(_y));
			normalAttackR.OnShow();
			if (normalAttackR.IsFinalBitmap()) {
				isAttacking = false;
				attack_cool_down = 90; //�C���������j3��
			}
		}
	}

}
