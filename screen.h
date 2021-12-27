#pragma once

//決定
bool Decision(char* keys, char* oldkeys, int pause);

//ポーズ(タイトルに戻る)
void Pause(char* keys, int& pause, bool& pauseFlag, bool& start, int& scene,
	int pauseYesGH, int pauseNoGH, int pauseSE, int cursorSE, int ketteiSE, int cancelSE,int bgm);