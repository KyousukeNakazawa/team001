#pragma once



typedef struct Object {
	float x; float y; int sizeX; int sizeY; float speed;
}Object;

//当たり判定
bool ObjCollision(float& x1, float& y1, int sizex1, int sizey1, float& x2, float& y2, int sizex2, int sizey2);

//鳥の移動処理
void ObjMovePlus(float& x, float speed);
void ObjMoveMinus(float& x, float speed);

//オブジェクトが画面外に出たときの処理
bool OffScreen(float pos, int screen);

//タイマー
void Timer(int& timer, int setTime);

//アニメーション
void AniGH(int& timer, int setTime, float x, float y, int GH);