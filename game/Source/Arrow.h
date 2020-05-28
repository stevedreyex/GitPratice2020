#ifndef ARROW_H
#define ARROW_H

#include "Maps.h"
#include "Character.h"
#include "BloodBar.h"
#include "Enemy.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供一個敵人													   //
	//		 																	//
	/////////////////////////////////////////////////////////////////////////////
	
	class Arrow{
	public:
		Arrow(int x, int y);
		Arrow();
		void loadBitmap();
		void OnMove(Maps *m);
		void OnShow(Maps *m);
		void setArrowXY(int x, int y);
		void setDirection(int direction);
		void setAttackIsFlying(bool b);
		int getX1();
		int getX2();
		int getY1();
		int getY2();
	private:
		CMovingBitmap arrowLeft;
		CMovingBitmap arrowRight;
		CMovingBitmap arrowUp;
		CMovingBitmap arrowDown;
		int _arrowX, _arrowY;
		int fly_direction;									//0=left, 1=right
		bool _attackIsFlying;
	};
}

#endif // !Scarecrow_H