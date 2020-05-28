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
#include "Box.h"
#include "Util.h"
#include "Item.h"
#include "Clock.h"
#include "Potion.h"
#include "RandomAttribute.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Enemy: Ball class
	/////////////////////////////////////////////////////////////////////////////

	//若在Character和Enemy中都有一個hp，選擇直接用Character中的那個

	Box::Box()
	{
		_x = 384;
		_y = 384;
		hp = 2;
		attack_damage = 0;
	}

	Box::Box(int x, int y, Hero *h) : Enemy(x, y, 1200, "Box", h, NO)
	{
		attack_damage = 0;
		attack_cool_down = 0;
		items.push_back(new Potion());
		items.push_back(new Clock());
		items.push_back(new RandomAttribute());
		
	}

	Box::~Box()
	{
	}

	void Box::LoadBitmap()
	{
		box.LoadBitmap(IDB_BOX, RGB(0, 0, 0));
		damaged_box.LoadBitmap(IDB_BOXDAMAGED, RGB(0, 0, 0));
		////道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->load();
		}
		blood_bar.loadBloodBar();
		EnemyRect = box.ReturnCRect();

	}

	void Box::OnMove(Maps * m) {
		if (isAlive()) {
			m->setPos(_x + 20, _y + 20, 1);
		}
		if (!isAlive()) {
			m->setPos(_x + 20, _y + 20, 0);
			itemsOnMove(m);
		}
		
	}

	void Box::OnShow(Maps *m)
	{
		if (isAlive()) {
			if (hp > 10) {
				box.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
				box.ShowBitmap();
			}
			if (hp <= 10) {
				damaged_box.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
				damaged_box.ShowBitmap();
			}
		}
		if (!isAlive()) {
			itemsOnShow(m);
		}

	}

	int Box::GetX1()
	{
		return _x;
	}

	int Box::GetY1()
	{
		return _y;
	}

	int Box::GetX2()
	{
		return _x + box.Width();
	}

	int Box::GetY2()
	{
		return _y + box.Height();
	}

	void Box::Initialize() {
		hp = 20;
		rand_num = rand();
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = false;
		blood_bar.setFullHP(hp);
		////道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->Initialize();
			items.at(i)->setNumOfBox(rand_num);
		}
	}

	bool Box::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，稻草人的Bitmap本身比稻草人的身體大太多。
		if (isAlive()) {
			if (x2 >= _x + 20 && x1 <= _x + box.Width() - 20 && y2 >= _y && y1 <= _y + box.Height() - 15) {
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
	void Box::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void Box::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void Box::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void Box::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void Box::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}



	CRect * Box::GetRect()
	{
		return &EnemyRect;
	}

	void Box::attack()
	{
		
	}

	void Box::attackShow(Maps * m)
	{
		
	}

}
