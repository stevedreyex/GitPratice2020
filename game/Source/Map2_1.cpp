#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include "Map2_1.h"
#include <vector>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Map2_1::Map2_1():Maps(-200, -200) {
		all_enemy_clear = 0;
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 15; j++) {
				if (i > 1 && i < 16 && j > 2 && j < 13) {
					map[i][j] = 0;
				}
				else {
					map[i][j] = 1;
				}
			}
		}
		map[8][9] = map[9][9] = 1;
		map[2][3] = map[2][4] = map[3][3] =  map[2][12] = map[15][12] = map[14][3] =  map[15][3] = map[15][4] = 1;
		map[8][2] = map[9][2] = 3;
	}

	Map2_1::~Map2_1()
	{

	}

	void Map2_1::Initialize()
	{
		setXY(-200, -200);
	}

	void Map2_1::setPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = n;
	}

	void Map2_1::setClear(bool b)
	{
		all_enemy_clear = b;
	}

	bool Map2_1::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] != 1) {
			return true;
		}
		return false;
	}

	bool Map2_1::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) {
			return true;
		}
		return false;
	}

	void Map2_1::OnMove() {

	}

	void Map2_1::LoadBitmap() {
		firstmap.LoadBitmap(IDB_MAP2_1);
		char *filename1_1[4] = { ".\\bitmaps\\gate1.bmp",".\\bitmaps\\gate2.bmp",".\\bitmaps\\gate3.bmp",".\\bitmaps\\gate4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			gate.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		gate.SetDelayCount(3);
	}

	void Map2_1::OnShow() {
		firstmap.SetTopLeft(getSX(), getSY());
		firstmap.ShowBitmap();
		if (all_enemy_clear == 1)
		{
			gate.SetTopLeft(getSX()+512, getSY() + 64);
			gate.OnMove();
			gate.OnShow();
		}
	}

	void Map2_1::getHeroX(int x)
	{
		hx = x;
	}

	void Map2_1::getHeroY(int y)
	{
		hy = y;
	}

	int Map2_1::screenX(int x)
	{
		return x + getSX();
	}

	int Map2_1::screenY(int y)
	{
		return y + getSY();
	}

}