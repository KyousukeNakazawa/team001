#pragma once



typedef struct Object {
	float x; float y; int sizeX; int sizeY; float speed;
}Object;

//�����蔻��
bool ObjCollision(float& x1, float& y1, int sizex1, int sizey1, float& x2, float& y2, int sizex2, int sizey2);

//���̈ړ�����
void ObjMovePlus(float& x, float speed);
void ObjMoveMinus(float& x, float speed);

//�I�u�W�F�N�g����ʊO�ɏo���Ƃ��̏���
bool OffScreen(float pos, int screen);

//�^�C�}�[
void Timer(int& timer, int setTime);

//�A�j���[�V����
void AniGH(int& timer, int setTime, float x, float y, int GH);