#ifndef UTIL_H
#define UTIL_H

	/////////////////////////////////////////////////////////////////////////////
	// 這個.h file 定義了參數的值，可以直接從這裡取用						   //
	/////////////////////////////////////////////////////////////////////////////
	constexpr int OBJS_DEFAULT_SPEED = 4; //物件固定移動速度;
	constexpr int SMOOTH_MOVE_TRESHOLD = OBJS_DEFAULT_SPEED * 3 - 1; //平滑移動門檻值

	constexpr int HERO_MOVE_SPEED = 5;		//英雄移動速度
	constexpr int SKILL_EVO_TVALUE = 22;	//技能進化的Treshold Value

	constexpr int MAX_ENEMY_PER_MAP = 10;//最大的敵人存量

	const double PROB_ENEMY_TURN = 0.02;//敵人自動轉向機率
	const double PROB_ITEM_GEN = 0.005;//打死敵人生寶物的機率
	///以下為各鍵值
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_A = 0x41;
	const char KEY_Q = 0x51;
	const char KEY_W = 0x57;
	const char KEY_E = 0x45;
	const char KEY_R = 0x52;
	const char CTRL = 17;
	const char NUM_0 = 0x30;	
	const char NUM_1 = 0x31;
	const char NUM_2 = 0x32;
	const char NUM_3 = 0x33;
	const char NUM_4 = 0x34;
	const char NUM_5 = 0x35;
	const char NUM_6 = 0x36;
	const char NUM_7 = 0x37;
	const char NUM_8 = 0x38;
	const char NUM_9 = 0x39	;
	//以下是一些留給跳躍關卡快捷鍵
	const char J_STG1_2 = 0x4F; //O
	const char J_STG1_4 = 0x50; //P
	const char J_STG1_6 = 0x4C; //L
	const char J_STG2_2 = 0x3A; //:
	const char J_STG2_4 = 0x3E; //>
	const char J_STG2_6 = 0x2F; // \/ (/)



	///音效
	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT,				// 2
		AUDIO_GOLDENWIND,		// 3
		AUDIO_SWORD,			// 4
		AUDIO_FIRE,				// 5
		AUDIO_SKILLE,			// 6
		Audio_KNIFE,			//7
		AUDIO_ICE,
		AUDIO_HITTING,
		AUDIO_GRASSBALL,
		AUDIO_BEGGER,
		AUDIO_AWAKEN,
		AUDIO_DAMAGE1,
		AUDIO_ABOSS_WALK,
		AUDIO_ABOSS_PREPARE,
		AUDIO_GOODFLASH,
		AUDIO_BADFLASH
	};

	enum STAGE {				// 定義各種音效的編號
		STAGE_1_1,				
		STAGE_1_2,
		STAGE_1_6,
		STAGE_2_1,
		STAGE_2_2,
		STAGE_2_3,
		STAGE_2_4,
	};

	enum ELEMENT_ATTRIBUTE {
		FIRE,					//火屬性
		ICE,					//冰屬性
		PLANT,					//植物屬性
		NO,

	};

	enum ATTACK_NAME {
		FIRE_BALL,				//火球
		ICE_BALL,				//Q技能的冰
		GRASS_BALL,				//Q技能的草
		FIRE_FLAME,

	};

#endif // !UTIL_H