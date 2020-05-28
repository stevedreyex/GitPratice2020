#ifndef __MAPS_H__
#define __MAPS_H__
#include <vector>
//#include "Enemy.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Maps
	{
	public:
		Maps(int x, int y);
		virtual bool isEmpty(int x, int y) const = 0;
		virtual void addSX(int n);
		virtual void addSY(int n);
		virtual int screenX(int x) { return 0; };
		virtual int screenY(int y) { return 0; };
		virtual void getHeroX(int x) {};
		virtual void getHeroY(int y) {};
		virtual void setPos(int x, int y, int n) = 0;
		virtual void setClear(bool b) = 0;
		virtual bool inFinishArea(int x, int y) = 0;
		void setXY(int x, int y);
		int getSX();
		int getSY();
		//virtual bool bumpIntoEnemy(int x1, int x2, int y1, int y2) = 0;
		//virtual vector<Enemy> returnEnemys() = 0 ;

	private:
		int _sx, _sy;
		bool all_enemy_clear;
	};
}
#endif