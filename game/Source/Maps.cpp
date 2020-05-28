#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include "Map1_6.h"
#include <vector>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	
	Maps::Maps(int x, int y)
	{
		_sx = x;
		_sy = y;
	}

	void Maps::addSX(int n)
	{
		_sx += n;
	}

	void Maps::addSY(int n)
	{
		_sy += n;
	}


	void Maps::setXY(int x, int y)
	{
		_sx = x;
		_sy = y;
	}

	int Maps::getSX()
	{
		return _sx;
	}

	int Maps::getSY()
	{
		return _sy;
	}

}