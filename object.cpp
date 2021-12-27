#include "DxLib.h"

typedef struct Object {
	float x; float y; int sizeX; int sizeY; float speed;
}Object;

//�����蔻��
bool ObjCollision(float& x1, float& y1, int sizex1, int sizey1, float& x2, float& y2, int sizex2, int sizey2) {
	float ax1 = x1;
	float ay1 = y1;
	float ax2 = x1 + sizex1;
	float ay2 = y1 + sizey1;

	float bx1 = x2;
	float by1 = y2;
	float bx2 = x2 + sizex2;
	float by2 = y2 + sizey2;

	return bx1 < ax2&& ax1 < bx2&& by1 < ay2&& ay1 < by2;
}

//�I�u�W�F�N�g�ړ�����
void ObjMovePlus(float& pos, float speed) {
	pos += speed;
}
void ObjMoveMinus(float& pos, float speed) {
	pos -= speed;
}

//�I�u�W�F�N�g����ʊO�ɏo���Ƃ��̏���
bool OffScreen(float pos, int screen) {
	return pos < screen;
}

//�^�C�}�[
void Timer(int& timer, int setTime) {
	timer--;
	if (timer < 0) {
		timer = setTime;
	}
}

//�A�j���[�V����
void AniGH(int& timer, int setTime, float x, float y, int GH) {
	timer++;
	if (timer >= setTime) {
		timer = 0;
	}
	DrawGraph(x, y, GH, true);
}