#include "DxLib.h"

typedef struct Box {
	const int sizeX;
	const int sizeY;
	float x;
	float y;
}Box;

//スクロール
void Scroll(float& playerX, float& speed, int& scroll, const int scrollEnd) {
	if (scroll >= scrollEnd) {
		playerX += speed;
	}
	else {
		scroll += speed;
	}
}

//上昇
void UP(char* keys, char* oldkeys, float& yadd, bool freezeFlag, int upSE) {//上昇
	if (freezeFlag == false) {
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			yadd = -6.0f;
			PlaySoundMem(upSE, DX_PLAYTYPE_BACK,true);
		}
	}
}

//重力
void Gravity(float& playerY, float& yadd, float gravity) {
	playerY += yadd;
	yadd += gravity;

	if (yadd > 30.0f) {
		yadd = 30.0f;
	}
	if (yadd < -30.0f) {
		yadd = -30.0f;
	}
}

//上に行き過ぎると凍る
void Freeze(float& playerY, const int topY, bool& freezeFlag, int& freezeTimer ,int freezeySE) {
	if (playerY <= topY) {
		freezeFlag = true;
		if (CheckSoundMem(freezeySE) == 0) {
			PlaySoundMem(freezeySE, DX_PLAYTYPE_BACK, true);
		}
	}
	if (freezeFlag == true) {
		freezeTimer--;
		if (freezeTimer <= 0) {
			freezeFlag = false;
			freezeTimer = 40;
		}
	}
}