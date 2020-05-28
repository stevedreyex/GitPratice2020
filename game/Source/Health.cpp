#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"
#include "Health.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	
	Health::Health()
	{
	}

	void Health::load()
	{
		health_pic.LoadBitmap(IDB_ITEMHEALTH, RGB(0, 0, 0));
	}

	void Health::OnMove(Maps *m, Hero *h)
	{
		if (isExist() && intercect(h) && (getRandomNum() % 100) < 40) {
			h->addHp(50);
			setExist(false);
		}
	}

	void Health::OnShow(Maps *m)
	{
		if (isExist() && (getRandomNum() % 100) < 40) {
			health_pic.SetTopLeft(m->screenX(getX()), m->screenY(getY()));
			health_pic.ShowBitmap();
		}
		
	}

	void Health::effect(Hero *h)
	{
	}



	/*bool Health::intercect(Hero * h)
	{
		if(isExist()) {
			if (h->GetX2() >= _x + 10 && h->GetX1() <= _x + 20 && h->GetY2() >= _y + 10 && h->GetY1() <= _y + 20) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
*/

}
