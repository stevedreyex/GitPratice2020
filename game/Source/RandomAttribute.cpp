#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"
#include "Clock.h"
#include "RandomAttribute.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	
	RandomAttribute::RandomAttribute()
	{
	}

	void RandomAttribute::load()
	{
		random_attribute_pic.LoadBitmap(IDB_ITEMRANDOMATTRIBUTE);
		item_on_status_bar.LoadBitmapA(IDB_ITEMRANDOMATTRIBUTE);
	}

	void RandomAttribute::OnMove(Maps *m, Hero *h)
	{
		_x = getX();
		_y = getY();
		if (isExist() && intercect(h) && getNumOfBox() % 100 <= 30) {
			RandomAttribute * p = new RandomAttribute();
			p->load();
			h->addItem(p);
			setExist(false);
		}
	}

	void RandomAttribute::OnShow(Maps *m)
	{
		if (isExist() && getNumOfBox() % 100 <= 30) {
			random_attribute_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
			random_attribute_pic.ShowBitmap();
		}
		
	}

	void RandomAttribute::effect(Hero *h)
	{
		int n = rand() % 2;
		if (h->getCurrentAttribute() == FIRE) {
			if (n == 0) {
				h->SetElementAttribute(ICE);
			}
			else if (n == 1) {
				h->SetElementAttribute(PLANT);
			}
		}
		else if (h->getCurrentAttribute() == ICE) {
			if (n == 0) {
				h->SetElementAttribute(FIRE);
			}
			else if (n == 1) {
				h->SetElementAttribute(PLANT);
			}
		}
		else if (h->getCurrentAttribute() == PLANT) {
			if (n == 0) {
				h->SetElementAttribute(FIRE);
			}
			else if (n == 1) {
				h->SetElementAttribute(ICE);
			}
		}
		setIsUsed(false);
	}

	bool RandomAttribute::intercect(Hero * h)
	{
		if (isExist()) {
			if (h->GetX2() >= _x + 10 && h->GetX1() <= _x + 20 && h->GetY2() >= _y + 10 && h->GetY1() <= _y + 20) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}


}
