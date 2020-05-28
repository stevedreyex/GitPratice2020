#ifndef __ITEM_H
#define __ITEM_H


#include "Maps.h"
#include "Hero.h"
#include "Character.h"

namespace game_framework {
	class Hero;
	class Item
	{
	public:
		Item();
		virtual void load() = 0;
		virtual void OnMove(Maps *m, Hero *h) = 0;
		virtual void OnShow(Maps *m) = 0;
		virtual void effect(Hero *h) = 0;
		void showOnStatusBar(int n);
		void Initialize();
		bool isExist();
		void setExist(bool b);
		void setNumOfBox(int n);
		void setXY(int x, int y);
		void setRandomNum(int n);
		int getX();
		int getY();
		int getRandomNum();
		int getNumOfBox();
		bool intercect(Hero *h);
		bool getIsUsed();
		void setIsUsed(bool b);
	
	private:
		int _x, _y;
		bool _isExist;
		int random_num;
		bool _isUsed;
		int num_of_box;
	
	protected:
		CMovingBitmap item_on_status_bar;
	};
}

#endif // !Item_H