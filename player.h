#pragma once

typedef struct Box {
	const int sizeX;
	const int sizeY;
	float x;
	float y;
}Box;

//スクロール
void Scroll(float& playerX, float& speed, int& scroll, const int scrollEnd);

//上昇
void UP(char* keys, char* oldkeys, float& yadd, bool freezeFlag, int upSE);

//重力
void Gravity(float& playerY, float& yadd, float gravity);

//上に行き過ぎると凍る
void Freeze(float& playerY, const int topY, bool& freezeFlag, int& freezeTimer, int freezeySE);