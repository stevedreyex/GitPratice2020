#ifndef OBJS_H
#define OBJS_H

#include <atltypes.h>
#include "Util.h"
#include "gamelib.h"

namespace game_framework {
	enum Direction
	{dirUp, dirDown, dirLeft, dirRight};
	enum ObjsAttribute
	{
		noDirObject,
		noMapCollisionObj,
		noCharacterCollisionObj,
		noAttackCollisionObj,
		altAllignMapObj
	};
	typedef std::vector<Objs*> CharacterArray;
	/////////////////////////////////////////////////////////////////////////////
	// 這個class定義了物件的共同介面										   //
	/////////////////////////////////////////////////////////////////////////////
	class Objs
	{
	private:
		int Fx, Fy; //座標
		int collisionCount;//碰撞次數，設計給自走的Enemy
		bool isMoving;//在移動(eg.Item不會移動)
		bool isVisible;//是可見的
		bool postToDead;//已經準備要消失的

		Direction dir;//腳色的方向
		ObjsAttribute att;
		CMovingBitmap objectPic;
		CRect * objectSize;
	protected:
		virtual bool CheckCollision(int &x, int &y);
		virtual bool CheckCharacterCollision();
	public:
		virtual void OnMove();
		virtual void OnShow();
		
		void RandomDirection();
		void CenterBy();
		
	};
	

	
}

#endif // !OBJS_H