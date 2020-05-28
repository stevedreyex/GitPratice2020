#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "PlayerStatus.h"
#include "Util.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	PlauerStatus::PlauerStatus()
	{
		_x = 0;
		_y = 0;
	}

	void PlauerStatus::Initialize(Hero * h)
	{
		_h = h;
	}

	void PlauerStatus::loadPlauerStatus() {
		status_bar.LoadBitmap(IDB_STATUSBAR, RGB(255, 255, 255));
		skill_q_fire_pic.LoadBitmap(IDB_SKILLQFIREPIC);
		skill_q_ice_pic.LoadBitmap(IDB_SKILLQICEPIC);
		skill_q_plant_pic.LoadBitmap(IDB_SKILLQPLANTPIC);
		skill_e_pic.LoadBitmap(IDB_SKILLEPIC);
		loadDigitsBitmap(Q_cooldown_first);
		loadDigitsBitmap(Q_cooldown_ten);
		
		loadDigitsBitmap(E_cooldown_first);
		loadDigitsBitmap(E_cooldown_ten);
		
		loadDigitsBitmap(HP_first);
		loadDigitsBitmap(HP_ten);
		loadDigitsBitmap(HP_hundred);
		loadDigitsBitmap(HP_thousand);
		
		loadDigitsBitmap(attack_fire_first);
		loadDigitsBitmap(attack_fire_ten);
		loadDigitsBitmap(attack_fire_hundred);
		loadDigitsBitmap(attack_fire_thousand);

		loadDigitsBitmap(attack_ice_first);
		loadDigitsBitmap(attack_ice_ten);
		loadDigitsBitmap(attack_ice_hundred);
		loadDigitsBitmap(attack_ice_thousand);

		loadDigitsBitmap(attack_plant_first);
		loadDigitsBitmap(attack_plant_ten);
		loadDigitsBitmap(attack_plant_hundred);
		loadDigitsBitmap(attack_plant_thousand);
	}

	void PlauerStatus::showPlauerStatus() {
		status_bar.SetTopLeft(0, 0);
		status_bar.ShowBitmap();
		showQ();
		showE();
		showHP();
		showAttackFire();
		showAttackIce();
		showAttackPlant();
		showItemsOfPlayer();
	}

	void PlauerStatus::setXY(int x, int y) {
		_x = x;
		_y = y;
	}

	void PlauerStatus::loadDigitsBitmap(CMovingBitmap a[])
	{
		a[0].LoadBitmap(IDB_0 , RGB(0, 0, 0));
		a[1].LoadBitmap(IDB_1, RGB(0, 0, 0));
		a[2].LoadBitmap(IDB_2, RGB(0, 0, 0));
		a[3].LoadBitmap(IDB_3, RGB(0, 0, 0));
		a[4].LoadBitmap(IDB_4, RGB(0, 0, 0));
		a[5].LoadBitmap(IDB_5, RGB(0, 0, 0));
		a[6].LoadBitmap(IDB_6, RGB(0, 0, 0));
		a[7].LoadBitmap(IDB_7, RGB(0, 0, 0));
		a[8].LoadBitmap(IDB_8, RGB(0, 0, 0));
		a[9].LoadBitmap(IDB_9, RGB(0, 0, 0));
	}

	void PlauerStatus::showQ()
	{
		if (_h->getCurrentAttribute() == FIRE) {
			q_pic = skill_q_fire_pic;
		}
		if (_h->getCurrentAttribute() == PLANT) {
			q_pic = skill_q_plant_pic;
		}
		if (_h->getCurrentAttribute() == ICE) {
			q_pic = skill_q_ice_pic;
		}
		int q_cd = _h->GetQCoolDown()/30;
		if (_h->GetQCoolDown() == 0) {
			q_pic.SetTopLeft(20, 0);
			q_pic.ShowBitmap();
		}
		if (_h->GetQCoolDown() != 0) {
			int first = q_cd % 10;
			q_cd /= 10;
			int second = q_cd % 10;
			Q_cooldown_first[first].SetTopLeft(50, 20);
			Q_cooldown_first[first].ShowBitmap();
			Q_cooldown_ten[second].SetTopLeft(40, 20);
			Q_cooldown_ten[second].ShowBitmap();
		}

	}

	void PlauerStatus::showE()
	{
		int e_cd = _h->GetECoolDown()/30;
		if (_h->GetECoolDown() == 0) {
			skill_e_pic.SetTopLeft(160, 0);
			skill_e_pic.ShowBitmap();
		}
		if (_h->GetECoolDown() != 0) {
			int first = e_cd % 10;
			e_cd /= 10;
			int second = e_cd % 10;
			E_cooldown_first[first].SetTopLeft(200, 20);
			E_cooldown_first[first].ShowBitmap();
			E_cooldown_ten[second].SetTopLeft(190, 20);
			E_cooldown_ten[second].ShowBitmap();
		}
	}

	void PlauerStatus::showHP()
	{
		int hp = _h->getHP();
		if (hp != 0) {
			int first = hp % 10;
			hp /= 10;
			int second = hp % 10;
			hp /= 10;
			int third = hp % 10;
			hp /= 10;
			int forth = hp % 10;

			HP_first[first].SetTopLeft(500, 0);
			HP_first[first].ShowBitmap();
			HP_ten[second].SetTopLeft(490, 0);
			HP_ten[second].ShowBitmap();
			HP_hundred[third].SetTopLeft(480, 0);
			HP_hundred[third].ShowBitmap();
			HP_thousand[forth].SetTopLeft(470, 0);
			HP_thousand[forth].ShowBitmap();
		}
	}

	void PlauerStatus::showAttackFire()
	{
		int att_fire = _h->get_attack_fire();
		if (att_fire != 0) {
			int first = att_fire % 10;
			att_fire /= 10;
			int second = att_fire % 10;
			att_fire /= 10;
			int third = att_fire % 10;
			att_fire /= 10;
			int forth = att_fire % 10;

			attack_fire_first[first].SetTopLeft(500, 20);
			attack_fire_first[first].ShowBitmap();
			attack_fire_ten[second].SetTopLeft(490, 20);
			attack_fire_ten[second].ShowBitmap();
			attack_fire_hundred[third].SetTopLeft(480, 20);
			attack_fire_hundred[third].ShowBitmap();
			attack_fire_thousand[forth].SetTopLeft(470, 20);
			attack_fire_thousand[forth].ShowBitmap();
		}
	}

	void PlauerStatus::showAttackIce()
	{
		int att_ice = _h->get_attack_ice();
		if (att_ice != 0) {
			int first = att_ice % 10;
			att_ice /= 10;
			int second = att_ice % 10;
			att_ice /= 10;
			int third = att_ice % 10;
			att_ice /= 10;
			int forth = att_ice % 10;

			attack_ice_first[first].SetTopLeft(500, 40);
			attack_ice_first[first].ShowBitmap();
			attack_ice_ten[second].SetTopLeft(490, 40);
			attack_ice_ten[second].ShowBitmap();
			attack_ice_hundred[third].SetTopLeft(480, 40);
			attack_ice_hundred[third].ShowBitmap();
			attack_ice_thousand[forth].SetTopLeft(470, 40);
			attack_ice_thousand[forth].ShowBitmap();
		}
	}

	void PlauerStatus::showAttackPlant()
	{
		int att_plant = _h->get_attack_plant();
		if (att_plant != 0) {
			int first = att_plant % 10;
			att_plant /= 10;
			int second = att_plant % 10;
			att_plant /= 10;
			int third = att_plant % 10;
			att_plant /= 10;
			int forth = att_plant % 10;

			attack_plant_first[first].SetTopLeft(500, 60);
			attack_plant_first[first].ShowBitmap();
			attack_plant_ten[second].SetTopLeft(490, 60);
			attack_plant_ten[second].ShowBitmap();
			attack_plant_hundred[third].SetTopLeft(480, 60);
			attack_plant_hundred[third].ShowBitmap();
			attack_plant_thousand[forth].SetTopLeft(470, 60);
			attack_plant_thousand[forth].ShowBitmap();
		}
	}

	void PlauerStatus::showItemsOfPlayer()
	{
		for (int i = 0; i < 6; i++) {
			if (_h->getItemsOfPlayer()->at(i) != nullptr) {
				_h->getItemsOfPlayer()->at(i)->showOnStatusBar(i);
			}
		}
	}

	
}
