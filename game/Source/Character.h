#ifndef CHARACTER_H
#define CHARACTER_H
#include "Maps.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////
	class Character
	{
	protected:
		Character(string name) {
			_name = name;
		}

		Character() {

		}

		string getName();

		virtual void OnShow(Maps *m) {};


	private:
		string _name;

	};
	

	
}

#endif // !CHARACTER_H