#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <ctgmath>
#include "audio.h"
#include "gamelib.h"
#include "Arrow.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"
#include "RedGoblin.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"

namespace game_framework {

	//若在Character和Enemy中都有一個hp，選擇直接用Character中的那個

	RedGoblin::RedGoblin()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}

	RedGoblin::RedGoblin(int x, int y, Hero *h) : Enemy(x, y, 1200, "RedGoblin", h, FIRE)
	{
		attack_damage = 20;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));
	}

	RedGoblin::~RedGoblin()
	{
	}

	void RedGoblin::LoadBitmap()
	{
		blood_bar.loadBloodBar();
		/////掉落道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->load();
		}
		/////怪物的動畫
		char *filename1_1[4] = { ".\\bitmaps\\redgoblinL1.bmp",".\\bitmaps\\redgoblinL2.bmp",".\\bitmaps\\redgoblinL3.bmp", ".\\bitmaps\\redgoblinL4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			walkingLeft.AddBitmap(filename1_1[i], RGB(1, 1, 1));
		char *filename1_2[4] = { ".\\bitmaps\\redgoblinR1.bmp",".\\bitmaps\\redgoblinR2.bmp",".\\bitmaps\\redgoblinR3.bmp", ".\\bitmaps\\redgoblinR4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			walkingRight.AddBitmap(filename1_2[i], RGB(1, 1, 1));
		/////攻擊的動畫
		char *filename2_1[5] = { ".\\bitmaps\\redslime_attackL1.bmp",".\\bitmaps\\redslime_attackL2.bmp",".\\bitmaps\\redslime_attackL3.bmp", ".\\bitmaps\\redslime_attackL4.bmp", ".\\bitmaps\\redslime_attackL5.bmp" };
		for (int i = 0; i < 5; i++)	// 載入動畫(由6張圖形構成)
			normalAttackL.AddBitmap(filename2_1[i], RGB(0, 0, 0));
		normalAttackL.SetDelayCount(3);
		char *filename2_2[5] = { ".\\bitmaps\\redslime_attackR1.bmp",".\\bitmaps\\redslime_attackR2.bmp",".\\bitmaps\\redslime_attackR3.bmp", ".\\bitmaps\\redslime_attackR4.bmp", ".\\bitmaps\\redslime_attackR5.bmp" };
		for (int i = 0; i < 5; i++)	// 載入動畫(由6張圖形構成)
			normalAttackR.AddBitmap(filename2_2[i], RGB(0, 0, 0));
		normalAttackR.SetDelayCount(3);
		arr.loadBitmap();
	}

	void RedGoblin::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		if (isAlive()) {
			//attack();
			attack_cool_down -= 1;
			//arrowAttackCD -= 1;
			walkingLeft.OnMove();
			walkingRight.OnMove();
			movement(m);
			arrowAttack();
			arr.OnMove(m);
			arrowAttackMove(m);
			if (arrowAttackCD != 0) {
				arrowAttackCD--;
			}
		}
		if (!isAlive()) {
			itemsOnMove(m);
		}
	}

	void RedGoblin::OnShow(Maps *m)
	{
		if (isAlive()) {
			if (_direction == 0)
			{
				if (isAttacking) {
					//attackShow(m);
					blood_bar.setXY(GetX1(), GetY1()-16);
					blood_bar.showBloodBar(m, hp - 16);
					arrowAttackShow(m);
				}
				else {
					
					//enemy.SetTopLeft(x, y);
					
					blood_bar.setXY(GetX1(), GetY1()-16);
					blood_bar.showBloodBar(m, hp);
					//arrowAttackShow(m);

				}
				walkingLeft.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
				walkingLeft.OnShow();
			}
			else
			{
				if (isAttacking) {
					//attackShow(m);
					blood_bar.setXY(GetX1(), GetY1()-16);
					blood_bar.showBloodBar(m, hp);
					arrowAttackShow(m);

				}
				else {
					
					blood_bar.setXY(GetX1(), GetY1()-16);
					blood_bar.showBloodBar(m, hp);
					//arrowAttackShow(m);

				}
				walkingRight.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
				//enemy.SetTopLeft(x, y);
				walkingRight.OnShow();
			}
			
		}
		if (!isAlive()) {
			itemsOnShow(m);
		}

	}

	int RedGoblin::GetX1()
	{
		return _x;
	}

	int RedGoblin::GetY1()
	{
		return _y;
	}

	int RedGoblin::GetX2()
	{
		return _x + walkingRight.Width();
	}

	int RedGoblin::GetY2()
	{
		return _y + walkingRight.Height();
	}

	void RedGoblin::Initialize() {
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking = attackIsFlying = false;
		hp = 1200;
		arrorClock = 0;
		arrowAttackCD = 0;
		blood_bar.setFullHP(hp);
		walkingLeft.SetDelayCount(5);
		walkingRight.SetDelayCount(5);
		///道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->Initialize();
		}
	}

	bool RedGoblin::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，稻草人的Bitmap本身比稻草人的身體大太多。
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
	//	// 檢測擦子所構成的矩形是否碰到球
	//	return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	//}
	////其實我不知道到底這個寫在map還是hero還是enemy好，但邏輯是她和hero不能重疊
	void RedGoblin::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void RedGoblin::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void RedGoblin::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void RedGoblin::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void RedGoblin::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void RedGoblin::movement(Maps *m)
	{
		int x = GetX1();
		int y1 = GetY1() ;
		if (_x > hero_on_map->GetX1()) {
			_direction = 0;
		}
		else {
			_direction = 1;
		}
		int step_size = rand() % 3;
		if (_x != hero_on_map->GetX1() && _y != hero_on_map->GetY1()) {
			if (abs(_x - hero_on_map->GetX1()) > abs(_y - hero_on_map->GetY1()))
			{
				if (_y > hero_on_map->GetY1())
					_y -= step_size;
				else
					_y += step_size;
			}
			else
			{
				if (_x > hero_on_map->GetX1())
					_x -= step_size;
				else
					_x += step_size;
			}
		}
		
		
	}




	CRect * RedGoblin::GetRect()
	{
		return &EnemyRect;
	}

	void RedGoblin::attack()
	{
		/*if (intersect(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2()) && attack_cool_down <= 0 && !isAttacking) {
			CAudio::Instance()->Play(AUDIO_HITTING);
			isAttacking = true;
			hero_on_map->offsetHp(attack_damage);
		}
		normalAttackR.OnMove();
		if (!isAttacking) {
			normalAttackR.Reset();
		}*/
	}

	void RedGoblin::attackShow(Maps * m)
	{
		if (isAttacking) {
			normalAttackR.SetTopLeft(m->screenX(_x), m->screenY(_y));
			normalAttackR.OnShow();
			if (normalAttackR.IsFinalBitmap()) {
				isAttacking = false;
				attack_cool_down = 90; //每次攻擊間隔3秒
			}
		}
	}

	void RedGoblin::arrowAttack()
	{
		if (!isAttacking && arrowAttackCD == 0)
		{
			/*attackIsFlying = true;
			arr.setArrowXY(_x, _y);*/
			if (_y == hero_on_map->GetY1() && hero_on_map->GetX1() <= _x)
			{
				arrorClock = 60;
				arr.setAttackIsFlying(true);
				arr.setDirection(0);
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (_y == hero_on_map->GetY1() && hero_on_map->GetX1() > _x)
			{
				arrorClock = 60;
				arr.setAttackIsFlying(true);
				arr.setDirection(1);
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (_x == hero_on_map->GetX1() && hero_on_map->GetY1() <= _y )
			{
				arrorClock = 60;
				arr.setAttackIsFlying(true);
				arr.setDirection(2);
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (_x == hero_on_map->GetX1() && hero_on_map->GetY1() > _y )
			{
				arrorClock = 60;
				arr.setAttackIsFlying(true);
				arr.setDirection(3);
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			
		}
	}

	void RedGoblin::arrowAttackMove(Maps * m)
	{
		if (isAttacking) {
			if (hero_on_map->intercect(arr.getX1(), arr.getX2(), arr.getY1(), arr.getY2())) {
				hero_on_map->offsetHp(attack_damage);
			}
		}
		/*if (arrowAttackCD == 0)
		{
			if (hero_on_map->intercect(arr.getX1(), arr.getX2(), arr.getY1(), arr.getY2())) {
				hero_on_map->offsetHp(attack_damage);
			}
		}*/
		if (isAttacking && arrorClock != 0) {
			arrorClock--;
			if (arrorClock == 0) {
				isAttacking = false;
			}
		}
		
		
	}

	void RedGoblin::arrowAttackShow(Maps * m)
	{
		arr.OnShow(m);
	}

}
