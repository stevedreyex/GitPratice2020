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
	// �o��class�w�q�F���󪺦@�P����										   //
	/////////////////////////////////////////////////////////////////////////////
	class Objs
	{
	private:
		int Fx, Fy; //�y��
		int collisionCount;//�I�����ơA�]�p���ۨ���Enemy
		bool isMoving;//�b����(eg.Item���|����)
		bool isVisible;//�O�i����
		bool postToDead;//�w�g�ǳƭn������

		Direction dir;//�}�⪺��V
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