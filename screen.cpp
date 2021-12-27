#include "DxLib.h"

//決定
bool Decision(char* keys, char* oldkeys, int pause) {
	if ((keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0) ||
		(keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
		&& pause == 0) {
		return true;
	}
	else {
		return false;
	}
}

//ポーズ(タイトルに戻る？)
void Pause(char* keys, int& pause, bool& pauseFlag, bool& start, int& scene,
	int pauseYesGH, int pauseNoGH, int pauseSE, int cursorSE, int ketteiSE, int cancelSE, int bgm) {
	if (pause == 0 && keys[KEY_INPUT_ESCAPE] == 1) {
		pause = 2;
		pauseFlag = true;
		PlaySoundMem(pauseSE, DX_PLAYTYPE_BACK, TRUE);
		StopSoundMem(bgm);
	}
	if (pause == 1) {//はい
		DrawGraph(490, 250, pauseYesGH, TRUE);
		if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_DOWN] == 1) {
			pause++;
			PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK, TRUE);
		}
		if (keys[KEY_INPUT_RETURN] == 1 || keys[KEY_INPUT_SPACE] == 1) {
			scene = 0;
			PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
		}
	}
	if (pause == 2) {//いいえ
		DrawGraph(490, 250, pauseNoGH, TRUE);
		if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_UP] == 1) {
			pause--;
			PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK, TRUE);
		}
		if (keys[KEY_INPUT_RETURN] == 1 || keys[KEY_INPUT_SPACE] == 1) {
			pause = 0;
			pauseFlag = false;
			PlaySoundMem(cancelSE, DX_PLAYTYPE_BACK, TRUE);
			if (start == true) {
				PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, false);
			}
			else if (start == false) {
				PlaySoundMem(bgm, DX_PLAYTYPE_BACK, false);
			}
		}
	}
}
