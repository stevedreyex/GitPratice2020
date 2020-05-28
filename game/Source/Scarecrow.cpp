#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"
#include "Scarecrow.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Enemy: Ball class
	/////////////////////////////////////////////////////////////////////////////

	//若在Character和Enemy中都有一個hp，選擇直接用Character中的那個

	Scarecrow::Scarecrow()
	{
		_x = 384;
		_y = 384;
		hp = 1200;
		attack_damage = 0;
	}

	Scarecrow::Scarecrow(int x, int y, Hero *h) : Enemy(x, y, 1200, "scarecrow", h, PLANT)
	{
		attack_damage = 50;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(PLANT));
	}

	Scarecrow::~Scarecrow()
	{
	}

	void Scarecrow::LoadBitmap()
	{
		enemy.LoadBitmap(IDB_SCARECROW, RGB(0, 0, 0));
		////道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->load();
		}
		blood_bar.loadBloodBar();
		EnemyRect = enemy.ReturnCRect();
		/////攻擊的動畫
		char *filename[12] = { ".\\bitmaps\\Scarecrow_attack1.bmp",".\\bitmaps\\Scarecrow_attack2.bmp",".\\bitmaps\\Scarecrow_attack3.bmp",".\\bitmaps\\Scarecrow_attack4.bmp", ".\\bitmaps\\Scarecrow_attack5.bmp", ".\\bitmaps\\Scarecrow_attack6.bmp", ".\\bitmaps\\Scarecrow_attack7.bmp", ".\\bitmaps\\Scarecrow_attack8.bmp", ".\\bitmaps\\Scarecrow_attack9.bmp", ".\\bitmaps\\Scarecrow_attack10.bmp", ".\\bitmaps\\Scarecrow_attack11.bmp", ".\\bitmaps\\Scarecrow_attack12.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			normalAttackR.AddBitmap(filename[i], RGB(0, 0, 0));
		normalAttackR.SetDelayCount(1);
	}

	void Scarecrow::OnMove(Maps * m) {
		if (isAlive()) {
			const int STEP_SIZE = 4;
			attack();
			attack_cool_down -= 1;
		}
		if (!isAlive()) {
			itemsOnMove(m);
		}
		
	}

	void Scarecrow::OnShow(Maps *m)
	{
		if (isAlive()) {
			if (isAttacking) {
				attackShow(m);
			}
			else {
				enemy.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
				//enemy.SetTopLeft(x, y);
				enemy.ShowBitmap();
				blood_bar.setXY(GetX1(), GetY1() + 50);
				blood_bar.showBloodBar(m, hp);
			}
		}
		if (!isAlive()) {
			itemsOnShow(m);
		}

	}

	int Scarecrow::GetX1()
	{
		return _x;
	}

	int Scarecrow::GetY1()
	{
		return _y;
	}

	int Scarecrow::GetX2()
	{
		return _x + enemy.Width();
	}

	int Scarecrow::GetY2()
	{
		return _y + enemy.Height();
	}

	void Scarecrow::Initialize() {
		hp = 1200;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = false;
		blood_bar.setFullHP(hp);
		////道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->Initialize();
		}
	}

	bool Scarecrow::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，稻草人的Bitmap本身比稻草人的身體大太多。
		if (isAlive()) {
			if (x2 >= _x + 20 && x1 <= _x + enemy.Width() - 20 && y2 >= _y + 60 && y1 <= _y + enemy.Height() - 15) {
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
	void Scarecrow::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void Scarecrow::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void Scarecrow::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void Scarecrow::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void Scarecrow::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}



	CRect * Scarecrow::GetRect()
	{
		return &EnemyRect;
	}

	void Scarecrow::attack()
	{
		if (intersect(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2()) && attack_cool_down <= 0 && !isAttacking) {
			isAttacking = true;
			CAudio::Instance()->Play(Audio_KNIFE);
			hero_on_map->offsetHp(attack_damage);
		}
		normalAttackR.OnMove();
		if (!isAttacking) {
			normalAttackR.Reset();
		}
	}

	void Scarecrow::attackShow(Maps * m)
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

}
