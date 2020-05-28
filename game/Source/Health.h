#ifndef __HEALTH_H
#define __HEALTH_H


#include "Maps.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Health: public Item
	{
	public:
		Health();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);
		//bool intercect(Hero *h) ;
		
	private:
		CMovingBitmap health_pic;

	};
}

#endif // !Health_H