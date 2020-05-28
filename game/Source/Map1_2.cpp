#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Enemy.h"
#include "Map1_2.h"
#include <vector>

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Map1_2::Map1_2():Maps(-200, -200) {
		all_enemy_clear = 0;
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 13; j++) {
				if (i > 0 && i < 15 && j >= 2 && j <= 11) {
					map[i][j] = 0;
				}
				else {
					map[i][j] = 1;
				}
			}
		}
		map[7][1] = map[8][1] = 3;
		map[1][5] = map[2][4] = map[3][3] = map[12][3] = map[13][4] = map[14][5] = 1;
		map[1][2] = map[1][3] = map[2][2] = map[13][2] = map[14][2] = map[14][3] = 1;
		map[1][11] = map[1][10] = map[2][11] = map[14][10] = map[13][11] = map[14][11] = 1;
	}

	Map1_2::~Map1_2()
	{

	}

	void Map1_2::Initialize()
	{
		setXY(-200, -200);
	}

	void Map1_2::setPos(int x, int y, int n)
	{
		int gx = x / 64;
		int gy = y / 64;
		map[gx][gy] = n;
	}

	void Map1_2::setClear(bool b)
	{
		all_enemy_clear = b;
	}

	bool Map1_2::isEmpty(int x, int y) const
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] != 1) {
			return true;
		}
		return false;
	}

	bool Map1_2::inFinishArea(int x, int y)
	{
		int gx = x / 64;
		int gy = y / 64;
		if (map[gx][gy] == 3) {
			return true;
		}
		return false;
	}

	void Map1_2::OnMove() {

	}

	void Map1_2::LoadBitmap() {
		firstmap.LoadBitmap(IDB_MAP1_2);
		char *filename1_1[4] = { ".\\bitmaps\\gate1.bmp",".\\bitmaps\\gate2.bmp",".\\bitmaps\\gate3.bmp",".\\bitmaps\\gate4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			gate.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		gate.SetDelayCount(3);
	}

	void Map1_2::OnShow() {
		firstmap.SetTopLeft(getSX(), getSY());
		firstmap.ShowBitmap();
		if (all_enemy_clear == 1)
		{
			gate.SetTopLeft(getSX()+448, getSY());
			gate.OnMove();
			gate.OnShow();
		}
	}

	void Map1_2::getHeroX(int x)
	{
		hx = x;
	}

	void Map1_2::getHeroY(int y)
	{
		hy = y;
	}

	int Map1_2::screenX(int x)
	{
		return x + getSX();
	}

	int Map1_2::screenY(int y)
	{
		return y + getSY();
	}

}