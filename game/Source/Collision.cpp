#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Collision.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Collision: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	Collision::Collision()
	{
		Initialize();
	}

	int Collision::GetX1()
	{
		return x;
	}

	int Collision::GetY1()
	{
		return y;
	}

	int Collision::GetX2()
	{
		return x + animation.Width();
	}

	int Collision::GetY2()
	{
		return y + animation.Height();
	}

	void Collision::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 400;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Collision::LoadBitmap()
	{
		//animation.AddBitmap(IDB_ERASER1, RGB(255, 255, 255));
	}

	void Collision::OnMove()
	{
	}

	void Collision::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Collision::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Collision::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Collision::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Collision::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Collision::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}