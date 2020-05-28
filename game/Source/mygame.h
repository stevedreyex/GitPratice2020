/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "ABoss.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Map1_6.h"
#include "Map1_2.h"
#include "Map2_1.h"
#include "Map2_2.h"
#include "Map2_3.h"
#include "Map2_4.h"
#include "Hero.h"
#include "Enemy.h"
#include "Util.h"
#include "Character.h"
#include "Scarecrow.h"
#include "GreenSlime.h"
#include "RedSlime.h"
#include "BlueSlime.h"
#include "Box.h"
#include "PlayerStatus.h"

namespace game_framework {

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
		bool goto_status;								// 0是上面的 game start, 1是下面的 story
		CMovingBitmap start_1;
		CMovingBitmap start_2;
		CMovingBitmap story_1;
		CMovingBitmap story_2;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void stage_process_move(Maps & stage_map, Hero & player, vector<Enemy*>& enemy_array, STAGE next_stage);
		void stage_process_show(Maps & stage_map, Hero & player, vector<Enemy*>& enemy_array, STAGE next_stage);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		bool allEnemyDie(vector<Enemy*> enemys);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const int		NUMBALLS;	// 球的總數
		PlauerStatus	player_status;
		Map1_1			map_stg1_1;
		Map1_2			map_stg1_2;
		Map1_6			map_stg1_6;
		Map2_1			map_stg2_1;
		Map2_2			map_stg2_2;
		Map2_3			map_stg2_3;
		Map2_4			map_stg2_4;
		Hero			player1;
		vector<Enemy*>  enemys1_1;
		vector<Enemy*>  enemys1_2;
		vector<Enemy*>  enemys1_6;
		vector<Enemy*>  enemys2_1;
		vector<Enemy*>  enemys2_2;
		vector<Enemy*>  enemys2_3;
		vector<Enemy*>  enemys2_4;
		STAGE			current_stage;
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明圖
		CMovingBitmap	corner;		// 角落圖
		CInteger		hits_left;	// 剩下的撞擊數
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}