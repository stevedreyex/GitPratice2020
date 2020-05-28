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
#include "ItemAttribute.h"
#include "Util.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	
	ItemAttribute::ItemAttribute(ELEMENT_ATTRIBUTE attribute)
	{
		_attribute = attribute;
	}

	void ItemAttribute::load()
	{
		fire_pic.LoadBitmap(IDB_ATTRIBUTEFIRE, RGB(0, 0, 0));
		ice_pic.LoadBitmap(IDB_ATTRIBUTEICE, RGB(0, 0, 0));
		plant_pic.LoadBitmap(IDB_ATTRIBUTEPLANT, RGB(0, 0, 0));
	}

	void ItemAttribute::OnMove(Maps *m, Hero *h)
	{
		_x = getX();
		_y = getY() + 30;
		if (isExist() && intercect(h)) {
			h->SetElementAttribute(_attribute);
			h->addAttack(1, _attribute);
			setExist(false);
		}
	}

	void ItemAttribute::OnShow(Maps *m)
	{
		if (isExist()) {
			if (_attribute == FIRE) {
				fire_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
				fire_pic.ShowBitmap();
			}
			if (_attribute == ICE) {
				ice_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
				ice_pic.ShowBitmap();
			}
			if (_attribute == PLANT) {
				plant_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
				plant_pic.ShowBitmap();
			}
		}
		
	}

	bool ItemAttribute::intercect(Hero * h)
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

	void ItemAttribute::effect(Hero *h)
	{
	}



}
