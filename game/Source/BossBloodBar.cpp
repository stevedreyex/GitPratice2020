#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "BossBloodBar.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	BossBloodBar::BossBloodBar()
	{
		_x = 0;
		_y = 0;
		full_hp = 0;
	}


	void BossBloodBar::setFullHP(int n) {
		full_hp = n;
	}

	void BossBloodBar::setXY(int x, int y) {
		_x = x;
		_y = y;
	}

	int BossBloodBar::getFullHP()
	{
		return (int)full_hp;
	}

	void BossBloodBar::loadBloodBar() {
		blood_bar[0].LoadBitmap(".\\bitmaps\\boss_blood_almost_die.bmp", RGB(0, 0, 0));
		blood_bar[1].LoadBitmap(".\\bitmaps\\boss_blood_almost_die.bmp", RGB(0, 0, 0));
		blood_bar[2].LoadBitmap(".\\bitmaps\\boss_blood14.bmp", RGB(0, 0, 0));
		blood_bar[3].LoadBitmap(".\\bitmaps\\boss_blood3over10.bmp", RGB(0, 0, 0));
		blood_bar[4].LoadBitmap(".\\bitmaps\\boss_blood4over10.bmp", RGB(0, 0, 0));
		blood_bar[5].LoadBitmap(".\\bitmaps\\boss_blood12.bmp", RGB(0, 0, 0));
		blood_bar[6].LoadBitmap(".\\bitmaps\\boss_blood6over10.bmp", RGB(0, 0, 0));
		blood_bar[7].LoadBitmap(".\\bitmaps\\boss_blood7over10.bmp", RGB(0, 0, 0));
		blood_bar[8].LoadBitmap(".\\bitmaps\\boss_blood34.bmp", RGB(0, 0, 0));
		blood_bar[9].LoadBitmap(".\\bitmaps\\boss_blood8over10.bmp", RGB(0, 0, 0));
		blood_bar[10].LoadBitmap(".\\bitmaps\\boss_blood_little_damaged.bmp", RGB(0, 0, 0));
		blood_bar[11].LoadBitmap(".\\bitmaps\\boss_blood_full.bmp", RGB(0, 0, 0));
	}

	void BossBloodBar::showBloodBar(Maps *m1, int hp) {
		if (hp > full_hp) {
			setFullHP(hp);
		}
		double proportion = hp / full_hp;
		if (proportion < 1.0 / 9) {
			blood_bar[0].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[0].ShowBitmap();
		}
		else if (proportion < 2.0 / 10) {
			blood_bar[1].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[1].ShowBitmap();
		}
		else if (proportion < 1.0 / 4) {
			blood_bar[2].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[2].ShowBitmap();
		}
		else if (proportion < 3.0/10)
		{
			blood_bar[3].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[3].ShowBitmap();
		}
		else if (proportion < 4.0/10) {
			blood_bar[4].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[4].ShowBitmap();
		}
		else if (proportion < 5.0 / 10) {
			blood_bar[5].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[5].ShowBitmap();
		}
		else if (proportion < 6.0 / 10) {
			blood_bar[6].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[6].ShowBitmap();
		}
		else if (proportion < 7.0 / 10) {
			blood_bar[7].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[7].ShowBitmap();
		}
		else if (proportion < 3.0 / 4) {
			blood_bar[8].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[8].ShowBitmap();
		}
		else if (proportion < 8.0 / 10) {
			blood_bar[9].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[9].ShowBitmap();
		}
		else if (proportion < 9.0 / 10) {
			blood_bar[10].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[10].ShowBitmap();
		}
		else {
			blood_bar[11].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[11].ShowBitmap();
		}
	}
}
