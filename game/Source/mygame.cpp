/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <algorithm>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Character.h"
#include "BlueSlime.h"
#include "GreenSlime.h"
#include "RedSlime.h"
#include "RedGoblin.h"
#include "Util.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);	// 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		goto_status = 0;
		logo.LoadBitmap(IDB_STARTBACKGROUND);
		start_1.LoadBitmap(IDB_START1, RGB(0, 0, 0));
		start_2.LoadBitmap(IDB_START2, RGB(0, 0, 0));
		story_1.LoadBitmap(IDB_STORY1, RGB(0, 0, 0));
		story_2.LoadBitmap(IDB_STORY2, RGB(0, 0, 0)
		);
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_UP)
			goto_status = 0;
		if (nChar == KEY_DOWN)
			goto_status = 1;
		if (nChar == KEY_SPACE)
			if (goto_status == 0)
				GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{
		//
		// 貼上logo
		//
		//logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
		logo.SetTopLeft(0, 0);
		logo.ShowBitmap();
		if (goto_status == 0)
		{
			start_1.SetTopLeft(192, 256);
			start_1.ShowBitmap();
			story_2.SetTopLeft(256, 320);
			story_2.ShowBitmap();
		}
		if (goto_status == 1)
		{
			start_2.SetTopLeft(192, 256);
			start_2.ShowBitmap();
			story_1.SetTopLeft(256, 320);
			story_1.ShowBitmap();
		}
			
		
		//
		// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		/*pDC->TextOut(195, 180, "中文名:乞丐大劍");
		pDC->TextOut(155, 220, "This game is namely a crap.");*/
		//pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		//if (ENABLE_GAME_PAUSE)
		//	pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		//pDC->TextOut(170, 260, "Press Space to continue.");
		//pDC->TextOut(60, 420, "107820005 廖子濬 107820012 鍾思賢");
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 最終進度為100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g), NUMBALLS(28)
	{
		current_stage = STAGE_1_1;
		enemys1_1.push_back(new Scarecrow(400, 450, &player1));
		/*enemys1_1.push_back(new RedGoblin(300, 450, &player1));
		enemys1_1.push_back(new RedGoblin(300, 550, &player1));*/
		enemys1_1.push_back(new Box(256, 384, &player1));
		//enemys1_1.push_back(new ABoss(256, 384, &player1));
		enemys1_2.push_back(new RedGoblin(300, 450, &player1));
		enemys1_2.push_back(new RedGoblin(300, 550, &player1));
		for (int i = 0; i < 3; i++) {
			enemys1_2.push_back(new Box((64 * 3*i)+128, 448, &player1));
		}
		for (int i = 0; i < 2; i++) {
			enemys1_2.push_back(new RedSlime((64 * 3*i)+400, 448, &player1));
		}
		for (int i = 0; i < 2; i++) {
			enemys1_2.push_back(new GreenSlime((64 * 3 * i) + 300, 400, &player1));
		}
		for (int i = 0; i < 2; i++) {
			enemys1_2.push_back(new BlueSlime((64 * 3 * i) + 200, 496, &player1));
		}
		for (int i = 0; i < 5; i++) {
			enemys1_6.push_back(new GreenSlime(200, (300 + 64*i), &player1));
			enemys1_6.push_back(new RedSlime(900, (300 + 64 * i), &player1));
			enemys1_6.push_back(new BlueSlime( (200 + 64*i), 900, &player1));
			enemys1_6.push_back(new Scarecrow(500, (200 + 64*i), &player1));
		}
		enemys1_6.push_back(new ABoss(800, 300, &player1));
		enemys2_1.push_back(new RedSlime(600, 600, &player1));
		enemys2_2.push_back(new GreenSlime(500, 500, &player1));
		enemys2_3.push_back(new GreenSlime(500, 500, &player1));
		enemys2_4.push_back(new BlueSlime(500, 500, &player1));
	}

	CGameStateRun::~CGameStateRun()
	{
		for (vector<Enemy*>::iterator it_i = enemys1_1.begin(); it_i != enemys1_1.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys1_2.begin(); it_i != enemys1_2.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys1_6.begin(); it_i != enemys1_6.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys2_1.begin(); it_i != enemys2_1.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys2_2.begin(); it_i != enemys2_2.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys2_3.begin(); it_i != enemys2_3.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys2_4.begin(); it_i != enemys2_4.end(); ++it_i) {
			delete *it_i;
		}
	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int BACKGROUND_X = 60;
		const int ANIMATION_SPEED = 15;
		CAudio::Instance()->Play(AUDIO_GOLDENWIND, true);			// 撥放 MIDI
		
		player1.Initialize();
		//第一關怪物
		for (unsigned i = 0; i < enemys1_1.size(); i++) {
			enemys1_1[i]->Initialize();
		}
		//第二關怪物
		for (unsigned i = 0; i < enemys1_2.size(); i++) {
			enemys1_2[i]->Initialize();
		}
		//第六關怪物
		for (unsigned i = 0; i < enemys1_6.size(); i++) {
			enemys1_6[i]->Initialize();
		}
		//2_1怪物
		for (unsigned i = 0; i < enemys2_1.size(); i++) {
			enemys2_1[i]->Initialize();
		}
		//2_2怪物
		for (unsigned i = 0; i < enemys2_2.size(); i++) {
			enemys2_2[i]->Initialize();
		}
		//2_3怪物
		for (unsigned i = 0; i < enemys2_3.size(); i++) {
			enemys2_3[i]->Initialize();
		}
		//2_4怪物
		for (unsigned i = 0; i < enemys2_4.size(); i++) {
			enemys2_4[i]->Initialize();
		}
		current_stage = STAGE_1_1;
		map_stg1_1.Initialize();
		map_stg1_6.Initialize();
		map_stg1_2.Initialize();
		map_stg2_1.Initialize();
		map_stg2_3.Initialize();
		map_stg2_4.Initialize();
		player_status.Initialize(&player1);
	}

	void CGameStateRun::stage_process_move(Maps & stage_map, Hero & player, vector<Enemy*> & enemy_array, STAGE next_stage)
	{
		player.OnMove(&stage_map, &enemy_array);
		for (unsigned i = 0; i < enemy_array.size(); i++) {
			enemy_array[i]->OnMove(&stage_map);
		}
		sort(enemy_array.begin(), enemy_array.end(), [](Enemy *a, Enemy *b) {return a->GetY2() < b->GetY2(); });
		int next_x, next_y = 0;
		switch (next_stage)
		{
		case STAGE_1_2: next_x = 480; next_y = 480;
			break;
		case STAGE_1_6: next_x = 780; next_y = 1470;
			break;
		case STAGE_2_1: next_x = 480; next_y = 480;
			break;
		case STAGE_2_2: next_x = 480; next_y = 480;
			break;
		case STAGE_2_3: next_x = 480; next_y = 480;
			break;
		case STAGE_2_4: next_x = 480; next_y = 480;
			break;
		}
		stage_map.setClear(allEnemyDie(enemy_array));
		if (allEnemyDie(enemy_array) && player.isInFinishArea(&stage_map))
		{
			if (next_stage == STAGE_1_6) {
				CAudio::Instance()->Stop(AUDIO_GOLDENWIND);			// 撥放 MIDI
				CAudio::Instance()->Play(AUDIO_AWAKEN, true);			// 撥放 MIDI
			}
			else {
				CAudio::Instance()->Play(AUDIO_GOLDENWIND);			// 撥放 MIDI
				CAudio::Instance()->Stop(AUDIO_AWAKEN);			// 撥放 MIDI
			}
				current_stage = next_stage;
				player.SetXY(next_x, next_y);
		}
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		switch (current_stage) {
			case STAGE_1_1:
				stage_process_move(map_stg1_1, player1, enemys1_1, STAGE_1_2);
				break;
			case STAGE_1_2:
				stage_process_move(map_stg1_2, player1, enemys1_2, STAGE_1_6);
				break;
			case STAGE_1_6:
				stage_process_move(map_stg1_6, player1, enemys1_6, STAGE_2_1);
				break;
			case STAGE_2_1:
				stage_process_move(map_stg2_1, player1, enemys2_1, STAGE_2_2);
				break;
			case STAGE_2_2:
				stage_process_move(map_stg2_2, player1, enemys2_2, STAGE_2_3);
				break;
			case STAGE_2_3:
				stage_process_move(map_stg2_3, player1, enemys2_3, STAGE_2_4);
				break;
			case STAGE_2_4:
				stage_process_move(map_stg2_4, player1, enemys2_4, STAGE_2_4);
				break;
		}


		if (!player1.isAlive()) {
			GotoGameState(GAME_STATE_OVER);
		}
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// 移動背景圖的座標
		//
		if (background.Top() > SIZE_Y)
			background.SetTopLeft(60, -background.Height());
		background.SetTopLeft(background.Left(), background.Top() + 1);
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		player1.LoadBitmap();
		player_status.loadPlauerStatus();
		//第一關怪物
		for (unsigned i = 0; i < enemys1_1.size(); i++) {
			enemys1_1[i]->LoadBitmap();
		}

		//第二關怪物
		for (unsigned i = 0; i < enemys1_2.size(); i++) {
			enemys1_2[i]->LoadBitmap();
		}
		//第六關怪物
		for (unsigned i = 0; i < enemys1_6.size(); i++) {
			enemys1_6[i]->LoadBitmap();
		}
		//2_1怪物
		for (unsigned i = 0; i < enemys2_1.size(); i++) {
			enemys2_1[i]->LoadBitmap();
		}
		//2_2怪物
		for (unsigned i = 0; i < enemys2_2.size(); i++) {
			enemys2_2[i]->LoadBitmap();
		}
		//2_3怪物
		for (unsigned i = 0; i < enemys2_3.size(); i++) {
			enemys2_3[i]->LoadBitmap();
		}
		//2_4怪物
		for (unsigned i = 0; i < enemys2_4.size(); i++) {
			enemys2_4[i]->LoadBitmap();
		}

		map_stg1_1.LoadBitmap();
		map_stg1_2.LoadBitmap();
		background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
		map_stg1_6.LoadBitmap();
		map_stg2_1.LoadBitmap();
		map_stg2_2.LoadBitmap();
		map_stg2_3.LoadBitmap();
		map_stg2_4.LoadBitmap();
		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
		corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		corner.ShowBitmap(background);							// 將corner貼到background
		hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_GOLDENWIND, "sounds\\goldenwind.mp3");	// 載入編號2的聲音ntut.mid
		CAudio::Instance()->Load(AUDIO_SWORD, "sounds\\swing2.mp3");
		CAudio::Instance()->Load(AUDIO_FIRE, "sounds\\fireball.mp3");
		CAudio::Instance()->Load(AUDIO_SKILLE, "sounds\\swing4.mp3");
		CAudio::Instance()->Load(Audio_KNIFE,  "sounds\\knife2.mp3");
		CAudio::Instance()->Load(AUDIO_ICE, "sounds\\iceball.mp3");
		CAudio::Instance()->Load(AUDIO_HITTING, "sounds\\hitting4.mp3");
		CAudio::Instance()->Load(AUDIO_GRASSBALL, "sounds\\grassball.mp3");
		CAudio::Instance()->Load(AUDIO_BEGGER, "sounds\\begger.mp3");
		CAudio::Instance()->Load(AUDIO_AWAKEN, "sounds\\awaken.mp3");
		CAudio::Instance()->Load(AUDIO_DAMAGE1, "sounds\\damage1.mp3");
		CAudio::Instance()->Load(AUDIO_ABOSS_WALK, "sounds\\footsteps_of_a_giant.mp3");
		CAudio::Instance()->Load(AUDIO_ABOSS_PREPARE, "sounds\\ABoss_prepare.mp3");
		CAudio::Instance()->Load(AUDIO_GOODFLASH, "sounds\\goodflash.mp3");
		CAudio::Instance()->Load(AUDIO_BADFLASH, "sounds\\badflash.mp3");

		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		int n = rand() % 3;
		switch (nChar)
		{
		case KEY_LEFT: player1.SetMovingLeft(true); break;
		case KEY_RIGHT: player1.SetMovingRight(true); break;
		case KEY_UP: player1.SetMovingUp(true); break;
		case KEY_DOWN: player1.SetMovingDown(true); break;
		case NUM_0:
			
			if(n == 0)
				player1.SetElementAttribute(FIRE);
			if (n == 1)
				player1.SetElementAttribute(ICE);
			if (n == 2)
				player1.SetElementAttribute(PLANT);
			break;
		case NUM_1: player1.useItem(1); /*current_stage = STAGE_1_1;*/ break;
		case NUM_2: player1.useItem(2);/* current_stage = STAGE_1_2;*/ break;
		case NUM_3: player1.useItem(3); break;
		case NUM_4: player1.useItem(4); break;
		case NUM_5: player1.useItem(5); break;
		case NUM_6: player1.useItem(6); break;
		case NUM_9: 
			player1.addHp(50);
			player1.addAttack(5, FIRE);
			player1.addAttack(5, PLANT);
			player1.addAttack(5, ICE);
			break; 
		case KEY_A: player1.SetUsingA(true); break;
		case KEY_Q: player1.SetUsingQ(true); break;
		case KEY_W: player1.SetUsingW(true); break;
		case KEY_E: player1.SetUsingE(true); break;
		case KEY_R: player1.SetUsingR(true); break;
		default: return;
		}
		if(nRepCnt==CTRL)
			if (nChar == NUM_1) {
				current_stage = STAGE_1_1;
			}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		switch (nChar)
		{
		case KEY_LEFT: player1.SetMovingLeft(false); break;
		case KEY_RIGHT: player1.SetMovingRight(false); break;
		case KEY_UP: player1.SetMovingUp(false); break;
		case KEY_DOWN: player1.SetMovingDown(false); break;
		default: return;
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(true);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		//eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	bool CGameStateRun::allEnemyDie(vector<Enemy*> enemys)
	{
		for (unsigned i = 0; i < enemys.size(); i++) {
			if (enemys.at(i)->isAlive() && enemys.at(i)->GetName() != "Box") {
				return false;
			}
		}
		return true;
	}

	//void CGameStateRun::stage_process_show(Maps & stage_map, Hero & player, vector<Enemy*>& enemy_array, STAGE next_stage)
	//{
	//	switch (current_stage)
	//	{
	//	case STAGE_1_1: Maps current_map = first_stage_map;
	//	}
	//	stage_map.OnShow();
	//	int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
	//	for (unsigned i = 0; i < enemys1_1.size(); i++) {
	//		if (player1.GetY2() > enemys1_1[i]->GetY2()) {		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
	//			hero_position = i;
	//		}
	//	}
	//	if (hero_position == -1) {
	//		player1.OnShow(&first_stage_map);
	//	}
	//	for (unsigned i = 0; i < enemys1_1.size(); i++) {
	//		enemys1_1[i]->OnShow(&first_stage_map);
	//		if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
	//			player1.OnShow(&first_stage_map);
	//		}
	//	}
	//}

	void CGameStateRun::OnShow()
	{
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		corner.SetTopLeft(0, 0);
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		/////////////////////////////第一關

		/*switch (current_stage) {
		case STAGE_1_1:
			stage_process_show(first_stage_map, player1, enemys1_1, STAGE_1_2);
			break;
		case STAGE_1_2:
			stage_process_show(second_stage_map, player1, enemys1_2, STAGE_1_3);
			break;
		}*/

		if (current_stage == STAGE_1_1) {
			map_stg1_1.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys1_1.size(); i++) {
				if (player1.GetY2() > enemys1_1[i]->GetY2()) {		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) {
				player1.OnShow(&map_stg1_1);
			}
			for (unsigned i = 0; i < enemys1_1.size(); i++) {
				enemys1_1[i]->OnShow(&map_stg1_1);
				if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg1_1);
				}
			}
		}
		

		/////////////////////////////////////////////第二關

		if (current_stage == STAGE_1_2) {
			map_stg1_2.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys1_2.size(); i++) {
				if (player1.GetY2() > enemys1_2[i]->GetY2()) {		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) {
				player1.OnShow(&map_stg1_2);
			}
			for (unsigned i = 0; i < enemys1_2.size(); i++) {
				enemys1_2[i]->OnShow(&map_stg1_2);
				if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg1_2);
				}

			}
		}

		////////////////////////////////////////////第六關

		if (current_stage == STAGE_1_6) {
			map_stg1_6.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys1_6.size(); i++) {
				if (player1.GetY2() > enemys1_6[i]->GetY2()) {		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) {
				player1.OnShow(&map_stg1_6);
			}
			for (unsigned i = 0; i < enemys1_6.size(); i++) {
				enemys1_6[i]->OnShow(&map_stg1_6);
				if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg1_6);
				}

			}
		}

		/////////////////////////////// 2_1

		if (current_stage == STAGE_2_1) {
			map_stg2_1.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys2_1.size(); i++) {
				if (player1.GetY2() > enemys2_1[i]->GetY2()) {		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) {
				player1.OnShow(&map_stg2_1);
			}
			for (unsigned i = 0; i < enemys2_1.size(); i++) {
				enemys2_1[i]->OnShow(&map_stg2_1);
				if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg2_1);
				}

			}
		}

		//////////////////// 2_2

		if (current_stage == STAGE_2_2) {
			map_stg2_2.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys2_2.size(); i++) {
				if (player1.GetY2() > enemys2_2[i]->GetY2()) {		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) {
				player1.OnShow(&map_stg2_2);
			}
			for (unsigned i = 0; i < enemys2_2.size(); i++) {
				enemys2_2[i]->OnShow(&map_stg2_2);
				if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg2_2);
				}

			}
		}

		//////////////////////// 2_3

		if (current_stage == STAGE_2_3) {
			map_stg2_3.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys2_3.size(); i++) {
				if (player1.GetY2() > enemys2_3[i]->GetY2()) {		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) {
				player1.OnShow(&map_stg2_3);
			}
			for (unsigned i = 0; i < enemys2_3.size(); i++) {
				enemys2_3[i]->OnShow(&map_stg2_3);
				if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg2_3);
				}

			}
		}

		//////////////////// 2_4

		if (current_stage == STAGE_2_4) {
			map_stg2_4.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys2_4.size(); i++) {
				if (player1.GetY2() > enemys2_4[i]->GetY2()) {		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) {
				player1.OnShow(&map_stg2_4);
			}
			for (unsigned i = 0; i < enemys2_4.size(); i++) {
				enemys2_4[i]->OnShow(&map_stg2_4);
				if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg2_4);
				}

			}
		}

		player_status.showPlauerStatus();
		
	}

};


