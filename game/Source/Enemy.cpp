#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Potion.h"
#include "Clock.h"


namespace game_framework {

	Enemy::Enemy() : Character("scarecrow")
	{
		_x = 384;
		_y = 384;
		hp = 1200;
		attack = 0;
	}

	Enemy::Enemy(int x, int y, int monsterHp, string name, Hero *h, ELEMENT_ATTRIBUTE a) : Character(name)
	{
		_x = x;
		_y = y;
		ini_x = x;
		ini_y = y;
		hp = monsterHp;
		attack = 0;
		isAttacking = false;
		hero_on_map = h;
		_attribute = a;
		if (GetName() != "Box") {
			items.push_back(new Health());
		}
	}

	Enemy::~Enemy()
	{
		for (vector<Item*>::iterator it_i = items.begin(); it_i != items.end(); ++it_i) {
			delete *it_i;
		}
	}

	int Enemy::distanceToHero()
	{
		int x_distance = _x - hero_on_map->GetX1();
		int y_distance = _y - hero_on_map->GetY1();
		return (int)(sqrt(pow(x_distance, 2) + pow(y_distance, 2)));
	}

	void Enemy::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void Enemy::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void Enemy::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void Enemy::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void Enemy::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void Enemy::offsetHP(int offset, ELEMENT_ATTRIBUTE attribute)
	{
		if (GetName() == "Box") {
			hp -= 1;
		}
		else {
			if (isCounterAttribute(_attribute, attribute)) {
				hp += (offset * 2);

			}
			else if (isCounterAttribute(attribute, _attribute)) {
				hp += (offset / 2);
			}
			else {
				hp += offset;
			}
			knockBack();
		}
		
	}
		
	

	void Enemy::itemsOnMove(Maps * m)
	{
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->OnMove(m, hero_on_map);
		}
	}

	void Enemy::itemsOnShow(Maps *m)
	{
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->setXY(_x + 32, _y + 32);
			items.at(i)->OnShow(m);
		}
	}

	bool Enemy::isAlive()
	{
		if (hp <= 0) {
			return false;
		}
		return true;
	}

	CRect * Enemy::GetRect()
	{
		return &EnemyRect;
	}

	bool Enemy::isAttack()
	{
		return isAttacking;
	}

	bool Enemy::isCounterAttribute(ELEMENT_ATTRIBUTE a, ELEMENT_ATTRIBUTE b)
	{
		if (a == FIRE) {
			if (b == ICE) {
				return true;
			}
		}
		if (a == ICE) {
			if (b == PLANT) {
				return true;
			}
		}
		if (a == PLANT) {
			if (b == FIRE) {
				return true;
			}
		}
		return false;
	}

	void Enemy::knockBack()
	{
		if (_direction == 0) {
			_x += 1;
		}
		if (_direction == 1) {
			_x -= 1;
		}
	}

	string Enemy::GetName()
	{
		return getName();
	}

}
