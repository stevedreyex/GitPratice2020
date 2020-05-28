#include "Enemy.h"

namespace game_framework {

	class Map1_2 : public Maps
	{
	public:
		Map1_2();
		~Map1_2();
		void Initialize();
		void setPos(int x, int y, int n);
		void setClear(bool b) override;
		bool isEmpty(int x, int y) const;
		bool inFinishArea(int x, int y) override;
		void OnMove();
		void LoadBitmap();
		void OnShow();
		void getHeroX(int x) override;
		void getHeroY(int y) override;
		int screenX(int x) override;
		int screenY(int y) override;

	private:
		CMovingBitmap firstmap;
		CAnimation gate;
		bool all_enemy_clear;
		int map[15][12];
		int hx, hy;
		int stage_left, stage_top;
	};
}