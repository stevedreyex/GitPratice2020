#ifndef __RANDOMATTRIBUTE_H
#define __RANDOMATTRIBUTE_H


#include "Maps.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class RandomAttribute: public Item
	{
	public:
		RandomAttribute();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);
		bool intercect(Hero *h) ;
		
	private:
		int _x, _y;
		int rand_num;
		CMovingBitmap random_attribute_pic;
	};
}

#endif // !Health_H