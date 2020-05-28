#ifndef UTIL_H
#define UTIL_H

	/////////////////////////////////////////////////////////////////////////////
	// �o��.h file �w�q�F�Ѽƪ��ȡA�i�H�����q�o�̨���						   //
	/////////////////////////////////////////////////////////////////////////////
	constexpr int OBJS_DEFAULT_SPEED = 4; //����T�w���ʳt��;
	constexpr int SMOOTH_MOVE_TRESHOLD = OBJS_DEFAULT_SPEED * 3 - 1; //���Ʋ��ʪ��e��

	constexpr int HERO_MOVE_SPEED = 5;		//�^�����ʳt��
	constexpr int SKILL_EVO_TVALUE = 22;	//�ޯ�i�ƪ�Treshold Value

	constexpr int MAX_ENEMY_PER_MAP = 10;//�̤j���ĤH�s�q

	const double PROB_ENEMY_TURN = 0.02;//�ĤH�۰���V���v
	const double PROB_ITEM_GEN = 0.005;//�����ĤH���_�������v
	///�H�U���U���
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
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
	//�H�U�O�@�ǯd�����D���d�ֱ���
	const char J_STG1_2 = 0x4F; //O
	const char J_STG1_4 = 0x50; //P
	const char J_STG1_6 = 0x4C; //L
	const char J_STG2_2 = 0x3A; //:
	const char J_STG2_4 = 0x3E; //>
	const char J_STG2_6 = 0x2F; // \/ (/)



	///����
	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
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

	enum STAGE {				// �w�q�U�ح��Ī��s��
		STAGE_1_1,				
		STAGE_1_2,
		STAGE_1_6,
		STAGE_2_1,
		STAGE_2_2,
		STAGE_2_3,
		STAGE_2_4,
	};

	enum ELEMENT_ATTRIBUTE {
		FIRE,					//���ݩ�
		ICE,					//�B�ݩ�
		PLANT,					//�Ӫ��ݩ�
		NO,

	};

	enum ATTACK_NAME {
		FIRE_BALL,				//���y
		ICE_BALL,				//Q�ޯ઺�B
		GRASS_BALL,				//Q�ޯ઺��
		FIRE_FLAME,

	};

#endif // !UTIL_H