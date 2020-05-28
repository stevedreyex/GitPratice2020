#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "BloodBar.h"
#include "Util.h"
#include "Attack.h"
#define HMS HERO_MOVE_SPEED


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Hero::Hero() : Character("Hero")
	{
		/*x = 480;
		y = 480;
		hp = 1200;
		attack = 20;
		skillTimes = 0;*/
		for (int i = 0; i < 6; i++) {
			items.push_back(nullptr);
		}
	}

	Hero::~Hero() {
		for (vector<Item*>::iterator it_i = items.begin(); it_i != items.end(); ++it_i) {
			delete *it_i;
			
		}
	}

	void Hero::LoadBitmap()
	{
		heroL.LoadBitmap(IDB_HERO_L, RGB(0, 0, 0));
		heroR.LoadBitmap(IDB_HERO_R, RGB(0, 0, 0));
		blood_bar.loadBloodBar();
		//被攻擊
		char *filename_attacked[4] = { ".\\bitmaps\\getting_attacked.bmp",".\\bitmaps\\getting_attacked2.bmp",".\\bitmaps\\getting_attacked.bmp",".\\bitmaps\\getting_attacked2.bmp"};
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			get_attacked.AddBitmap(filename_attacked[i], RGB(0, 0, 0));
		get_attacked.SetDelayCount(2);

		//向左走動畫
		char *filename1[6] = { ".\\bitmaps\\walkingL1.bmp",".\\bitmaps\\walkingL2.bmp",".\\bitmaps\\walkingL3.bmp",".\\bitmaps\\walkingL4.bmp", ".\\bitmaps\\walkingL3.bmp", ".\\bitmaps\\walkingL2.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			walkingLeft.AddBitmap(filename1[i], RGB(0, 0, 0));
		//向右走動畫
		char *filename2[6] = { ".\\bitmaps\\walkingR1.bmp",".\\bitmaps\\walkingR2.bmp",".\\bitmaps\\walkingR3.bmp",".\\bitmaps\\walkingR4.bmp", ".\\bitmaps\\walkingR3.bmp", ".\\bitmaps\\walkingR2.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			walkingRight.AddBitmap(filename2[i], RGB(0, 0, 0));
		RectHero = heroL.ReturnCRect();
		//E動畫
		char *filenameW[8] = { ".\\bitmaps\\Clock1.bmp",".\\bitmaps\\Clock2.bmp",".\\bitmaps\\Clock3.bmp",".\\bitmaps\\Clock4.bmp", ".\\bitmaps\\Clock5.bmp", ".\\bitmaps\\Clock6.bmp", ".\\bitmaps\\Clock7.bmp", ".\\bitmaps\\Clock8.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			skillE.AddBitmap(filenameW[i], RGB(0, 0, 0));
		skillE.SetDelayCount(2);
		//普功動畫(左)
		normalAttackL.AddBitmap(IDB_COUNTER1, RGB(0, 0, 0));
		normalAttackL.AddBitmap(IDB_COUNTER2, RGB(0, 0, 0));
		normalAttackL.AddBitmap(IDB_COUNTER3, RGB(0, 0, 0));
		normalAttackL.SetDelayCount(5);
		//普功動畫(右)
		normalAttackR.AddBitmap(IDB_CLOCK1, RGB(0, 0, 0));
		normalAttackR.AddBitmap(IDB_CLOCK2, RGB(0, 0, 0));
		normalAttackR.AddBitmap(IDB_CLOCK3, RGB(0, 0, 0));
		normalAttackR.SetDelayCount(5);
		//Q
		q_attack.loadBitmap();
	}

	void Hero::OnMove(Maps * m, vector<Enemy*> * enemys) {
		//TRACE("-------%d", slide_left);
		if (isMovingLeft && m->isEmpty(x - HMS, y) && m->isEmpty(x - HMS, GetY2()-10))
		{
			m->addSX(HMS);
			x -= HMS;
			slide_left = 30;
		}

		if (isMovingRight && m->isEmpty(GetX2() + HMS, y) && m->isEmpty(GetX2() + HMS, GetY2()-10))
		{
			m->addSX(-HMS);
			x += HMS;
			slide_right = 30;
		}
		if (isMovingUp && m->isEmpty(x+10, y - HMS) && m->isEmpty(GetX2()-10, y - HMS))
		{
			m->addSY(HMS);
			y -= HMS;
			slide_up = 30;
		}

		if (isMovingDown && m->isEmpty(x+10, GetY2() + HMS) && m->isEmpty(GetX2()-10, GetY2() + HMS))
		{
			m->addSY(-HMS);
			y += HMS;
			slide_down = 30;
		}
		if (gonnaBleeding(enemys, GetX1(), GetX2(), GetY1(), GetY2()))
		{
			//hp -= 10;
		}

		m->getHeroX(x);
		m->getHeroY(y);
		walkingLeft.OnMove();
		walkingRight.OnMove();
		skillEMove();
		skillWMove(m);
		skillQMove(m);
		normalAttackMove();
		get_attacked.OnMove();
		if (isSlide) {
			slide(m);
		}
	}

	void Hero::OnShow(Maps *m)
	{
		blood_bar.setXY(x - 10, y - 10);
		blood_bar.showBloodBar(m, hp);
		gettingAttackedShow();
		if (isUsingSkill()) { 
			normalAttackShow(m);
			skillEShow();
			skillQShow(m);
		}
		else {
			heroShow(m);
		}
		showHeroStatus();
	}

	int Hero::GetX1() {
		return x;
	}

	int Hero::GetY1() {
		return y;
	}

	int Hero::GetX2()
	{
		return x + heroR.Width();
	}

	int Hero::GetY2()
	{
		return y + heroR.Height();
	}

	int Hero::GetQCoolDown()
	{
		return skill_q_cool_down;
	}

	int Hero::GetECoolDown()
	{
		return skill_e_cool_down;
	}

	int Hero::getHP()
	{
		return hp;
	}

	int Hero::getFullHP()
	{
		return blood_bar.getFullHP();
	}

	int Hero::get_attack_fire()
	{
		return attack_fire;
	}

	int Hero::get_attack_ice()
	{
		return attack_ice;
	}

	int Hero::get_attack_plant()
	{
		return attack_plant;
	}

	ELEMENT_ATTRIBUTE Hero::getCurrentAttribute()
	{
		return _attribute;
	}

	vector<Item*>* Hero::getItemsOfPlayer()
	{
		return &items;
	}

	void Hero::Initialize() {
		x = 480;
		y = 480;
		hp = 1200;
		//attack_fire = SKILL_EVO_TVALUE; //借我測一下flame，晚點改回來。
		attack_fire = 20;
		attack_ice = 20;
		attack_plant = 20;
		skillTimes = 0;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttack = is_getting_attacked =false;
		isUsingA = isUsingQ = isUsingW = isUsingE = isUsingR = false;
		blood_bar.setFullHP(hp);
		walkingLeft.SetDelayCount(5);
		walkingRight.SetDelayCount(5);
		skill_e_cool_down = skill_q_cool_down = 0;
		slide_left = slide_right = slide_down = slide_up = 0;
		isSlide = true;
		_attribute = FIRE;
		for (int i = 0; i < 6; i++) {
			items.at(i) = nullptr;
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////
	
	void Hero::SetMovingDown(bool b) {
		isMovingDown = b;
		directionUD = 1;
	}

	void Hero::SetMovingUp(bool b) {
		isMovingUp = b;
		directionUD = 0;
	}

	void Hero::SetMovingLeft(bool b) {
		isMovingLeft = b;
		directionLR = 0;
	}

	void Hero::SetMovingRight(bool b) {
		isMovingRight = b;
		directionLR = 1;
	}

	void Hero::SetXY(int num_x, int num_y)
	{
		x = num_x;
		y = num_y;
	}
	
	/////////////////////////////////////////////////////////////////////////////
	
	void Hero::SetUsingA(bool b)
	{
		if (!isUsingSkill()) {
			if (b) {
				CAudio::Instance()->Play(AUDIO_SWORD);
			}

			isUsingA = b;
		}
	}
	
	void Hero::SetUsingQ(bool b)
	{
		if (!isUsingSkill() && skill_q_cool_down <= 0) {
			skill_q_cool_down = 60;
			if (b) {
				skillQ();
				//CAudio::Instance()->Play(AUDIO_FIRE);
			}
			isUsingQ = b;
		}
	}
	
	void Hero::SetUsingW(bool b)
	{
		if (!isUsingSkill() && skill_w_cool_down <= 0) {
			skill_w_cool_down = 180;
			isUsingW = b;
		}
	}
	
	void Hero::SetUsingE(bool b)
	{
		if (!isUsingSkill() && skill_e_cool_down <= 0) {
			skill_e_cool_down = 150;
			if (b) {
				CAudio::Instance()->Play(AUDIO_BEGGER);
				CAudio::Instance()->Play(AUDIO_SKILLE);
			}
			isUsingE = b;
		}
	}
	
	void Hero::SetUsingR(bool b)
	{
		if (!isUsingSkill()) {
			isUsingR = b;
		}
	}

	void Hero::SetElementAttribute(ELEMENT_ATTRIBUTE e)
	{
		_attribute = e;
	}

	void Hero::SetAllCoolDownToZero()
	{
		skill_q_cool_down = skill_e_cool_down = skill_w_cool_down = 0;
	}
	
	/////////////////////////////////////////////////////////////////////////////
	
	bool Hero::gonnaBleeding(vector<Enemy*> * enemys, int x1, int x2, int y1, int y2)
	{
		int attack = 0;
		if (_attribute == FIRE) {
			attack = -1*attack_fire;
		}
		if (_attribute == ICE) {
			attack = -1*attack_ice;
		}
		if (_attribute == PLANT) {
			attack = -1*attack_plant;
		}
		//attack = -10000;
		for (unsigned i = 0; i < enemys->size(); i++)
		{
			if (enemys->at(i)->intersect(x1, x2, y1, y2))
			{
				return true;
			}
			//普功
			if (enemys->at(i)->intersect(x1 - 30, x2 - 30, y1 + 10, y2) && directionLR == 0 && isUsingA)
			{
				enemys->at(i)->offsetHP(attack, _attribute);
			}
			if (enemys->at(i)->intersect(x1 + 30, x2 + 30, y1 + 10, y2) && directionLR == 1 && isUsingA)
			{
				enemys->at(i)->offsetHP(attack, _attribute);
			}
			//Q技能
			if (enemys->at(i)->intersect(q_attack.getX1(), q_attack.getX2(), q_attack.getY1(), q_attack.getY2()) && isUsingQ)
			{
				if (attack_fire >= SKILL_EVO_TVALUE && _attribute == FIRE)
					enemys->at(i)->offsetHP(attack*2, _attribute);
				enemys->at(i)->offsetHP(attack, _attribute);
			}
			//E技能
			if (enemys->at(i)->intersect(x1 - 30, x2 + 30, y1 - 30, y2 + 30) && isUsingE)
			{
				enemys->at(i)->offsetHP(attack, _attribute);
			}
		}
		return false;
	}

	void Hero::offsetHp(int n)
	{
		is_getting_attacked = true;
		hp -= n;
	}

	void Hero::addHp(int n)
	{
		hp += n;
	}

	void Hero::addAttack(int n, ELEMENT_ATTRIBUTE attribute)
	{
		if (attribute == FIRE) {
			attack_fire += n;
		}
		if (attribute == ICE) {
			attack_ice += n;
		}
		if (attribute == PLANT) {
			attack_plant += n;
		}
	}

	void Hero::addItem(Item * item)
	{
		int n = -1;
		for (int i = 5; i >= 0; i--) {
			if (items.at(i) == nullptr) {
				n = i;
			}
		}
		if (n != -1 && items.at(n) == nullptr) {
			items.at(n) = item;
		}
		else {
			delete item;
		}

	}

	void Hero::slide(Maps * m)
	{
		if (slide_right > 0) {
			slide_right--;
		}
		if (slide_left > 0) {
			slide_left--;
		}
		if (slide_up > 0) {
			slide_up--;
		}
		if (slide_down > 0) {
			slide_down--;
		}
		if (!isMovingLeft && m->isEmpty(x - HMS, y) && m->isEmpty(x - HMS, GetY2() - 10))
		{
			if (slide_left > 0) {
				m->addSX((int)(slide_left/5.0));
				x -= (int)(slide_left / 5.0);
				if (isMovingRight) {
					m->addSX(HMS);
					x -= HMS;
				}
			}
		}

		if (!isMovingRight && m->isEmpty(GetX2() + HMS, y) && m->isEmpty(GetX2() + HMS, GetY2() - 10))
		{
			if (slide_right > 0) {
				m->addSX(-(int)(slide_right / 5.0));
				x += (int)(slide_right / 5.0);
				if (isMovingLeft) {
					m->addSX(-HMS);
					x += HMS;
				}
			}
		}
		if (!isMovingUp && m->isEmpty(x + 10, y - HMS) && m->isEmpty(GetX2() - 10, y - HMS))
		{
			if (slide_up > 0) {
				m->addSY((int)(slide_up / 5.0));
				y -= (int)(slide_up / 5.0);
				if(isMovingDown){
					m->addSY(HMS);
					y -= HMS;
				}
			}

		}

		if (!isMovingDown && m->isEmpty(x + 10, GetY2() + HMS) && m->isEmpty(GetX2() - 10, GetY2() + HMS))
		{
			if (slide_down > 0) {
				m->addSY(-(int)(slide_down / 5.0));
				y += (int)(slide_down / 5.0);
				if (isMovingUp) {
					m->addSY(-HMS);
					y += HMS;
				}
			}

		}


	}

	/////////////////////////////////////////////////////////////////////////////

	bool Hero::isMoving()
	{
		if (isMovingDown || isMovingLeft || isMovingRight || isMovingUp) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Hero::isAlive()
	{
		if (hp > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Hero::isInFinishArea(Maps * m)
	{
		if (m->inFinishArea(x, y)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Hero::isUsingSkill()
	{
		if (isUsingA || isUsingQ || isUsingE ) {
			return true;
		}
		return false;
	}

	void Hero::heroShow(Maps *m)
	{
		if (directionLR == 0)
		{
			if (isMoving()) {
				walkingLeft.SetTopLeft(m->screenX(x), m->screenY(y));
				walkingLeft.OnShow();
			}
			else {
				heroL.SetTopLeft(m->screenX(x), m->screenY(y));
				heroL.ShowBitmap();
			}

		}
		else
		{
			if (isMoving()) {
				walkingRight.SetTopLeft(m->screenX(x), m->screenY(y));
				walkingRight.OnShow();
			}
			else {
				heroR.SetTopLeft(m->screenX(x), m->screenY(y));
				heroR.ShowBitmap();
			}

		}
	}

	bool Hero::intercect(int x1, int x2, int y1, int y2)
	{
		if (x2 >= x + 20 && x1 <= x + walkingRight.Width() && y2 >= y && y1 <= y + walkingRight.Height()) {
			return true;
		}
		else {
			return false;
		}
	}

	/////////////////////////////////////////////////////////////////////////////

	void Hero::normalAttackMove()
	{
		normalAttackL.OnMove();
		normalAttackR.OnMove();
		if (!isUsingA) {
			normalAttackL.Reset();			//沒有用技能的時候 要Reset CAnimation，下次才會從第一張圖跑
			normalAttackR.Reset();
		}
	}

	void Hero::normalAttackShow(Maps *m)
	{
		if (directionLR == 0 && isUsingA) {
			normalAttackL.SetTopLeft(m->screenX(x) - 20, m->screenY(y) - 10);
			normalAttackL.OnShow();
			if (normalAttackL.IsFinalBitmap()) {
				isUsingA = false;
			}
		}
		if (directionLR == 1 && isUsingA) {
			normalAttackR.SetTopLeft(m->screenX(x) - 20, m->screenY(y) - 10);
			normalAttackR.OnShow();
			if (normalAttackR.IsFinalBitmap()) {
				isUsingA = false;
			}
		}
	}

	void Hero::showHeroStatus()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str,"Cool Down: Q:%d E:%d   HP: %d", skill_q_cool_down / 30,skill_e_cool_down / 30, hp);
		pDC->TextOut(0, 0, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

	}

	void Hero::gettingAttackedShow()
	{
		if (is_getting_attacked) {
			get_attacked.SetTopLeft(0, 0);
			get_attacked.OnShow();
			if (get_attacked.IsFinalBitmap()) {
				is_getting_attacked = false;
			}
		}
		else {
			get_attacked.Reset();
		}
	}

	void Hero::skillQ()
	{
		if (!isUsingSkill()) {
			q_attack.setXY(x, y);
			if (_attribute == FIRE) {
				CAudio::Instance()->Play(AUDIO_FIRE);
			}
			if (_attribute == ICE) {
				CAudio::Instance()->Play(AUDIO_ICE);
			}
			if (_attribute == PLANT) {
				CAudio::Instance()->Play(AUDIO_GRASSBALL);
			}
			q_attack.setAttackIsFlying(true);
			if (directionLR == 0) {
				q_attack.setDirection(0);
				q_attack.setStepSize(-10, 0);
			}
			if (directionLR == 1) {
				q_attack.setDirection(1);
				q_attack.setStepSize(10, 0);
			}
		}

	}

	void Hero::skillQMove(Maps *m)
	{
		if (isUsingQ) {
			q_attack.OnMove(m);
			q_attack.setXY(x, y);
		}
		if (skill_q_cool_down > 0) {
			skill_q_cool_down -= 1;
		}
		if (_attribute == FIRE) {
			q_attack.setAttackName(FIRE_BALL);
			if (!isUsingQ)
			{
				q_attack.resetAnimation(FIRE_BALL);
			}
			if (attack_fire >= SKILL_EVO_TVALUE) {
				q_attack.setAttackName(FIRE_FLAME);
				if (!isUsingQ)
				{
					q_attack.resetAnimation(FIRE_FLAME);
				}
			}
		}
		if (_attribute == ICE) {
			q_attack.setAttackName(ICE_BALL);
			if (!isUsingQ)
			{
				q_attack.resetAnimation(ICE_BALL);
			}
		}
		if (_attribute == PLANT) {
			q_attack.setAttackName(GRASS_BALL);
			if (!isUsingQ)
			{
				q_attack.resetAnimation(GRASS_BALL);
			}
		}
	}

	void Hero::skillQShow(Maps * m)
	{
		if (isUsingQ) {
			heroShow(m);
			q_attack.OnShow(m);
			skillTimes += 1;							//+1代表跑了1/30秒
			if (skillTimes > 20) {						//預計讓他飛2/3秒
				isUsingQ = false;
				q_attack.setAttackIsFlying(false);
				skillTimes = 0;							//跑完整個技能把skillTime設回為0
			}
		}
	}

	void Hero::useItem(int n)
	{
		if (items.at(n - 1) != nullptr) {
			items.at(n - 1)->effect(this);
		}
		vector<Item*>::iterator it_i = items.begin();
		for (int i = 0; i < n - 1; i++) {
			++it_i;
		}
		delete *it_i;
		items.at(n - 1) = nullptr;
	}

	void Hero::skillW()
	{

	}

	void Hero::skillWMove(Maps *m)
	{
		if (skill_w_cool_down > 0) {
			skill_w_cool_down -= 1;
		}
		if (isUsingW)
		{
			if (isMovingLeft)
			{
				if (m->isEmpty(x - 15 * HMS, y) && m->isEmpty(x - 15 * HMS, GetY2() - 10) && m->isEmpty(x - 30 * HMS, y) && m->isEmpty(x - 30 * HMS, GetY2() - 10))
				{
					CAudio::Instance()->Play(AUDIO_GOODFLASH);
					m->addSX(32 * HMS);
					x -= 32 * HMS;
				}
				else
				{
					CAudio::Instance()->Play(AUDIO_BADFLASH);
				}
			}

			if (isMovingRight)
			{
				if (m->isEmpty(GetX2() + 15 * HMS, y) && m->isEmpty(GetX2() + 15 * HMS, GetY2() - 10) && m->isEmpty(GetX2() + 30 * HMS, y) && m->isEmpty(GetX2() + 30 * HMS, GetY2() - 10))
				{
					CAudio::Instance()->Play(AUDIO_GOODFLASH);
					m->addSX(-32 * HMS);
					x += 32 * HMS;
				}
				else
				{
					CAudio::Instance()->Play(AUDIO_BADFLASH);
				}
			}
			if (isMovingUp)
			{
				if (m->isEmpty(x + 10, y - 15 * HMS) && m->isEmpty(GetX2() - 10, y - 15 * HMS) && m->isEmpty(x + 10, y - 30 * HMS) && m->isEmpty(GetX2() - 10, y - 30 * HMS))
				{
					CAudio::Instance()->Play(AUDIO_GOODFLASH);
					m->addSY(32 * HMS);
					y -= 32 * HMS;
				}
				else
				{
					CAudio::Instance()->Play(AUDIO_BADFLASH);
				}
			}

			if (isMovingDown)
			{
				if (m->isEmpty(x + 10, GetY2() + 15 * HMS) && m->isEmpty(GetX2() - 10, GetY2() + 15 * HMS) && m->isEmpty(x + 10, GetY2() + 30 * HMS) && m->isEmpty(GetX2() - 10, GetY2() + 30 * HMS))
				{
					m->addSY(-32 * HMS);
					y += 32 * HMS;
				}
				else
				{
					CAudio::Instance()->Play(AUDIO_BADFLASH);
				}
			}
		}
		isUsingW = false;

	}

	void Hero::skillEMove()
	{
		if (skill_e_cool_down > 0) {
			skill_e_cool_down -= 1;
		}
		skillE.OnMove();
		if (!isUsingE)
			skillE.Reset(); 
	}

	void Hero::skillEShow()
	{
		if (isUsingE) {
			skillE.SetTopLeft(280 - 25, 280 - 15);
			skillE.OnShow();
			if (skillE.IsFinalBitmap()) {
				skillTimes += 1;			//+1代表跑了一回CAnimation
				if (skillTimes == 3) {
					skillTimes = 0;			//跑完整個技能把skillTime設回為0
					isUsingE = false;
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////

}
