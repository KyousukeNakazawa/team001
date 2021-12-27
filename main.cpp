#include "DxLib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "player.h"
#include "screen.h"


// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "Flight Avoid";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int cancelSE = LoadSoundMem("resource/sound/cancel.mp3");//キャンセル音
	ChangeVolumeSoundMem(160, cancelSE);
	int cursorSE = LoadSoundMem("resource/sound/cursor.mp3");//ステージ選択、ポーズ画面のカーソル音
	ChangeVolumeSoundMem(150, cursorSE);
	int ketteiSE = LoadSoundMem("resource/sound/stageselectkettei.mp3");//ステージ選択、ポーズ画面の決定音
	ChangeVolumeSoundMem(150, ketteiSE);
	int titleketteiSE = LoadSoundMem("resource/sound/titlekettei.mp3");//タイトル画面決定音
	ChangeVolumeSoundMem(150, titleketteiSE);
	int pauseSE = LoadSoundMem("resource/sound/pause.mp3");//ポーズ画面開く音
	ChangeVolumeSoundMem(130, pauseSE);
	int countdownSE = LoadSoundMem("resource/sound/Countdown.mp3");//カウントダウン、スタート
	ChangeVolumeSoundMem(130, countdownSE);

	int upSE = LoadSoundMem("resource/sound/up.mp3");//プレイヤー上昇
	ChangeVolumeSoundMem(100, upSE);
	int freezeySE = LoadSoundMem("resource/sound/freezey.mp3");//プレイヤー凍る
	ChangeVolumeSoundMem(140, freezeySE);
	int playerbakuhatuSE = LoadSoundMem("resource/sound/playerbakuhatu.mp3");//プレイヤー爆発音
	ChangeVolumeSoundMem(130, playerbakuhatuSE);
	int kumoHitSE = LoadSoundMem("resource/sound/kumoHit.mp3");//雲に当たった音
	ChangeVolumeSoundMem(150, kumoHitSE);
	int nijiHitSE = LoadSoundMem("resource/sound/nijiHit.mp3");//虹に当たった音
	ChangeVolumeSoundMem(150, nijiHitSE);
	int toriHitSE = LoadSoundMem("resource/sound/toriHit.mp3");//鳥に当たった音
	ChangeVolumeSoundMem(170, toriHitSE);
	int missileHitSE = LoadSoundMem("resource/sound/missileHit.mp3");//ミサイルに当たった音
	ChangeVolumeSoundMem(150, missileHitSE);
	int missileShotSE = LoadSoundMem("resource/sound/missileShot.mp3");//ミサイル発射音
	ChangeVolumeSoundMem(170, missileShotSE);
	int sirenSE = LoadSoundMem("resource/sound/siren.mp3");//敵機きたときの警告音
	ChangeVolumeSoundMem(160, sirenSE);

	int stage1BGM = LoadSoundMem("resource/sound/stage1BGM.mp3");
	ChangeVolumeSoundMem(100, stage1BGM);
	int stage2BGM = LoadSoundMem("resource/sound/stage2BGM.mp3");
	ChangeVolumeSoundMem(100, stage2BGM);
	int endlessBGM = LoadSoundMem("resource/sound/endlessBGM.mp3");
	ChangeVolumeSoundMem(100, endlessBGM);
	int gameclearBGM = LoadSoundMem("resource/sound/gameclearBGM.mp3");
	ChangeVolumeSoundMem(100, gameclearBGM);
	int gameoverBGM = LoadSoundMem("resource/sound/gameoverBGM.mp3");
	ChangeVolumeSoundMem(100, gameoverBGM);
	int titleBGM = LoadSoundMem("resource/sound/titleBGM.mp3");
	ChangeVolumeSoundMem(100, titleBGM);


	int bgm_null = LoadSoundMem("");

	int playerGH3[4];	//プレイヤーhp3
	LoadDivGraph("resource/picture/player.png", 4, 4, 1, 128, 64, playerGH3);

	int playerGH2[4];	//プレイヤーhp2
	LoadDivGraph("resource/picture/player2.png", 4, 4, 1, 128, 64, playerGH2);

	int playerGH1[4];	//プレイヤーhp1
	LoadDivGraph("resource/picture/player3.png", 4, 4, 1, 128, 64, playerGH1);

	int playerColdGH = LoadGraph("resource/picture/playerCold.png");//プレイヤー凍る


	int haikei = LoadGraph("resource/picture/backGround.png");//背景
	int startGH = LoadGraph("resource/picture/START.png");

	int titleGH = LoadGraph("resource/picture/title.png");//タイトル画面
	int gameOverGH = LoadGraph("resource/picture/gameOver.png");//ゲームオーバー画面
	int stageSelectGH[4];//ステージ選択画面
	LoadDivGraph("resource/picture/stageselect.png", 4, 4, 1, 1280, 720, stageSelectGH);
	int gameClearGH = LoadGraph("resource/picture/gameclear.png");//ゲームクリア画面
	int optionGH = LoadGraph("resource/picture/howtoplay.png");//遊び方画面
	int scoreGH = LoadGraph("resource/picture/score.png");//エンドレススコア画面

	int startCountGH[3];//ゲームスタートのカウントダウン
	LoadDivGraph("resource/picture/count.png", 3, 3, 1, 200, 200, startCountGH);

	int numberGH[10];//数字画像
	LoadDivGraph("resource/picture/num.png", 10, 10, 1, 48, 48, numberGH);
	int number2GH[10];//数字画像
	LoadDivGraph("resource/picture/num2.png", 10, 10, 1, 48, 48, number2GH);
	//int meterGH = LoadGraph("resource/picture/meter.png");//メートル

	int pauseYesGH = LoadGraph("resource/picture/titleyes.png");
	int pauseNoGH = LoadGraph("resource/picture/titleno.png");

	int birdGH[2];	//鳥
	LoadDivGraph("resource/picture/leftTori.png", 2, 2, 1, 32, 32, birdGH);

	int enemyGH[4];	//敵機
	LoadDivGraph("resource/picture/enemy.png", 4, 4, 1, 128, 64, enemyGH);

	int missileGH = LoadGraph("resource/picture/misairu.png");	//ミサイル

	int cloudGH = LoadGraph("resource/picture/kumo.png");	//雲

	int rainbowGH[7];	//虹
	LoadDivGraph("resource/picture/niji.png", 7, 7, 1, 32, 32, rainbowGH);

	int smallBuildGH = LoadGraph("resource/picture/biru1.png");	//建物
	int bigBuildGH = LoadGraph("resource/picture/biru2.png");

	int hpGH[8];	//ライフ
	LoadDivGraph("resource/picture/hp.png", 8, 8, 1, 32, 32, hpGH);

	int explosionGH[8];	//爆破エフェクト
	LoadDivGraph("resource/picture/explosion.png", 8, 8, 1, 64, 64, explosionGH);

	// ゲームループで使う変数の宣言
	//スコアのセーブ
	FILE* rfp;
	FILE* wfp;

	int error;// ファイルを読み込めたか
	char data[100];// ファイルから読み込んだデータ(文字列)
	int arr[3];// ファイルから読み込んだデータ(整数型)

	//プレイヤー
	Box player = { 128,64,256.0f,256.0f };

	float yadd = 0.0f;
	float gravity = 0.5f;
	const float defSpeed = 10.0f;
	float playerSpeed = defSpeed;//速度
	const int topY = 0;//画面の一番上

	const int endX = 12800;//画面の一番右

	int freezeTimer = 40;//凍る時間
	bool freezeFlag = false;//凍っているか

	bool isPlayerAlive = TRUE;
	const int lifeNum = 3;
	int playerLife = lifeNum;
	const int playerGHTime = 40;
	int playerGHTimer = 0;

	//スクロール
	int back[2] = { 0, 12800 };
	int scroll = 0;
	//const int scrollX = 740;
	const int scrollEnd = 11520;

	int scene = 0;//シーン
	enum Scene { TITLE, SELECT, STAGE1, STAGE2, ENDLESS, OPTION, GAMECLEAR, GAMEOVER, SCORE };
	bool retry = false;//ゲームオーバー画面、エンドレススコア用
	int old_scene = 0;
	int stage = 1;//ステージ選択

	bool start = FALSE;

	int pause = 0;
	bool pauseFlag = FALSE;
	int sound = 0;
	int countdownSEFlag = false;

	//オブジェクト情報
	enum Flag { OFF, ON, F_OFF };
	//最初は全て画面外に置いておく
	const int resetX = -500;
	const int resetY = 0;

	bool sirenFlag = false;

	//敵機
	const int enemyNum = 3;
	const int enemyPositionX = 750;	//自機と敵機の距離
	const int enemyPositionY = 180;
	int enemyFlag[enemyNum] = {};
	struct Object enemyPlane[enemyNum];	//ミサイルを打つ敵
	for (int i = 0; i < enemyNum; i++) {
		enemyPlane[i].sizeX = 128;
		enemyPlane[i].sizeY = 64;
		enemyPlane[i].x = player.x + enemyPositionX;
		enemyPlane[i].y = -enemyPlane[i].sizeY;
		enemyPlane[i].speed = 5;
	}
	const int enemyGHTime = 40;
	int enemyGHTimer = 0;
	const int enemyTime = 700;
	const int enemyTime2 = 400;
	int enemyTimer = 0;
	bool isEnemyFlag = false;

	//ミサイル
	const int missileNum = 9;
	int missileFlag[missileNum] = {};
	struct Object missile[missileNum];	//ミサイル
	for (int i = 0; i < missileNum; i++) {
		missile[i].sizeX = 128;
		missile[i].sizeY = 32;
		missile[i].x = player.x + enemyPositionX;
		missile[i].y = 0;
		missile[i].speed = 10;
	}
	const int missileTime = 30;
	int missileTimer = missileTime;	//ミサイル発射タイマー

	//建物
	const int buildNum = 5;
	int smallBuildFlag[buildNum] = {};
	int bigBuildFlag[buildNum] = {};
	struct Object smallBuild[buildNum];	//小さい建物
	struct Object bigBuild[buildNum];	//大きい建物
	for (int i = 0; i < buildNum; i++) {
		smallBuild[i].sizeX = 128;
		smallBuild[i].sizeY = 256;
		smallBuild[i].speed = playerSpeed;
		bigBuild[i].sizeX = 128;
		bigBuild[i].sizeY = 384;
		bigBuild[i].speed = playerSpeed;
	}
	const int smallBuildTime = 1000;
	const int bigBuildTime = 3000;
	int smallBuildTimer = smallBuildTime;
	int bigBuildTimer = bigBuildTime;

	//鳥
	const int birdNum = 50;
	const int birdRange = 200;
	int slowBirdFlag[birdNum] = {};
	int fastBirdFlag[birdNum] = {};
	struct Object slowBird[birdNum];	//遅い鳥
	struct Object fastBird[birdNum];	//速い鳥
	for (int i = 0; i < birdNum; i++) {	//ステージ1の配置
		slowBird[i].sizeX = 32;
		slowBird[i].sizeY = 32;
		slowBird[i].speed = 15;
		fastBird[i].sizeX = 32;
		fastBird[i].sizeY = 32;
		fastBird[i].speed = 20;
	}
	const int birdTimeEasy = 100;
	const int birdTimeNormal = 75;
	const int birdTimeHard = 50;
	int slowBirdTimer = birdTimeEasy;	//鳥が飛んでく間隔
	int fastBirdTimer = birdTimeEasy;
	const int birdGHTime = 20;
	int birdGHTimer = 0;

	//雲（スピードダウン）
	const int downSpeed = 5;
	const int gimmickNum = 5;
	const int cloudRange = 200;
	int cloudFlag[gimmickNum] = {};
	Object cloud[gimmickNum];
	for (int i = 0; i < gimmickNum; i++) {
		cloud[i].sizeX = 128;
		cloud[i].sizeY = 64;
		cloud[i].speed = playerSpeed;
	}
	const int cloudTime = 500;
	const int speedDownTime = 100;
	int cloudTimer = cloudTime;
	int speedDownTimer = speedDownTime;


	//虹（スピードアップ）
	const int upSpeed = 15;
	const int rainbowRange = 200;
	int rainbowFlag[gimmickNum] = {};
	Object rainbow[gimmickNum];
	for (int i = 0; i < gimmickNum; i++) {
		rainbow[i].sizeX = 32;
		rainbow[i].sizeY = 32;
		rainbow[i].speed = playerSpeed;
	}
	const int rainbowTime = 700;
	const int speedUpTime = 60;	//速度が上がり続ける時間
	int rainbowTimer = rainbowTime * 2;
	int speedUpTimer = speedUpTime;
	const int rainbowGHTime = 70;
	int rainbowGHTimer = 0;

	//爆破
	float brastX;
	float brastY;
	const int brastSizeX = 64;
	const int brastSizeY = 64;
	const int brastGHTime = 80;
	int brastGHTimer = 0;

	const int birdGHNum = 2;
	const int enemyGHNum = 4;
	const int rainbowGHNum = 7;
	const int hpGHNum = 8;
	const int explosionGHNum = 8;
	const int playerGHNum = 4;

	//UI
	//HP
	const int hpX = 32;
	const int hpY = 16;
	const int hpGHTime = 80;
	int hpGHTimer = 0;

	//カウントダウンタイマー
	const int startTime = 200;
	int startTimer = startTime;

	//数字画像化用
	const int digits = 11;
	char strNum[digits] = { 0 };
	int eachNum[digits] = { 0 };
	int score = 0;

	char strNumSave1[digits] = { 0 };
	int eachNumSave1[digits] = { 0 };

	char strNumSave2[digits] = { 0 };
	int eachNumSave2[digits] = { 0 };

	char strNumSave3[digits] = { 0 };
	int eachNumSave3[digits] = { 0 };

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i) {
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		//乱数取得
		srand(time(nullptr));

		switch (scene) {

		case TITLE://タイトル画面
			StopSoundMem(gameclearBGM);
			StopSoundMem(gameoverBGM);
			StopSoundMem(countdownSE);
			StopSoundMem(stage1BGM);
			StopSoundMem(stage2BGM);
			StopSoundMem(endlessBGM);
			if (CheckSoundMem(titleBGM) == 0) {
				PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, titleGH, true);
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				scene = 1;
				stage = 0;
				pause = 0;
				score = 0;
				PlaySoundMem(titleketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
			}
			memset(strNum, '\0', sizeof(strNum));

			/*DrawFormatString(0, 0, GetColor(255, 255, 255), "タイトル画面", TRUE);
			DrawFormatString(0, 15, GetColor(255, 255, 255), "スペースで進む", TRUE);*/
			break;

		case SELECT://ステージ選択画面

			//選ぶ
			if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0) {
				if (stage != 3)PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK, TRUE);
				stage++;
				if (stage >= 3) {
					stage = 3;
				}
			}
			if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0) {
				if (stage != 0)PlaySoundMem(cursorSE, DX_PLAYTYPE_BACK, TRUE);
				stage--;
				if (stage <= 0) {
					stage = 0;
				}
			}

			switch (stage) {
			case 0:
				if (Decision(keys, oldkeys, pause)) {
					scene = 2;//ステージ1
					StopSoundMem(titleBGM);
					PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
					//変数リセットする
					player.x = 256;
					player.y = 256;
					yadd = 0;
					isPlayerAlive = true;
					playerLife = 3;
					playerSpeed = defSpeed;
					scroll = 0;
					startTimer = startTime;
					start = false;
					pauseFlag = false;
					freezeFlag = false;
					countdownSEFlag = false;
					for (int i = 0; i < birdNum; i++) {
						slowBirdFlag[i] = OFF;
						fastBirdFlag[i] = OFF;
						slowBird[i].x = resetX;
						slowBird[i].y = resetY;
						fastBird[i].x = resetX;
						fastBird[i].y = resetY;

					}
					for (int i = 0; i < gimmickNum; i++) {
						cloudFlag[i] = OFF;
						rainbowFlag[i] = OFF;
						cloud[i].x = resetX;
						cloud[i].y = resetY;
					}
					for (int i = 0; i < buildNum; i++) {
						smallBuildFlag[i] = OFF;
						bigBuildFlag[i] = OFF;
						smallBuild[i].x = resetX;
						smallBuild[i].y = resetY;
						bigBuild[i].x = resetX;
						bigBuild[i].y = resetY;
					}
					smallBuildTimer = smallBuildTime;
					bigBuildTimer = bigBuildTime;
					cloudTimer = cloudTime;
					rainbowTimer = rainbowTime;
				}
				break;

			case 1:
				if (Decision(keys, oldkeys, pause)) {
					scene = 3;//ステージ2
					StopSoundMem(titleBGM);
					PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
					//変数リセットする
					player.x = 256;
					player.y = 256;
					yadd = 0;
					isPlayerAlive = true;
					playerSpeed = defSpeed;
					playerLife = 3;
					scroll = 0;
					startTimer = startTime;
					start = false;
					pauseFlag = false;
					freezeFlag = false;
					countdownSEFlag = false;
					for (int i = 0; i < birdNum; i++) {
						slowBirdFlag[i] = OFF;
						fastBirdFlag[i] = OFF;
						slowBird[i].x = resetX;
						slowBird[i].y = resetY;
						fastBird[i].x = resetX;
						fastBird[i].y = resetY;
					}
					for (int i = 0; i < gimmickNum; i++) {
						cloudFlag[i] = OFF;
						rainbowFlag[i] = OFF;
						rainbow[i].x = resetX;
						rainbow[i].y = resetY;
						cloud[i].x = resetX;
						cloud[i].y = resetY;
					}
					for (int i = 0; i < buildNum; i++) {
						smallBuildFlag[i] = OFF;
						bigBuildFlag[i] = OFF;
						smallBuild[i].x = resetX;
						smallBuild[i].y = resetY;
						bigBuild[i].x = resetX;
						bigBuild[i].y = resetY;
					}
					for (int i = 0; i < enemyNum; i++) {
						enemyFlag[i] = OFF;
						enemyPlane[i].y = -enemyPlane[i].sizeY;
					}
					for (int i = 0; i < missileNum; i++) {
						missileFlag[i] = OFF;
						missile[i].x = player.x + enemyPositionX;
						missile[i].y;
						missile[i].speed = 10;
					}
					enemyTimer = enemyTime2;
					smallBuildTimer = smallBuildTime;
					bigBuildTimer = bigBuildTime;
					cloudTimer = cloudTime;
					rainbowTimer = rainbowTime;
					isEnemyFlag = false;

				}
				break;

			case 2:
				if (Decision(keys, oldkeys, pause)) {
					scene = 4;//エンドレス
					StopSoundMem(titleBGM);
					PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
					//変数リセットする
					score = 0;
					player.x = 256;
					player.y = 256;
					yadd = 0;
					isPlayerAlive = true;
					playerSpeed = defSpeed;
					playerLife = 3;
					scroll = 0;
					startTimer = startTime;
					start = false;
					pauseFlag = false;
					freezeFlag = false;
					countdownSEFlag = false;
					for (int i = 0; i < birdNum; i++) {
						slowBirdFlag[i] = OFF;
						fastBirdFlag[i] = OFF;
						slowBird[i].x = resetX;
						slowBird[i].y = resetY;
						fastBird[i].x = resetX;
						fastBird[i].y = resetY;
					}
					for (int i = 0; i < gimmickNum; i++) {
						cloudFlag[i] = OFF;
						rainbowFlag[i] = OFF;
						rainbow[i].x = resetX;
						rainbow[i].y = resetY;
						cloud[i].x = resetX;
						cloud[i].y = resetY;
					}
					for (int i = 0; i < buildNum; i++) {
						smallBuildFlag[i] = OFF;
						bigBuildFlag[i] = OFF;
						smallBuild[i].x = resetX;
						smallBuild[i].y = resetY;
						bigBuild[i].x = resetX;
						bigBuild[i].y = resetY;
					}
					for (int i = 0; i < enemyNum; i++) {
						enemyFlag[i] = OFF;
						enemyPlane[i].y = -enemyPlane[i].sizeY;
					}
					for (int i = 0; i < missileNum; i++) {
						missileFlag[i] = OFF;
						missile[i].x = player.x + enemyPositionX;
						missile[i].y;
						missile[i].speed = 10;
					}
					enemyTimer = enemyTime;
					smallBuildTimer = smallBuildTime;
					bigBuildTimer = bigBuildTime;
					cloudTimer = cloudTime;
					rainbowTimer = rainbowTime;
					isEnemyFlag = false;
					back[0] = 0;
					back[1] = 12800;
				}
				break;

			case 3:
				if (Decision(keys, oldkeys, pause)) {
					scene = 5;//遊び方
					PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
				}
				break;
			}

			DrawGraph(0, 0, stageSelectGH[stage], true);


			//DrawFormatString(0, 0, GetColor(255, 255, 255), "ステージ選択画面\n矢印で選択、spaceで決定", TRUE);
			////DrawFormatString(0, 30, GetColor(255, 255, 255), "stage:%d", stage, TRUE);
			//if (stage == 1)DrawFormatString(0, 40, GetColor(255, 255, 255), "ステージ1", TRUE);
			//if (stage == 2)DrawFormatString(0, 40, GetColor(255, 255, 255), "ステージ2", TRUE);
			//if (stage == 3)DrawFormatString(0, 40, GetColor(255, 255, 255), "エンドレス", TRUE);
			//if (stage == 4)DrawFormatString(0, 40, GetColor(255, 255, 255), "遊び方", TRUE);
			break;

		case STAGE1:	//ステージ1

			//背景描画
			DrawGraph(0 - scroll, 0, haikei, true);

			//タイマーが0になったらスタート
			if (startTimer >= 0 && pauseFlag == false && start == false) {//タイマーが0以上のとき

				startTimer--;
				if (startTimer <= 0) {
					pauseFlag = false;
					start = TRUE;
					PlaySoundMem(stage1BGM, DX_PLAYTYPE_BACK, TRUE);
				}
				if (CheckSoundMem(countdownSE) == 0 && countdownSEFlag == false) {
					PlaySoundMem(countdownSE, DX_PLAYTYPE_BACK, TRUE);
					countdownSEFlag = true;
				}
				//描画
				//プレイヤー
				DrawGraph(player.x, player.y, playerGH3[0], true);

				//カウントダウン
				if (startTimer >= 50) {
					for (int i = 0; i < 3; i++) {
						DrawGraph(WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2 - 100, startCountGH[(startTimer - 50) / 50], true);
					}
				}
				else {
					DrawGraph(WIN_WIDTH / 2 - 200, WIN_HEIGHT / 2 - 100, startGH, true);
				}
			}

			if (start == true && pauseFlag == false && isPlayerAlive == true) {
				/*if (CheckSoundMem(stage1BGM) == 0) {
					PlaySoundMem(stage1BGM, DX_PLAYTYPE_BACK, FALSE);
				}*/

				if (isPlayerAlive == true) {
					//強制スクロール
					Scroll(player.x, playerSpeed, scroll, scrollEnd);

					//上昇
					UP(keys, oldkeys, yadd, freezeFlag, upSE);

					//重力
					Gravity(player.y, yadd, gravity);

					//上に行き過ぎると凍る
					Freeze(player.y, topY, freezeFlag, freezeTimer, freezeySE);
				}

				//鳥
				//移動処理
				//遅い鳥 進むにつれて難易度アップ
				if (scroll >= 0 && scroll < WIN_WIDTH * 2) {
					Timer(slowBirdTimer, birdTimeEasy);
				}
				else if (scroll >= WIN_WIDTH * 2 && scroll < WIN_WIDTH * 5) {
					Timer(slowBirdTimer, birdTimeNormal);
				}
				else {
					Timer(slowBirdTimer, birdTimeHard);
				}

				for (int i = 0; i < birdNum; i++) {
					if (slowBirdTimer <= 0 && slowBirdFlag[i] == OFF) {
						slowBirdFlag[i] = ON;
						slowBird[i].x = WIN_WIDTH;
						slowBird[i].y = (rand() * 100) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (slowBirdFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(slowBird[i].x + slowBird[i].sizeX, 0)) {
							slowBirdFlag[i] = OFF;
						}
						//当たり判定
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, slowBird[i].x, slowBird[i].y, slowBird[i].sizeX, slowBird[i].sizeY)) {
							slowBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//移動
						ObjMoveMinus(slowBird[i].x, slowBird[i].speed);

						//描画
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, slowBird[i].x, slowBird[i].y, birdGH[j]);
					}
				}

				//速い鳥 進むにつれて難易度アップ
				if (scroll >= WIN_WIDTH * 2 && scroll < WIN_WIDTH * 5) {
					Timer(fastBirdTimer, birdTimeNormal);
				}
				else if (scroll >= WIN_WIDTH * 5) {
					Timer(fastBirdTimer, birdTimeHard);
				}
				for (int i = 0; i < birdNum; i++) {
					if (fastBirdTimer <= 0 && fastBirdFlag[i] == OFF) {
						fastBirdFlag[i] = ON;
						//座標更新
						fastBird[i].x = WIN_WIDTH;
						fastBird[i].y = (rand() * 150) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (fastBirdFlag[i] == ON) {
						//画面外に出るかプレイヤーに当たったら消える
						if (OffScreen(fastBird[i].x + fastBird[i].sizeX, 0)) {
							fastBirdFlag[i] = OFF;
						}
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, fastBird[i].x, fastBird[i].y, fastBird[i].sizeX, fastBird[i].sizeY)) {
							fastBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//移動
						ObjMoveMinus(fastBird[i].x, fastBird[i].speed);

						//描画
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, fastBird[i].x, fastBird[i].y, birdGH[j]);
					}
				}

				//建物の処理
				for (int i = 0; i < buildNum; i++) {
					if (scroll > WIN_WIDTH * 5 && smallBuildFlag[i] == OFF) {
						smallBuildFlag[i] = ON;
						//座標設定
						smallBuild[i].x = WIN_WIDTH * (i + 1);
						smallBuild[i].y = WIN_HEIGHT - smallBuild[i].sizeY;
					}
					if (smallBuildFlag[i] == ON) {
						//プレイヤーに当たったらhp -3
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, smallBuild[i].x, smallBuild[i].y, smallBuild[i].sizeX, smallBuild[i].sizeY)) {
							playerLife -= 3;
						}

						//画面外に出たら消える
						if (OffScreen(smallBuild[i].x + smallBuild[i].sizeX, 0)) {
							smallBuildFlag[i] = F_OFF;
						}

						//移動
						ObjMoveMinus(smallBuild[i].x, smallBuild[i].speed);

						//描画
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
					}
				}

				//雲の処理
				for (int i = 0; i < gimmickNum; i++) {
					//タイマー
					Timer(cloudTimer, cloudTime);
					if (cloudTimer <= 0 && cloudFlag[i] == OFF) {
						cloudFlag[i] = ON;
						//座標更新
						cloud[i].x = WIN_WIDTH;
						cloud[i].y = (rand() * 200) % (WIN_HEIGHT - cloudRange);
					}
					if (cloudFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(cloud[i].x + cloud[i].sizeX, 0)) {
							cloudFlag[i] = OFF;
						}

						//当たると速度dowm
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, cloud[i].x, cloud[i].y, cloud[i].sizeX, cloud[i].sizeY)) {
							cloudFlag[i] = F_OFF;
							PlaySoundMem(kumoHitSE, DX_PLAYTYPE_BACK, TRUE);
						}
					}

					//移動
					ObjMoveMinus(cloud[i].x, cloud[i].speed);

					if (cloudFlag[i] == F_OFF) {
						playerSpeed = downSpeed;
						speedDownTimer--;
					}
					if (speedDownTimer <= 0) {
						playerSpeed = defSpeed;
						cloudFlag[i] = OFF;
						speedDownTimer = speedDownTime;
					}
					//描画
					DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);

				}

				//虹の処理
				for (int i = 0; i < gimmickNum; i++) {
					Timer(rainbowTimer, rainbowTime);
					if (rainbowTimer <= 0 && rainbowFlag[i] == OFF) {
						rainbowFlag[i] = ON;
						//座標更新
						rainbow[i].x = WIN_WIDTH;
						rainbow[i].y = (rand() * 300) % (WIN_HEIGHT - rainbowRange);
					}
					if (rainbowFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(rainbow[i].x + rainbow[i].sizeX, 0)) {
							rainbowFlag[i] = OFF;
						}

						//移動
						ObjMoveMinus(rainbow[i].x, rainbow[i].speed);

						//当たったら速度up
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, rainbow[i].x, rainbow[i].y, rainbow[i].sizeX, rainbow[i].sizeY)) {
							rainbowFlag[i] = F_OFF;
							PlaySoundMem(nijiHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//描画
						int j = rainbowGHTimer / (rainbowGHTime / rainbowGHNum);
						AniGH(rainbowGHTimer, rainbowGHTime, rainbow[i].x, rainbow[i].y, rainbowGH[j]);
					}
					if (rainbowFlag[i] == F_OFF) {
						playerSpeed = upSpeed;
						speedUpTimer--;
					}
					if (speedUpTimer <= 0) {
						playerSpeed = defSpeed;
						rainbowFlag[i] = OFF;
						speedUpTimer = speedUpTime;
					}
				}

				//クリア
				if (player.x + scroll >= 12800) {
					scene = GAMECLEAR;
					StopSoundMem(stage1BGM);
				}

				//画面外に落下でゲームオーバー
				if (player.y >= WIN_HEIGHT) {
					isPlayerAlive = false;
					StopSoundMem(stage1BGM);
					if (CheckSoundMem(playerbakuhatuSE) == 0) {
						PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}

				//プレイヤー生きてるときはプレイヤー描画
				if (isPlayerAlive == true) {
					//プレイヤー凍ってるときは凍ってる画像を描画
					if (freezeFlag == true) {
						DrawGraph(player.x, player.y, playerColdGH, true);
					}
					//凍ってないとき
					if (freezeFlag == false) {
						//プレイヤー hp数によって変化
						int playerGH;
						int j = playerGHTimer / (playerGHTime / playerGHNum);
						if (playerLife == 3) {
							playerGH = playerGH3[j];
						}
						else if (playerLife == 2) {
							playerGH = playerGH2[j];
						}
						else {
							playerGH = playerGH1[j];
						}
						AniGH(playerGHTimer, playerGHTime, player.x, player.y, playerGH);
					}
				}
			}

			//ライフが無くなったら爆発して画面切り替え
			if (playerLife <= 0) {
				isPlayerAlive = false;
				StopSoundMem(stage1BGM);
				if (CheckSoundMem(playerbakuhatuSE) == 0) {
					PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			if (isPlayerAlive == false) {
				brastX = player.x;
				brastY = player.y;
				int j = brastGHTimer / (brastGHTime / explosionGHNum);
				AniGH(brastGHTimer, brastGHTime, brastX, brastY, explosionGH[j]);
				if (brastGHTimer <= 0) {
					scene = GAMEOVER;
				}
			}

			//ポーズ中も描画
			if (pauseFlag == true || isPlayerAlive == false) {

				//プレイヤー
				if (isPlayerAlive == true) {
					DrawGraph(player.x, player.y, playerGH3[0], true);
				}

				//鳥
				for (int i = 0; i < birdNum; i++) {
					if (slowBirdFlag[i] == ON || fastBirdFlag[i] == ON) {
						DrawGraph(slowBird[i].x, slowBird[i].y, birdGH[0], true);
						DrawGraph(fastBird[i].x, fastBird[i].y, birdGH[0], true);
					}
				}

				//建物
				for (int i = 0; i < buildNum; i++) {
					if (smallBuildFlag[i] == ON || bigBuildFlag[i] == ON) {
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
						DrawGraph(bigBuild[i].x, bigBuild[i].y, smallBuildGH, true);
					}
				}

				//ギミック
				for (int i = 0; i < gimmickNum; i++) {
					if (cloudFlag[i] == ON || rainbowFlag[i] == ON) {
						DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);
						DrawGraph(rainbow[i].x, rainbow[i].y, rainbowGH[0], true);
					}
				}
			}

			//UI
			//HP
			for (int i = 0; i < playerLife; i++) {
				int j = hpGHTimer / (hpGHTime / hpGHNum);
				AniGH(hpGHTimer, hpGHTime, WIN_WIDTH - hpX * 6 + hpX * (i + 2), hpY, hpGH[j]);
			}


			if (start == true) {
				sound = stage1BGM;
			}
			else if (start == false) {
				sound = countdownSE;
			}
			//ポーズ
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, sound);


			/*DrawFormatString(0, 0, GetColor(255, 255, 255), "cloud[0].x:%d", cloud[0].x);
			DrawFormatString(0, 15, GetColor(255, 255, 255), "cloudTimer:%d", cloudTimer);*/

			break;

		case STAGE2:
			//BGM
			//背景描画
			DrawGraph(0 - scroll, 0, haikei, true);

			//タイマーが0になったらスタート
			if (startTimer >= 0 && pauseFlag == false && start == false) {//タイマーが0以上のとき
				startTimer--;
				if (startTimer <= 0) {
					pauseFlag = false;
					start = TRUE;
					PlaySoundMem(stage2BGM, DX_PLAYTYPE_BACK, TRUE);
				}
				if (CheckSoundMem(countdownSE) == 0 && countdownSEFlag == false) {
					PlaySoundMem(countdownSE, DX_PLAYTYPE_BACK, TRUE);
					countdownSEFlag = true;
				}

				//描画
				//プレイヤー
				DrawGraph(player.x, player.y, playerGH3[0], true);

				//カウントダウン
				if (startTimer >= 50) {
					for (int i = 0; i < 3; i++) {
						DrawGraph(WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2 - 100, startCountGH[(startTimer - 50) / 50], true);
					}
				}
				else {
					DrawGraph(WIN_WIDTH / 2 - 200, WIN_HEIGHT / 2 - 100, startGH, true);
				}
			}

			if (start == true && pauseFlag == false && isPlayerAlive == true) {

				if (isPlayerAlive == true) {
					//強制スクロール
					Scroll(player.x, playerSpeed, scroll, scrollEnd);

					//上昇
					UP(keys, oldkeys, yadd, freezeFlag, upSE);

					//重力
					Gravity(player.y, yadd, gravity);

					//上に行き過ぎると凍る
					Freeze(player.y, topY, freezeFlag, freezeTimer, freezeySE);
				}

				//鳥の処理
				//遅い鳥 進むにつれて難易度アップ
				if (scroll >= 0 && scroll < WIN_WIDTH * 3) {
					Timer(slowBirdTimer, birdTimeHard);
				}
				else if (scroll >= WIN_WIDTH * 3 && scroll < WIN_WIDTH * 6) {
					Timer(slowBirdTimer, birdTimeNormal);
				}
				else {
					Timer(slowBirdTimer, birdTimeHard);
				}
				for (int i = 0; i < birdNum; i++) {
					if (slowBirdTimer <= 0 && slowBirdFlag[i] == OFF) {
						slowBirdFlag[i] = ON;
						//座標更新
						slowBird[i].x = WIN_WIDTH;
						slowBird[i].y = (rand() * 100) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (slowBirdFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(slowBird[i].x + slowBird[i].sizeX, 0)) {
							slowBirdFlag[i] = OFF;
						}
						//当たり判定
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, slowBird[i].x, slowBird[i].y, slowBird[i].sizeX, slowBird[i].sizeY)) {
							slowBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//移動
						ObjMoveMinus(slowBird[i].x, slowBird[i].speed);

						//描画
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, slowBird[i].x, slowBird[i].y, birdGH[j]);
					}
				}

				//速い鳥 進むにつれて難易度アップ
				if (scroll >= 0 && scroll < WIN_WIDTH * 3) {
					Timer(fastBirdTimer, birdTimeEasy);
				}
				else if (scroll >= WIN_WIDTH * 3 && scroll < WIN_WIDTH * 6) {
					Timer(fastBirdTimer, birdTimeNormal);
				}
				else {
					Timer(fastBirdTimer, birdTimeHard);
				}
				for (int i = 0; i < birdNum; i++) {
					if (fastBirdTimer <= 0 && fastBirdFlag[i] == OFF) {
						fastBirdFlag[i] = ON;
						//座標更新
						fastBird[i].x = WIN_WIDTH;
						fastBird[i].y = (rand() * 150) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (fastBirdFlag[i] == ON) {
						//画面外に出るかプレイヤーに当たったら消える
						if (OffScreen(fastBird[i].x + fastBird[i].sizeX, 0)) {
							fastBirdFlag[i] = OFF;
						}
						//当たり判定
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, fastBird[i].x, fastBird[i].y, fastBird[i].sizeX, fastBird[i].sizeY)) {
							fastBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//移動
						ObjMoveMinus(fastBird[i].x, fastBird[i].speed);

						//描画
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, fastBird[i].x, fastBird[i].y, birdGH[j]);
					}
				}

				//建物の処理
				for (int i = 0; i < buildNum; i++) {
					if (scroll > WIN_WIDTH * 6 && bigBuildFlag[i] == OFF) {
						bigBuildFlag[i] = ON;
						//座標設定
						bigBuild[i].x = WIN_WIDTH * (i + 1);
						bigBuild[i].y = WIN_HEIGHT - bigBuild[i].sizeY;
					}
					if (bigBuildFlag[i] == ON) {
						//プレイヤーに当たったらhp -3
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, bigBuild[i].x, bigBuild[i].y, bigBuild[i].sizeX, bigBuild[i].sizeY)) {
							playerLife -= 3;
						}

						//画面外に出たら消える
						if (OffScreen(bigBuild[i].x + bigBuild[i].sizeX, 0)) {
							bigBuildFlag[i] = F_OFF;
						}

						//移動
						ObjMoveMinus(bigBuild[i].x, bigBuild[i].speed);

						//描画
						DrawGraph(bigBuild[i].x, bigBuild[i].y, bigBuildGH, true);
					}
				}

				//雲の処理
				for (int i = 0; i < gimmickNum; i++) {
					//タイマー
					Timer(cloudTimer, cloudTime);
					if (cloudTimer <= 0 && cloudFlag[i] == OFF) {
						cloudFlag[i] = ON;
						//座標更新
						cloud[i].x = WIN_WIDTH;
						cloud[i].y = (rand() * 200) % (WIN_HEIGHT - cloudRange);
					}
					if (cloudFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(cloud[i].x + cloud[i].sizeX, 0)) {
							cloudFlag[i] = OFF;
						}

						//当たると速度dowm
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, cloud[i].x, cloud[i].y, cloud[i].sizeX, cloud[i].sizeY)) {
							cloudFlag[i] = F_OFF;
							PlaySoundMem(kumoHitSE, DX_PLAYTYPE_BACK, TRUE);
						}
					}

					//移動
					ObjMoveMinus(cloud[i].x, cloud[i].speed);

					if (cloudFlag[i] == F_OFF) {
						playerSpeed = downSpeed;
						speedDownTimer--;
					}
					if (speedDownTimer <= 0) {
						playerSpeed = defSpeed;
						cloudFlag[i] = OFF;
						speedDownTimer = speedDownTime;
					}
					//描画
					DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);

				}

				//虹の処理
				for (int i = 0; i < gimmickNum; i++) {
					Timer(rainbowTimer, rainbowTime);
					if (rainbowTimer <= 0 && rainbowFlag[i] == OFF) {
						rainbowFlag[i] = ON;
						//座標更新
						rainbow[i].x = WIN_WIDTH;
						rainbow[i].y = (rand() * 300) % (WIN_HEIGHT - rainbowRange);
					}
					if (rainbowFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(rainbow[i].x + rainbow[i].sizeX, 0)) {
							rainbowFlag[i] = OFF;
						}

						//移動
						ObjMoveMinus(rainbow[i].x, rainbow[i].speed);

						//当たったら速度up
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, rainbow[i].x, rainbow[i].y, rainbow[i].sizeX, rainbow[i].sizeY)) {
							rainbowFlag[i] = F_OFF;
							PlaySoundMem(nijiHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//描画
						int j = rainbowGHTimer / (rainbowGHTime / rainbowGHNum);
						AniGH(rainbowGHTimer, rainbowGHTime, rainbow[i].x, rainbow[i].y, rainbowGH[j]);
					}
					if (rainbowFlag[i] == F_OFF) {
						playerSpeed = upSpeed;
						speedUpTimer--;
					}
					if (speedUpTimer <= 0) {
						playerSpeed = defSpeed;
						rainbowFlag[i] = OFF;
						speedUpTimer = speedUpTime;
					}
				}

				//ミサイルの処理
				//位置についたらタイマー始動
				if (enemyPlane[2].y >= enemyPositionY * 3) {
					Timer(missileTimer, missileTime);
				}
				for (int i = 0; i < missileNum; i++) {
					//タイマーが0になったらミサイル発射
					if (missileTimer <= 0 && missileFlag[i] == OFF) {
						missileFlag[i] = ON;
						PlaySoundMem(missileShotSE, DX_PLAYTYPE_BACK, TRUE);
						//ミサイル座標更新
						if (i % enemyNum == 0) {
							missile[i].y = enemyPositionY * 1;
						}
						else if (i % enemyNum == 1) {
							missile[i].y = enemyPositionY * 2;
						}
						else if (i % enemyNum == 2) {
							missile[i].y = enemyPositionY * 3;
						}
						break;
					}

					//ミサイルが左へ移動
					if (missileFlag[i] == ON) {
						//当たったらライフが減る
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, missile[i].x, missile[i].y, missile[i].sizeX, missile[i].sizeY)) {
							missileFlag[i] = OFF;
						}
						if (missileFlag[i] == OFF) {
							playerLife -= 2;
							missileFlag[i] = F_OFF;
							PlaySoundMem(missileHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//画面外に出たら消える
						if (OffScreen(missile[i].x + missile[i].sizeX, 0)) {
							missileFlag[i] = F_OFF;
						}

						//移動
						ObjMoveMinus(missile[i].x, missile[i].speed);

						//描画
						DrawGraph(missile[i].x, missile[i].y, missileGH, true);
					}
				}


				//敵機の登場処理
				for (int i = 0; i < enemyNum; i++) {
					if (isEnemyFlag == true) {
						enemyFlag[i] = ON;

					}
					//ミサイル発射位置についたら止まる
					if (enemyFlag[i] == ON && enemyPlane[i].y >= enemyPositionY * (i + 1)) {
						enemyPlane[i].y = enemyPositionY * (i + 1);
					}
					//一定の場所まで行くと登場
					else if (enemyFlag[i] == ON && missile[8].x > 0) {
						ObjMovePlus(enemyPlane[i].y, enemyPlane[i].speed);
					}
					//ミサイルを打ち切ったらフェードアウト
					if (enemyFlag[i] == ON && missile[8].x < 0) {
						enemyFlag[i] = OFF;
					}
					if (enemyFlag[i] == OFF && enemyPlane[i].y > -enemyPlane[i].sizeY) {
						ObjMoveMinus(enemyPlane[i].y, enemyPlane[i].speed);
					}

					//	描画
					int j = enemyGHTimer / (enemyGHTime / enemyGHNum);
					AniGH(enemyGHTimer, enemyGHTime, enemyPlane[i].x, enemyPlane[i].y, enemyGH[j]);
				}

				//タイマーが0になったら飛行機がでてくる
				if (enemyTimer >= 0 && isEnemyFlag == false) {
					enemyTimer--;
					if (enemyTimer == 0) {
						isEnemyFlag = true;
						enemyTimer = enemyTime2;
						PlaySoundMem(sirenSE, DX_PLAYTYPE_BACK, true);
					}
				}

				//クリア
				if (player.x + scroll >= 12800) {
					scene = GAMECLEAR;
					StopSoundMem(stage2BGM);
				}

				//画面外に落下でゲームオーバー
				if (player.y >= WIN_HEIGHT) {
					isPlayerAlive = false;
					StopSoundMem(stage2BGM);
					if (CheckSoundMem(playerbakuhatuSE) == 0) {
						PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}

				//プレイヤー生きてるときはプレイヤー描画
				if (isPlayerAlive == true) {
					//プレイヤー凍ってるときは凍ってる画像を描画
					if (freezeFlag == true) {
						DrawGraph(player.x, player.y, playerColdGH, true);
					}
					//凍ってないとき
					if (freezeFlag == false) {
						//プレイヤー hp数によって変化
						int playerGH;
						int j = playerGHTimer / (playerGHTime / playerGHNum);
						if (playerLife == 3) {
							playerGH = playerGH3[j];
						}
						else if (playerLife == 2) {
							playerGH = playerGH2[j];
						}
						else {
							playerGH = playerGH1[j];
						}
						AniGH(playerGHTimer, playerGHTime, player.x, player.y, playerGH);
					}
				}
				//ライフが無くなったら爆発して画面切り替え
				if (playerLife <= 0) {
					isPlayerAlive = false;
					if (CheckSoundMem(playerbakuhatuSE) == 0) {
						StopSoundMem(stage2BGM);
						PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}
			}
			if (isPlayerAlive == false) {
				brastX = player.x;
				brastY = player.y;
				int j = brastGHTimer / (brastGHTime / explosionGHNum);
				AniGH(brastGHTimer, brastGHTime, brastX, brastY, explosionGH[j]);
				if (brastGHTimer <= 0) {
					scene = GAMEOVER;
				}
			}


			//ポーズ中も描画
			if (pauseFlag == true || isPlayerAlive == false) {

				//プレイヤー
				if (isPlayerAlive == true) {
					DrawGraph(player.x, player.y, playerGH3[0], true);
				}
				//鳥
				for (int i = 0; i < birdNum; i++) {
					if (slowBirdFlag[i] == ON || fastBirdFlag[i] == ON) {
						DrawGraph(slowBird[i].x, slowBird[i].y, birdGH[0], true);
						DrawGraph(fastBird[i].x, fastBird[i].y, birdGH[0], true);
					}
				}

				//建物
				for (int i = 0; i < buildNum; i++) {
					if (smallBuildFlag[i] == ON || bigBuildFlag[i] == ON) {
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
						DrawGraph(bigBuild[i].x, bigBuild[i].y, bigBuildGH, true);
					}
				}

				//ミサイル
				for (int i = 0; i < missileNum; i++) {
					if (missileFlag[i] == ON) {
						DrawGraph(missile[i].x, missile[i].y, missileGH, true);
					}
				}

				//敵機
				for (int i = 0; i < enemyNum; i++) {
					if (enemyFlag[i] == ON) {
						DrawGraph(enemyPlane[i].x, enemyPlane[i].y, enemyGH[0], true);
					}
				}

				//ギミック
				for (int i = 0; i < gimmickNum; i++) {
					if (cloudFlag[i] == ON || rainbowFlag[i] == ON) {
						DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);
						DrawGraph(rainbow[i].x, rainbow[i].y, rainbowGH[0], true);
					}
				}
			}

			//UI
			//HP
			for (int i = 0; i < playerLife; i++) {
				int j = hpGHTimer / (hpGHTime / hpGHNum);
				AniGH(hpGHTimer, hpGHTime, WIN_WIDTH - hpX * (i + 2), hpY, hpGH[j]);
			}

			if (start == true) {
				sound = stage2BGM;
			}
			else if (start == false) {
				sound = countdownSE;
			}
			//ポーズ
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, sound);

			//確認
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "TIMER:%d", TIMER);
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "cloudTimer:%d", cloudTimer);

			break;

		case ENDLESS:
			//背景描画
			DrawGraph(back[0] - scroll, 0, haikei, true);
			DrawGraph(back[1] - scroll, 0, haikei, true);

			//配列に格納
			score = scroll / 50;
			sprintf_s(strNum, sizeof(strNum), "%d", score);

			//オフセット値に合わせる
			for (int i = 0; i < digits; i++) {
				eachNum[i] = strNum[i] - 48;
			}

			//タイマーが0になったらスタート
			if (startTimer > 0 && pauseFlag == false && start == false) {//タイマーが0以上のとき
				startTimer--;
				if (startTimer <= 0) {
					pauseFlag = false;
					start = TRUE;
					PlaySoundMem(endlessBGM, DX_PLAYTYPE_LOOP, TRUE);
				}
				if (CheckSoundMem(countdownSE) == 0 && countdownSEFlag == false) {
					PlaySoundMem(countdownSE, DX_PLAYTYPE_BACK, TRUE);
					countdownSEFlag = true;
				}
				//描画
				//プレイヤー
				DrawGraph(player.x, player.y, playerGH3[0], true);

				//カウントダウン
				if (startTimer >= 50) {
					for (int i = 0; i < 3; i++) {
						DrawGraph(WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2 - 100, startCountGH[(startTimer - 50) / 50], true);
					}
				}
				else {
					DrawGraph(WIN_WIDTH / 2 - 200, WIN_HEIGHT / 2 - 100, startGH, true);
				}
			}

			if (start == true && pauseFlag == false && isPlayerAlive == true) {

				if (isPlayerAlive == true) {
					//強制スクロール
					scroll += playerSpeed;
					for (int i = 0; i < 2; i++) {
						if (back[i] - scroll <= -WIN_WIDTH * 10) {
							back[i] = WIN_WIDTH * 10 + scroll;
						}
					}

					//上昇
					UP(keys, oldkeys, yadd, freezeFlag, upSE);


					//重力
					Gravity(player.y, yadd, gravity);

					//上に行き過ぎると凍る
					Freeze(player.y, topY, freezeFlag, freezeTimer, freezeySE);
				}

				//鳥
				//移動処理
				//遅い鳥 進むにつれて難易度アップ
				if (scroll >= 0 && scroll < WIN_WIDTH * 5) {
					Timer(slowBirdTimer, birdTimeEasy);
				}
				else if (scroll >= WIN_WIDTH * 5 && scroll < WIN_WIDTH * 10) {
					Timer(slowBirdTimer, birdTimeNormal);
				}
				else {
					Timer(slowBirdTimer, birdTimeHard);
				}

				for (int i = 0; i < birdNum; i++) {
					if (slowBirdTimer <= 0 && slowBirdFlag[i] == OFF) {
						slowBirdFlag[i] = ON;
						slowBird[i].x = WIN_WIDTH;
						slowBird[i].y = (rand() * 100) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (slowBirdFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(slowBird[i].x + slowBird[i].sizeX, 0)) {
							slowBirdFlag[i] = OFF;
						}
						//当たり判定
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, slowBird[i].x, slowBird[i].y, slowBird[i].sizeX, slowBird[i].sizeY)) {
							slowBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//移動
						ObjMoveMinus(slowBird[i].x, slowBird[i].speed);

						//描画
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, slowBird[i].x, slowBird[i].y, birdGH[j]);
					}
				}

				//速い鳥 進むにつれて難易度アップ
				if (scroll >= WIN_WIDTH * 5 && scroll < WIN_WIDTH * 10) {
					Timer(fastBirdTimer, birdTimeEasy);
				}
				else if (scroll >= WIN_WIDTH * 10 && scroll < WIN_WIDTH * 15) {
					Timer(fastBirdTimer, birdTimeNormal);
				}
				else if (scroll >= WIN_WIDTH * 15) {
					Timer(fastBirdTimer, birdTimeHard);
				}
				for (int i = 0; i < birdNum; i++) {
					if (fastBirdTimer <= 0 && fastBirdFlag[i] == OFF) {
						fastBirdFlag[i] = ON;
						//座標更新
						fastBird[i].x = WIN_WIDTH;
						fastBird[i].y = (rand() * 150) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (fastBirdFlag[i] == ON) {
						//画面外に出るかプレイヤーに当たったら消える
						if (OffScreen(fastBird[i].x + fastBird[i].sizeX, 0)) {
							fastBirdFlag[i] = OFF;
						}
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, fastBird[i].x, fastBird[i].y, fastBird[i].sizeX, fastBird[i].sizeY)) {
							fastBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//移動
						ObjMoveMinus(fastBird[i].x, fastBird[i].speed);

						//描画
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, fastBird[i].x, fastBird[i].y, birdGH[j]);
					}
				}



				//雲の処理
				for (int i = 0; i < gimmickNum; i++) {
					//タイマー
					Timer(cloudTimer, cloudTime);
					if (cloudTimer <= 0 && cloudFlag[i] == OFF) {
						cloudFlag[i] = ON;
						//座標更新
						cloud[i].x = WIN_WIDTH;
						cloud[i].y = (rand() * 200) % (WIN_HEIGHT - cloudRange);
					}
					if (cloudFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(cloud[i].x + cloud[i].sizeX, 0)) {
							cloudFlag[i] = OFF;
						}

						//当たると速度dowm
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, cloud[i].x, cloud[i].y, cloud[i].sizeX, cloud[i].sizeY)) {
							cloudFlag[i] = F_OFF;
							PlaySoundMem(kumoHitSE, DX_PLAYTYPE_BACK, TRUE);
						}
					}

					//移動
					ObjMoveMinus(cloud[i].x, cloud[i].speed);

					if (cloudFlag[i] == F_OFF) {
						playerSpeed = downSpeed;
						speedDownTimer--;
					}
					if (speedDownTimer <= 0) {
						playerSpeed = defSpeed;
						cloudFlag[i] = OFF;
						speedDownTimer = speedDownTime;
					}
					//描画
					DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);

				}

				//虹の処理
				for (int i = 0; i < gimmickNum; i++) {
					Timer(rainbowTimer, rainbowTime);
					if (rainbowTimer <= 0 && rainbowFlag[i] == OFF) {
						rainbowFlag[i] = ON;
						//座標更新
						rainbow[i].x = WIN_WIDTH;
						rainbow[i].y = (rand() * 300) % (WIN_HEIGHT - rainbowRange);
					}
					if (rainbowFlag[i] == ON) {
						//画面外に出たら消える
						if (OffScreen(rainbow[i].x + rainbow[i].sizeX, 0)) {
							rainbowFlag[i] = OFF;
						}

						//移動
						ObjMoveMinus(rainbow[i].x, rainbow[i].speed);

						//当たったら速度up
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, rainbow[i].x, rainbow[i].y, rainbow[i].sizeX, rainbow[i].sizeY)) {
							rainbowFlag[i] = F_OFF;
							PlaySoundMem(nijiHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//描画
						int j = rainbowGHTimer / (rainbowGHTime / rainbowGHNum);
						AniGH(rainbowGHTimer, rainbowGHTime, rainbow[i].x, rainbow[i].y, rainbowGH[j]);
					}
					if (rainbowFlag[i] == F_OFF) {
						playerSpeed = upSpeed;
						speedUpTimer--;
					}
					if (speedUpTimer <= 0) {
						playerSpeed = defSpeed;
						rainbowFlag[i] = OFF;
						speedUpTimer = speedUpTime;
					}
				}
				//建物の処理
				//小さい
				for (int i = 0; i < buildNum; i++) {
					Timer(smallBuildTimer, smallBuildTime);
					if (smallBuildTimer <= 0 && smallBuildFlag[i] == OFF) {
						smallBuildFlag[i] = ON;
						//座標設定
						smallBuild[i].x = WIN_WIDTH + 100;
						smallBuild[i].y = WIN_HEIGHT - smallBuild[i].sizeY;
						break;
					}
					if (smallBuildFlag[i] == ON) {
						//プレイヤーに当たったらhp -3
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, smallBuild[i].x, smallBuild[i].y, smallBuild[i].sizeX, smallBuild[i].sizeY)) {
							playerLife -= 3;
						}

						//画面外に出たら消える
						if (OffScreen(smallBuild[i].x + smallBuild[i].sizeX, 0)) {
							smallBuildFlag[i] = OFF;
						}

						//移動
						ObjMoveMinus(smallBuild[i].x, smallBuild[i].speed);

						//描画
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
					}
				}

				//大きい
				for (int i = 0; i < buildNum; i++) {
					Timer(bigBuildTimer, bigBuildTime);
					if (bigBuildTimer <= 0 && bigBuildFlag[i] == OFF) {
						bigBuildFlag[i] = ON;
						//座標設定
						bigBuild[i].x = WIN_WIDTH + 800;
						bigBuild[i].y = WIN_HEIGHT - bigBuild[i].sizeY;
						break;
					}
					if (bigBuildFlag[i] == ON) {
						//プレイヤーに当たったらhp -3
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, bigBuild[i].x, bigBuild[i].y, bigBuild[i].sizeX, bigBuild[i].sizeY)) {
							playerLife -= 3;
						}

						//画面外に出たら消える
						if (OffScreen(bigBuild[i].x + bigBuild[i].sizeX, 0)) {
							bigBuildFlag[i] = OFF;
						}

						//移動
						ObjMoveMinus(bigBuild[i].x, bigBuild[i].speed);

						//描画
						DrawGraph(bigBuild[i].x, bigBuild[i].y, bigBuildGH, true);
					}
				}

				//ミサイルの処理
				//位置についたらタイマー始動
				if (enemyPlane[2].y >= enemyPositionY * 3) {
					Timer(missileTimer, missileTime);
				}
				for (int i = 0; i < missileNum; i++) {
					//タイマーが0になったらミサイル発射
					if (missileTimer <= 0 && missileFlag[i] == OFF) {
						missileFlag[i] = ON;
						PlaySoundMem(missileShotSE, DX_PLAYTYPE_BACK, TRUE);
						//ミサイル座標更新
						if (i % enemyNum == 0) {
							missile[i].y = enemyPositionY * 1;
						}
						else if (i % enemyNum == 1) {
							missile[i].y = enemyPositionY * 2;
						}
						else if (i % enemyNum == 2) {
							missile[i].y = enemyPositionY * 3;
						}
						break;
					}

					//ミサイルが左へ移動
					if (missileFlag[i] == ON) {
						//当たったらライフが減る
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, missile[i].x, missile[i].y, missile[i].sizeX, missile[i].sizeY)) {
							missileFlag[i] = OFF;
						}
						if (missileFlag[i] == OFF) {
							playerLife -= 2;
							missileFlag[i] = F_OFF;
							PlaySoundMem(missileHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//画面外に出たら消える
						if (OffScreen(missile[i].x + missile[i].sizeX, 0)) {
							missileFlag[i] = F_OFF;
						}

						//移動
						ObjMoveMinus(missile[i].x, missile[i].speed);

						//描画
						DrawGraph(missile[i].x, missile[i].y, missileGH, true);
					}
				}

				//敵機の登場処理
				for (int i = 0; i < enemyNum; i++) {
					if (isEnemyFlag == true) {
						enemyFlag[i] = ON;
					}
					//ミサイル発射位置についたら止まる
					if (enemyFlag[i] == ON && enemyPlane[i].y >= enemyPositionY * (i + 1)) {
						enemyPlane[i].y = enemyPositionY * (i + 1);
					}
					//一定の場所まで行くと登場
					else if (enemyFlag[i] == ON && missile[8].x > 0) {
						ObjMovePlus(enemyPlane[i].y, enemyPlane[i].speed);
					}
					//ミサイルを打ち切ったらフェードアウト
					if (enemyFlag[i] == ON && missile[8].x < 0) {
						enemyFlag[i] = OFF;
						isEnemyFlag = false;
					}
					if (enemyFlag[i] == OFF && enemyPlane[i].y > -enemyPlane[i].sizeY) {
						ObjMoveMinus(enemyPlane[i].y, enemyPlane[i].speed);
					}

					//	描画
					int j = enemyGHTimer / (enemyGHTime / enemyGHNum);
					AniGH(enemyGHTimer, enemyGHTime, enemyPlane[i].x, enemyPlane[i].y, enemyGH[j]);
				}

				//タイマーが0になったら飛行機がでてくる
				if (enemyTimer >= 0 && isEnemyFlag == false) {
					enemyTimer--;
					if (enemyTimer == 0) {
						for (int i = 0; i < enemyNum; i++) {
							enemyFlag[i] = OFF;
							enemyPlane[i].y = -enemyPlane[i].sizeY;
						}
						for (int i = 0; i < missileNum; i++) {
							missileFlag[i] = OFF;
							missile[i].x = player.x + enemyPositionX;
							missile[i].y;
							missile[i].speed = 10;
						}
						enemyTimer = enemyTime;
						isEnemyFlag = true;
						PlaySoundMem(sirenSE, DX_PLAYTYPE_BACK, true);
					}
				}

				//画面外に落下でゲームオーバー
				if (player.y >= WIN_HEIGHT) {
					isPlayerAlive = false;
					StopSoundMem(endlessBGM);
					if (CheckSoundMem(playerbakuhatuSE) == 0) {
						PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}

				//プレイヤー生きてるときはプレイヤー描画
				if (isPlayerAlive == true) {
					//プレイヤー凍ってるときは凍ってる画像を描画
					if (freezeFlag == true) {
						DrawGraph(player.x, player.y, playerColdGH, true);
					}
					//凍ってないとき
					if (freezeFlag == false) {
						//プレイヤー hp数によって変化
						int playerGH;
						int j = playerGHTimer / (playerGHTime / playerGHNum);
						if (playerLife == 3) {
							playerGH = playerGH3[j];
						}
						else if (playerLife == 2) {
							playerGH = playerGH2[j];
						}
						else {
							playerGH = playerGH1[j];
						}
						AniGH(playerGHTimer, playerGHTime, player.x, player.y, playerGH);
					}
				}

				//ライフが無くなったら爆発して画面切り替え
				if (playerLife <= 0) {
					isPlayerAlive = false;
					StopSoundMem(endlessBGM);
					if (CheckSoundMem(playerbakuhatuSE) == 0) {
						PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}
			}
			if (isPlayerAlive == false) {
				brastX = player.x;
				brastY = player.y;
				int j = brastGHTimer / (brastGHTime / explosionGHNum);
				AniGH(brastGHTimer, brastGHTime, brastX, brastY, explosionGH[j]);
				if (brastGHTimer <= 0) {
					scene = SCORE;
				}
			}

			//ポーズ中も描画
			if (pauseFlag == true || isPlayerAlive == false) {

				//プレイヤー
				if (isPlayerAlive == true) {
					DrawGraph(player.x, player.y, playerGH3[0], true);
				}

				//鳥
				for (int i = 0; i < birdNum; i++) {
					if (slowBirdFlag[i] == ON || fastBirdFlag[i] == ON) {
						DrawGraph(slowBird[i].x, slowBird[i].y, birdGH[0], true);
						DrawGraph(fastBird[i].x, fastBird[i].y, birdGH[0], true);
					}
				}

				//建物
				for (int i = 0; i < buildNum; i++) {
					if (smallBuildFlag[i] == ON || bigBuildFlag[i] == ON) {
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
						DrawGraph(bigBuild[i].x, bigBuild[i].y, bigBuildGH, true);
					}
				}

				//ミサイル
				for (int i = 0; i < missileNum; i++) {
					if (missileFlag[i] == ON) {
						DrawGraph(missile[i].x, missile[i].y, missileGH, true);
					}
				}

				//敵機
				for (int i = 0; i < enemyNum; i++) {
					if (enemyFlag[i] == ON) {
						DrawGraph(enemyPlane[i].x, enemyPlane[i].y, enemyGH[0], true);
					}
				}

				//ギミック
				for (int i = 0; i < gimmickNum; i++) {
					if (cloudFlag[i] == ON || rainbowFlag[i] == ON) {
						DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);
						DrawGraph(rainbow[i].x, rainbow[i].y, rainbowGH[0], true);
					}
				}
			}

			//UI
			//HP
			for (int i = 0; i < playerLife; i++) {
				int j = hpGHTimer / (hpGHTime / hpGHNum);
				AniGH(hpGHTimer, hpGHTime, WIN_WIDTH - hpX * (i + 2), hpY, hpGH[j]);
			}

			//距離
			for (int i = 0; i < digits; i++) {
				DrawGraph(48 * i + 32, 16, numberGH[eachNum[i]], true);
			}

			if (start == true) {
				sound = endlessBGM;
			}
			else if (start == false) {
				sound = countdownSE;
			}
			//ポーズ
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, sound);;

			//DrawFormatString(0, 0, GetColor(255, 255, 255), "score:%d", true);
			//確認
			/*DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", playerSpeed);
			DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", enemyTimer);
			DrawFormatString(0, 150, GetColor(255, 255, 255), "%d", isEnemyFlag);
			DrawFormatString(0, 150, GetColor(255, 255, 255), "score:%d", score, true);
			DrawFormatString(0, 165, GetColor(255, 255, 255), "scroll:%d", scroll, true);*/

			break;

		case OPTION://操作方法
			DrawGraph(0, 0, optionGH, true);
			if (keys[KEY_INPUT_ESCAPE] == 1 && oldkeys[KEY_INPUT_ESCAPE] == 0) {
				scene = 1;
				PlaySoundMem(cancelSE, DX_PLAYTYPE_BACK, TRUE);
			}
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "遊び方\nESCでステージ選択に戻る", TRUE);
			break;

		case GAMECLEAR://ゲームクリア
			if (CheckSoundMem(gameclearBGM) == 0) {
				PlaySoundMem(gameclearBGM, DX_PLAYTYPE_LOOP, TRUE);
			}

			DrawGraph(0, 0, gameClearGH, true);
			//ポーズ
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, bgm_null);

			//DrawFormatString(0, 0, GetColor(255, 255, 255), "クリア画面\nスペースでタイトルに戻る", TRUE);
			break;

		case GAMEOVER://ゲームオーバー
			if (CheckSoundMem(gameoverBGM) == 0) {
				PlaySoundMem(gameoverBGM, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, gameOverGH, true);
			//ポーズ
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, bgm_null);

			//DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームオーバー画面\nスペースでタイトルに戻る", TRUE);
			break;

		case SCORE://エンドレスモードスコア
			StopSoundMem(endlessBGM);
			if (CheckSoundMem(gameclearBGM) == 0) {
				PlaySoundMem(gameclearBGM, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, scoreGH, true);
			//距離
			for (int i = 0; i < digits; i++) {
				DrawGraph(48 * i + 700, 230, numberGH[eachNum[i]], true);
			}
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, bgm_null);

			//スコアをセーブするやつ
			// ---------- ファイル読み込み(read) ----------
			error = fopen_s(&rfp, "resource/save.txt", "r");

			int digitCount = 0;// 何行読み込んだか
			while (fgets(data, 100, rfp) != NULL)
			{
				int tmp = atoi(data);// ascii to int
				arr[digitCount] = tmp;
				digitCount++;
			}

			fclose(rfp);// 閉じる
			// ---------- スコアを更新 ----------
			if (arr[0] < score)
			{
				arr[2] = arr[1];
				arr[1] = arr[0];
				arr[0] = score;
			}
			else if (arr[1] < score && arr[0] > score)
			{
				arr[2] = arr[1];
				arr[1] = score;
			}
			else if (arr[2] < score && arr[1] > score)
			{
				arr[2] = score;
			}
			// ---------- ファイルに更新した値を書き込む(write) ----------
			error = fopen_s(&wfp, "resource/save.txt", "w");

			// ファイルに書き込み
			for (int i = 0; i < 3; ++i)
			{
				fprintf(wfp, "%d\n", arr[i]);
			}

			fclose(wfp);// 閉じる

			//スコアランキング描画
			sprintf_s(strNumSave1, sizeof(strNumSave1), "%d", arr[0]);
			sprintf_s(strNumSave2, sizeof(strNumSave2), "%d", arr[1]);
			sprintf_s(strNumSave3, sizeof(strNumSave3), "%d", arr[2]);

			//オフセット値に合わせる
			for (int i = 0; i < digits; i++) {
				eachNumSave1[i] = strNumSave1[i] - 48;
				eachNumSave2[i] = strNumSave2[i] - 48;
				eachNumSave3[i] = strNumSave3[i] - 48;
			}

			//距離
			for (int i = 0; i < digits; i++) {
				DrawGraph(48 * i + 700, 515, number2GH[eachNumSave1[i]], true);
				DrawGraph(48 * i + 700, 570, number2GH[eachNumSave2[i]], true);
				DrawGraph(48 * i + 700, 625, number2GH[eachNumSave3[i]], true);
			}
			/*DrawFormatString(0, 675, GetColor(255, 255, 255), "arr[0]:%d", arr[0], true);
			DrawFormatString(0, 690, GetColor(255, 255, 255), "arr[1]:%d", arr[1], true);
			DrawFormatString(0, 705, GetColor(255, 255, 255), "arr[2]:%d", arr[2], true);*/

			break;
		}


		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (keys[KEY_INPUT_TAB] == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}