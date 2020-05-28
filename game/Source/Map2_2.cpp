#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include "Map2_2.h"
#include <vector>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Map2_2::Map2_2():Maps(-200, -200) {
		all_enemy_clear = 0;
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 16; j++) {
				if (i > 1 && i < 16 && j > 1 && j < 14) {
					map[i][j] = 0;
				}
				else {
					map[i][j] = 1;
				}
			}
		}
		map[2][2] = map[2][3] = map[3][2] =  map[2][13] = map[15][13] = map[14][2] =  map[15][2] = map[15][3] = 1;
		map[8][1] = map[9][1] = 3;
	}

	Map2_2::~Map2_2()
	{

	}

	void Map2_2::Initialize()
	{
		setXY(-200, -200);
	}

	void Map2_2::setPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = n;
	}

	void Map2_2::setClear(bool b)
	{
		all_enemy_clear = b;
	}

	bool Map2_2::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] != 1) {
			return true;
		}
		return false;
	}

	bool Map2_2::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) {
			return true;
		}
		return false;
	}

	void Map2_2::OnMove() {

	}

	void Map2_2::LoadBitmap() {
		firstmap.LoadBitmap(IDB_MAP2_2);
		char *filename1_1[4] = { ".\\bitmaps\\gate1.bmp",".\\bitmaps\\gate2.bmp",".\\bitmaps\\gate3.bmp",".\\bitmaps\\gate4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			gate.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		gate.SetDelayCount(3);
	}

	void Map2_2::OnShow() {
		firstmap.SetTopLeft(getSX(), getSY());
		firstmap.ShowBitmap();
		if (all_enemy_clear == 1)
		{
			gate.SetTopLeft(getSX()+512, getSY());
			gate.OnMove();
			gate.OnShow();
		}
	}

	void Map2_2::getHeroX(int x)
	{
		hx = x;
	}

	void Map2_2::getHeroY(int y)
	{
		hy = y;
	}

	int Map2_2::screenX(int x)
	{
		return x + getSX();
	}

	int Map2_2::screenY(int y)
	{
		return y + getSY();
	}

}