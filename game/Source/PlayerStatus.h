#ifndef __PLAYERSTATUS_H
#define __PLAYERSTATUS_H


#include "Maps.h"
#include "Character.h"
#include "Hero.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class PlauerStatus
	{
	public:
		PlauerStatus();
		void Initialize(Hero *h);
		void loadPlauerStatus();
		void showPlauerStatus();
		void setXY(int x, int y);
		void loadDigitsBitmap(CMovingBitmap a[]);
		void showQ();
		void showE();
		void showHP();
		void showAttackFire();
		void showAttackIce();
		void showAttackPlant();
		void showItemsOfPlayer();

	private:
		int _x, _y;
		CMovingBitmap status_bar;
		CMovingBitmap q_pic;

		CMovingBitmap skill_q_fire_pic;
		CMovingBitmap skill_q_ice_pic;
		CMovingBitmap skill_q_plant_pic;
		CMovingBitmap skill_e_pic;
		CMovingBitmap HP_first[10];
		CMovingBitmap HP_ten[10];
		CMovingBitmap HP_hundred[10];
		CMovingBitmap HP_thousand[10];

		CMovingBitmap Q_cooldown_first[10];
		CMovingBitmap Q_cooldown_ten[10];
		CMovingBitmap E_cooldown_first[10];
		CMovingBitmap E_cooldown_ten[10];

		CMovingBitmap attack_fire_first[10];
		CMovingBitmap attack_fire_ten[10];
		CMovingBitmap attack_fire_hundred[10];
		CMovingBitmap attack_fire_thousand[10];

		CMovingBitmap attack_ice_first[10];
		CMovingBitmap attack_ice_ten[10];
		CMovingBitmap attack_ice_hundred[10];
		CMovingBitmap attack_ice_thousand[10];

		CMovingBitmap attack_plant_first[10];
		CMovingBitmap attack_plant_ten[10];
		CMovingBitmap attack_plant_hundred[10];
		CMovingBitmap attack_plant_thousand[10];

		Hero *_h;
	};
}

#endif // !PlauerStatus_H