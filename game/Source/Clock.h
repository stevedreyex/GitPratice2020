#ifndef __CLOCK_H
#define __CLOCK_H


#include "Maps.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Clock: public Item
	{
	public:
		Clock();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);
		bool intercect(Hero *h) ;
		
	private:
		int _x, _y;
		CMovingBitmap clock_pic;
	};
}

#endif // !Health_H