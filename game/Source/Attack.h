#ifndef __ATTACK_H

#define __ATTACK_H


#include "Maps.h"
#include "Character.h"
#include "Util.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Attack {
	public:
		Attack(int x, int y);
		Attack();
		void loadBitmap();
		void OnMove(Maps *m);
		void OnShow(Maps *m);
		void setAttribute(ELEMENT_ATTRIBUTE attribute);
		void setAttackName(ATTACK_NAME name);			//設定攻擊名稱
		void setXY(int x, int y);
		void setDirection(int direction);
		void setAttackIsFlying(bool b);
		void setStepSize(int x, int y);
		void resetAnimation(ATTACK_NAME atk);
		int getX1();
		int getX2();
		int getY1();
		int getY2();
	private:
		CMovingBitmap fire_attack;
		CAnimation flame_L1;
		CAnimation flame_L2;
		CAnimation flame_R1;
		CAnimation flame_R2;
		CAnimation ice_ball;
		CAnimation fire_ball;
		CAnimation grass_ball;
		CMovingBitmap fire_attack_boom;
		CMovingBitmap ice_attack;
		CMovingBitmap plant_attack;
		bool flame_status;
		int _x, _y;
		int step_size_x, step_size_y;
		int _direction;									//0=left, 1=right
		ELEMENT_ATTRIBUTE _attribute;
		ATTACK_NAME	_attack_name;						//攻擊的種類從這裡Call
		bool _attackIsFlying;
	};
}

#endif 