#pragma once

typedef struct Box {
	const int sizeX;
	const int sizeY;
	float x;
	float y;
}Box;

//�X�N���[��
void Scroll(float& playerX, float& speed, int& scroll, const int scrollEnd);

//�㏸
void UP(char* keys, char* oldkeys, float& yadd, bool freezeFlag, int upSE);

//�d��
void Gravity(float& playerY, float& yadd, float gravity);

//��ɍs���߂���Ɠ���
void Freeze(float& playerY, const int topY, bool& freezeFlag, int& freezeTimer, int freezeySE);