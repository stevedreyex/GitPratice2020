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

	Map1_6::Map1_6():Maps(-500, -1190) {
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				if (i > 2 && i < 22 && j >= 3 && j < 22) {
					map[i][j] = 0;
				}
				else {
					map[i][j] = 1;
				}
			}
		}
		map[9][10] = map[15][10] = map[9][16] = map[15][16] = 1;
		for (int i = 10; i <= 14; i++) {
			map[i][1] = 0;
			map[i][2] = 0;
			map[i][22] = 0;
			map[i][23] = 0;
		}
		map[9][22] = map[15][22] = map[9][2] = map[15][2] = 0;
		for (int i = 10; i <= 14; i++) {
			map[1][i] = 0;
			map[2][i] = 0;
			map[22][i] = 0;
			map[23][i] = 0;
		}
		map[2][9] = map[22][9] = map[2][15] = map[22][15] = 0;
		map[12][2] = map[11][2] = 3;
	}

	Map1_6::~Map1_6()
	{

	}

	void Map1_6::Initialize()
	{
		setXY(-500, -1190);
	}

	void Map1_6::setPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = n;
	}

	void Map1_6::setClear(bool b)
	{
		all_enemy_clear = b;
	}

	bool Map1_6::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] != 1) {
			return true;
		}
		return false;
	}

	bool Map1_6::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) {
			return true;
		}
		return false;
	}

	void Map1_6::OnMove() {

	}

	void Map1_6::LoadBitmap() {
		firstmap.LoadBitmap(IDB_MAP1_6);
	}

	void Map1_6::OnShow() {
		firstmap.SetTopLeft(getSX(), getSY());
		firstmap.ShowBitmap();
	}

	void Map1_6::getHeroX(int x)
	{
		hx = x;
	}

	void Map1_6::getHeroY(int y)
	{
		hy = y;
	}

	int Map1_6::screenX(int x)
	{
		return x + getSX();
	}

	int Map1_6::screenY(int y)
	{
		return y + getSY();
	}

}