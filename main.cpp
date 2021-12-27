#include "DxLib.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "player.h"
#include "screen.h"


// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "Flight Avoid";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 720;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int cancelSE = LoadSoundMem("resource/sound/cancel.mp3");//�L�����Z����
	ChangeVolumeSoundMem(160, cancelSE);
	int cursorSE = LoadSoundMem("resource/sound/cursor.mp3");//�X�e�[�W�I���A�|�[�Y��ʂ̃J�[�\����
	ChangeVolumeSoundMem(150, cursorSE);
	int ketteiSE = LoadSoundMem("resource/sound/stageselectkettei.mp3");//�X�e�[�W�I���A�|�[�Y��ʂ̌��艹
	ChangeVolumeSoundMem(150, ketteiSE);
	int titleketteiSE = LoadSoundMem("resource/sound/titlekettei.mp3");//�^�C�g����ʌ��艹
	ChangeVolumeSoundMem(150, titleketteiSE);
	int pauseSE = LoadSoundMem("resource/sound/pause.mp3");//�|�[�Y��ʊJ����
	ChangeVolumeSoundMem(130, pauseSE);
	int countdownSE = LoadSoundMem("resource/sound/Countdown.mp3");//�J�E���g�_�E���A�X�^�[�g
	ChangeVolumeSoundMem(130, countdownSE);

	int upSE = LoadSoundMem("resource/sound/up.mp3");//�v���C���[�㏸
	ChangeVolumeSoundMem(100, upSE);
	int freezeySE = LoadSoundMem("resource/sound/freezey.mp3");//�v���C���[����
	ChangeVolumeSoundMem(140, freezeySE);
	int playerbakuhatuSE = LoadSoundMem("resource/sound/playerbakuhatu.mp3");//�v���C���[������
	ChangeVolumeSoundMem(130, playerbakuhatuSE);
	int kumoHitSE = LoadSoundMem("resource/sound/kumoHit.mp3");//�_�ɓ���������
	ChangeVolumeSoundMem(150, kumoHitSE);
	int nijiHitSE = LoadSoundMem("resource/sound/nijiHit.mp3");//���ɓ���������
	ChangeVolumeSoundMem(150, nijiHitSE);
	int toriHitSE = LoadSoundMem("resource/sound/toriHit.mp3");//���ɓ���������
	ChangeVolumeSoundMem(170, toriHitSE);
	int missileHitSE = LoadSoundMem("resource/sound/missileHit.mp3");//�~�T�C���ɓ���������
	ChangeVolumeSoundMem(150, missileHitSE);
	int missileShotSE = LoadSoundMem("resource/sound/missileShot.mp3");//�~�T�C�����ˉ�
	ChangeVolumeSoundMem(170, missileShotSE);
	int sirenSE = LoadSoundMem("resource/sound/siren.mp3");//�G�@�����Ƃ��̌x����
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

	int playerGH3[4];	//�v���C���[hp3
	LoadDivGraph("resource/picture/player.png", 4, 4, 1, 128, 64, playerGH3);

	int playerGH2[4];	//�v���C���[hp2
	LoadDivGraph("resource/picture/player2.png", 4, 4, 1, 128, 64, playerGH2);

	int playerGH1[4];	//�v���C���[hp1
	LoadDivGraph("resource/picture/player3.png", 4, 4, 1, 128, 64, playerGH1);

	int playerColdGH = LoadGraph("resource/picture/playerCold.png");//�v���C���[����


	int haikei = LoadGraph("resource/picture/backGround.png");//�w�i
	int startGH = LoadGraph("resource/picture/START.png");

	int titleGH = LoadGraph("resource/picture/title.png");//�^�C�g�����
	int gameOverGH = LoadGraph("resource/picture/gameOver.png");//�Q�[���I�[�o�[���
	int stageSelectGH[4];//�X�e�[�W�I�����
	LoadDivGraph("resource/picture/stageselect.png", 4, 4, 1, 1280, 720, stageSelectGH);
	int gameClearGH = LoadGraph("resource/picture/gameclear.png");//�Q�[���N���A���
	int optionGH = LoadGraph("resource/picture/howtoplay.png");//�V�ѕ����
	int scoreGH = LoadGraph("resource/picture/score.png");//�G���h���X�X�R�A���

	int startCountGH[3];//�Q�[���X�^�[�g�̃J�E���g�_�E��
	LoadDivGraph("resource/picture/count.png", 3, 3, 1, 200, 200, startCountGH);

	int numberGH[10];//�����摜
	LoadDivGraph("resource/picture/num.png", 10, 10, 1, 48, 48, numberGH);
	int number2GH[10];//�����摜
	LoadDivGraph("resource/picture/num2.png", 10, 10, 1, 48, 48, number2GH);
	//int meterGH = LoadGraph("resource/picture/meter.png");//���[�g��

	int pauseYesGH = LoadGraph("resource/picture/titleyes.png");
	int pauseNoGH = LoadGraph("resource/picture/titleno.png");

	int birdGH[2];	//��
	LoadDivGraph("resource/picture/leftTori.png", 2, 2, 1, 32, 32, birdGH);

	int enemyGH[4];	//�G�@
	LoadDivGraph("resource/picture/enemy.png", 4, 4, 1, 128, 64, enemyGH);

	int missileGH = LoadGraph("resource/picture/misairu.png");	//�~�T�C��

	int cloudGH = LoadGraph("resource/picture/kumo.png");	//�_

	int rainbowGH[7];	//��
	LoadDivGraph("resource/picture/niji.png", 7, 7, 1, 32, 32, rainbowGH);

	int smallBuildGH = LoadGraph("resource/picture/biru1.png");	//����
	int bigBuildGH = LoadGraph("resource/picture/biru2.png");

	int hpGH[8];	//���C�t
	LoadDivGraph("resource/picture/hp.png", 8, 8, 1, 32, 32, hpGH);

	int explosionGH[8];	//���j�G�t�F�N�g
	LoadDivGraph("resource/picture/explosion.png", 8, 8, 1, 64, 64, explosionGH);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//�X�R�A�̃Z�[�u
	FILE* rfp;
	FILE* wfp;

	int error;// �t�@�C����ǂݍ��߂���
	char data[100];// �t�@�C������ǂݍ��񂾃f�[�^(������)
	int arr[3];// �t�@�C������ǂݍ��񂾃f�[�^(�����^)

	//�v���C���[
	Box player = { 128,64,256.0f,256.0f };

	float yadd = 0.0f;
	float gravity = 0.5f;
	const float defSpeed = 10.0f;
	float playerSpeed = defSpeed;//���x
	const int topY = 0;//��ʂ̈�ԏ�

	const int endX = 12800;//��ʂ̈�ԉE

	int freezeTimer = 40;//���鎞��
	bool freezeFlag = false;//�����Ă��邩

	bool isPlayerAlive = TRUE;
	const int lifeNum = 3;
	int playerLife = lifeNum;
	const int playerGHTime = 40;
	int playerGHTimer = 0;

	//�X�N���[��
	int back[2] = { 0, 12800 };
	int scroll = 0;
	//const int scrollX = 740;
	const int scrollEnd = 11520;

	int scene = 0;//�V�[��
	enum Scene { TITLE, SELECT, STAGE1, STAGE2, ENDLESS, OPTION, GAMECLEAR, GAMEOVER, SCORE };
	bool retry = false;//�Q�[���I�[�o�[��ʁA�G���h���X�X�R�A�p
	int old_scene = 0;
	int stage = 1;//�X�e�[�W�I��

	bool start = FALSE;

	int pause = 0;
	bool pauseFlag = FALSE;
	int sound = 0;
	int countdownSEFlag = false;

	//�I�u�W�F�N�g���
	enum Flag { OFF, ON, F_OFF };
	//�ŏ��͑S�ĉ�ʊO�ɒu���Ă���
	const int resetX = -500;
	const int resetY = 0;

	bool sirenFlag = false;

	//�G�@
	const int enemyNum = 3;
	const int enemyPositionX = 750;	//���@�ƓG�@�̋���
	const int enemyPositionY = 180;
	int enemyFlag[enemyNum] = {};
	struct Object enemyPlane[enemyNum];	//�~�T�C����łG
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

	//�~�T�C��
	const int missileNum = 9;
	int missileFlag[missileNum] = {};
	struct Object missile[missileNum];	//�~�T�C��
	for (int i = 0; i < missileNum; i++) {
		missile[i].sizeX = 128;
		missile[i].sizeY = 32;
		missile[i].x = player.x + enemyPositionX;
		missile[i].y = 0;
		missile[i].speed = 10;
	}
	const int missileTime = 30;
	int missileTimer = missileTime;	//�~�T�C�����˃^�C�}�[

	//����
	const int buildNum = 5;
	int smallBuildFlag[buildNum] = {};
	int bigBuildFlag[buildNum] = {};
	struct Object smallBuild[buildNum];	//����������
	struct Object bigBuild[buildNum];	//�傫������
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

	//��
	const int birdNum = 50;
	const int birdRange = 200;
	int slowBirdFlag[birdNum] = {};
	int fastBirdFlag[birdNum] = {};
	struct Object slowBird[birdNum];	//�x����
	struct Object fastBird[birdNum];	//������
	for (int i = 0; i < birdNum; i++) {	//�X�e�[�W1�̔z�u
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
	int slowBirdTimer = birdTimeEasy;	//�������ł��Ԋu
	int fastBirdTimer = birdTimeEasy;
	const int birdGHTime = 20;
	int birdGHTimer = 0;

	//�_�i�X�s�[�h�_�E���j
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


	//���i�X�s�[�h�A�b�v�j
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
	const int speedUpTime = 60;	//���x���オ�葱���鎞��
	int rainbowTimer = rainbowTime * 2;
	int speedUpTimer = speedUpTime;
	const int rainbowGHTime = 70;
	int rainbowGHTimer = 0;

	//���j
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

	//�J�E���g�_�E���^�C�}�[
	const int startTime = 200;
	int startTimer = startTime;

	//�����摜���p
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

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i) {
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//�����擾
		srand(time(nullptr));

		switch (scene) {

		case TITLE://�^�C�g�����
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

			/*DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�g�����", TRUE);
			DrawFormatString(0, 15, GetColor(255, 255, 255), "�X�y�[�X�Ői��", TRUE);*/
			break;

		case SELECT://�X�e�[�W�I�����

			//�I��
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
					scene = 2;//�X�e�[�W1
					StopSoundMem(titleBGM);
					PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
					//�ϐ����Z�b�g����
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
					scene = 3;//�X�e�[�W2
					StopSoundMem(titleBGM);
					PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
					//�ϐ����Z�b�g����
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
					scene = 4;//�G���h���X
					StopSoundMem(titleBGM);
					PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
					//�ϐ����Z�b�g����
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
					scene = 5;//�V�ѕ�
					PlaySoundMem(ketteiSE, DX_PLAYTYPE_NORMAL, TRUE);
				}
				break;
			}

			DrawGraph(0, 0, stageSelectGH[stage], true);


			//DrawFormatString(0, 0, GetColor(255, 255, 255), "�X�e�[�W�I�����\n���őI���Aspace�Ō���", TRUE);
			////DrawFormatString(0, 30, GetColor(255, 255, 255), "stage:%d", stage, TRUE);
			//if (stage == 1)DrawFormatString(0, 40, GetColor(255, 255, 255), "�X�e�[�W1", TRUE);
			//if (stage == 2)DrawFormatString(0, 40, GetColor(255, 255, 255), "�X�e�[�W2", TRUE);
			//if (stage == 3)DrawFormatString(0, 40, GetColor(255, 255, 255), "�G���h���X", TRUE);
			//if (stage == 4)DrawFormatString(0, 40, GetColor(255, 255, 255), "�V�ѕ�", TRUE);
			break;

		case STAGE1:	//�X�e�[�W1

			//�w�i�`��
			DrawGraph(0 - scroll, 0, haikei, true);

			//�^�C�}�[��0�ɂȂ�����X�^�[�g
			if (startTimer >= 0 && pauseFlag == false && start == false) {//�^�C�}�[��0�ȏ�̂Ƃ�

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
				//�`��
				//�v���C���[
				DrawGraph(player.x, player.y, playerGH3[0], true);

				//�J�E���g�_�E��
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
					//�����X�N���[��
					Scroll(player.x, playerSpeed, scroll, scrollEnd);

					//�㏸
					UP(keys, oldkeys, yadd, freezeFlag, upSE);

					//�d��
					Gravity(player.y, yadd, gravity);

					//��ɍs���߂���Ɠ���
					Freeze(player.y, topY, freezeFlag, freezeTimer, freezeySE);
				}

				//��
				//�ړ�����
				//�x���� �i�ނɂ�ē�Փx�A�b�v
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
						//��ʊO�ɏo���������
						if (OffScreen(slowBird[i].x + slowBird[i].sizeX, 0)) {
							slowBirdFlag[i] = OFF;
						}
						//�����蔻��
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, slowBird[i].x, slowBird[i].y, slowBird[i].sizeX, slowBird[i].sizeY)) {
							slowBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�ړ�
						ObjMoveMinus(slowBird[i].x, slowBird[i].speed);

						//�`��
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, slowBird[i].x, slowBird[i].y, birdGH[j]);
					}
				}

				//������ �i�ނɂ�ē�Փx�A�b�v
				if (scroll >= WIN_WIDTH * 2 && scroll < WIN_WIDTH * 5) {
					Timer(fastBirdTimer, birdTimeNormal);
				}
				else if (scroll >= WIN_WIDTH * 5) {
					Timer(fastBirdTimer, birdTimeHard);
				}
				for (int i = 0; i < birdNum; i++) {
					if (fastBirdTimer <= 0 && fastBirdFlag[i] == OFF) {
						fastBirdFlag[i] = ON;
						//���W�X�V
						fastBird[i].x = WIN_WIDTH;
						fastBird[i].y = (rand() * 150) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (fastBirdFlag[i] == ON) {
						//��ʊO�ɏo�邩�v���C���[�ɓ��������������
						if (OffScreen(fastBird[i].x + fastBird[i].sizeX, 0)) {
							fastBirdFlag[i] = OFF;
						}
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, fastBird[i].x, fastBird[i].y, fastBird[i].sizeX, fastBird[i].sizeY)) {
							fastBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�ړ�
						ObjMoveMinus(fastBird[i].x, fastBird[i].speed);

						//�`��
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, fastBird[i].x, fastBird[i].y, birdGH[j]);
					}
				}

				//�����̏���
				for (int i = 0; i < buildNum; i++) {
					if (scroll > WIN_WIDTH * 5 && smallBuildFlag[i] == OFF) {
						smallBuildFlag[i] = ON;
						//���W�ݒ�
						smallBuild[i].x = WIN_WIDTH * (i + 1);
						smallBuild[i].y = WIN_HEIGHT - smallBuild[i].sizeY;
					}
					if (smallBuildFlag[i] == ON) {
						//�v���C���[�ɓ���������hp -3
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, smallBuild[i].x, smallBuild[i].y, smallBuild[i].sizeX, smallBuild[i].sizeY)) {
							playerLife -= 3;
						}

						//��ʊO�ɏo���������
						if (OffScreen(smallBuild[i].x + smallBuild[i].sizeX, 0)) {
							smallBuildFlag[i] = F_OFF;
						}

						//�ړ�
						ObjMoveMinus(smallBuild[i].x, smallBuild[i].speed);

						//�`��
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
					}
				}

				//�_�̏���
				for (int i = 0; i < gimmickNum; i++) {
					//�^�C�}�[
					Timer(cloudTimer, cloudTime);
					if (cloudTimer <= 0 && cloudFlag[i] == OFF) {
						cloudFlag[i] = ON;
						//���W�X�V
						cloud[i].x = WIN_WIDTH;
						cloud[i].y = (rand() * 200) % (WIN_HEIGHT - cloudRange);
					}
					if (cloudFlag[i] == ON) {
						//��ʊO�ɏo���������
						if (OffScreen(cloud[i].x + cloud[i].sizeX, 0)) {
							cloudFlag[i] = OFF;
						}

						//������Ƒ��xdowm
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, cloud[i].x, cloud[i].y, cloud[i].sizeX, cloud[i].sizeY)) {
							cloudFlag[i] = F_OFF;
							PlaySoundMem(kumoHitSE, DX_PLAYTYPE_BACK, TRUE);
						}
					}

					//�ړ�
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
					//�`��
					DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);

				}

				//���̏���
				for (int i = 0; i < gimmickNum; i++) {
					Timer(rainbowTimer, rainbowTime);
					if (rainbowTimer <= 0 && rainbowFlag[i] == OFF) {
						rainbowFlag[i] = ON;
						//���W�X�V
						rainbow[i].x = WIN_WIDTH;
						rainbow[i].y = (rand() * 300) % (WIN_HEIGHT - rainbowRange);
					}
					if (rainbowFlag[i] == ON) {
						//��ʊO�ɏo���������
						if (OffScreen(rainbow[i].x + rainbow[i].sizeX, 0)) {
							rainbowFlag[i] = OFF;
						}

						//�ړ�
						ObjMoveMinus(rainbow[i].x, rainbow[i].speed);

						//���������瑬�xup
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, rainbow[i].x, rainbow[i].y, rainbow[i].sizeX, rainbow[i].sizeY)) {
							rainbowFlag[i] = F_OFF;
							PlaySoundMem(nijiHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�`��
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

				//�N���A
				if (player.x + scroll >= 12800) {
					scene = GAMECLEAR;
					StopSoundMem(stage1BGM);
				}

				//��ʊO�ɗ����ŃQ�[���I�[�o�[
				if (player.y >= WIN_HEIGHT) {
					isPlayerAlive = false;
					StopSoundMem(stage1BGM);
					if (CheckSoundMem(playerbakuhatuSE) == 0) {
						PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}

				//�v���C���[�����Ă�Ƃ��̓v���C���[�`��
				if (isPlayerAlive == true) {
					//�v���C���[�����Ă�Ƃ��͓����Ă�摜��`��
					if (freezeFlag == true) {
						DrawGraph(player.x, player.y, playerColdGH, true);
					}
					//�����ĂȂ��Ƃ�
					if (freezeFlag == false) {
						//�v���C���[ hp���ɂ���ĕω�
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

			//���C�t�������Ȃ����甚�����ĉ�ʐ؂�ւ�
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

			//�|�[�Y�����`��
			if (pauseFlag == true || isPlayerAlive == false) {

				//�v���C���[
				if (isPlayerAlive == true) {
					DrawGraph(player.x, player.y, playerGH3[0], true);
				}

				//��
				for (int i = 0; i < birdNum; i++) {
					if (slowBirdFlag[i] == ON || fastBirdFlag[i] == ON) {
						DrawGraph(slowBird[i].x, slowBird[i].y, birdGH[0], true);
						DrawGraph(fastBird[i].x, fastBird[i].y, birdGH[0], true);
					}
				}

				//����
				for (int i = 0; i < buildNum; i++) {
					if (smallBuildFlag[i] == ON || bigBuildFlag[i] == ON) {
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
						DrawGraph(bigBuild[i].x, bigBuild[i].y, smallBuildGH, true);
					}
				}

				//�M�~�b�N
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
			//�|�[�Y
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, sound);


			/*DrawFormatString(0, 0, GetColor(255, 255, 255), "cloud[0].x:%d", cloud[0].x);
			DrawFormatString(0, 15, GetColor(255, 255, 255), "cloudTimer:%d", cloudTimer);*/

			break;

		case STAGE2:
			//BGM
			//�w�i�`��
			DrawGraph(0 - scroll, 0, haikei, true);

			//�^�C�}�[��0�ɂȂ�����X�^�[�g
			if (startTimer >= 0 && pauseFlag == false && start == false) {//�^�C�}�[��0�ȏ�̂Ƃ�
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

				//�`��
				//�v���C���[
				DrawGraph(player.x, player.y, playerGH3[0], true);

				//�J�E���g�_�E��
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
					//�����X�N���[��
					Scroll(player.x, playerSpeed, scroll, scrollEnd);

					//�㏸
					UP(keys, oldkeys, yadd, freezeFlag, upSE);

					//�d��
					Gravity(player.y, yadd, gravity);

					//��ɍs���߂���Ɠ���
					Freeze(player.y, topY, freezeFlag, freezeTimer, freezeySE);
				}

				//���̏���
				//�x���� �i�ނɂ�ē�Փx�A�b�v
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
						//���W�X�V
						slowBird[i].x = WIN_WIDTH;
						slowBird[i].y = (rand() * 100) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (slowBirdFlag[i] == ON) {
						//��ʊO�ɏo���������
						if (OffScreen(slowBird[i].x + slowBird[i].sizeX, 0)) {
							slowBirdFlag[i] = OFF;
						}
						//�����蔻��
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, slowBird[i].x, slowBird[i].y, slowBird[i].sizeX, slowBird[i].sizeY)) {
							slowBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�ړ�
						ObjMoveMinus(slowBird[i].x, slowBird[i].speed);

						//�`��
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, slowBird[i].x, slowBird[i].y, birdGH[j]);
					}
				}

				//������ �i�ނɂ�ē�Փx�A�b�v
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
						//���W�X�V
						fastBird[i].x = WIN_WIDTH;
						fastBird[i].y = (rand() * 150) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (fastBirdFlag[i] == ON) {
						//��ʊO�ɏo�邩�v���C���[�ɓ��������������
						if (OffScreen(fastBird[i].x + fastBird[i].sizeX, 0)) {
							fastBirdFlag[i] = OFF;
						}
						//�����蔻��
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, fastBird[i].x, fastBird[i].y, fastBird[i].sizeX, fastBird[i].sizeY)) {
							fastBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�ړ�
						ObjMoveMinus(fastBird[i].x, fastBird[i].speed);

						//�`��
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, fastBird[i].x, fastBird[i].y, birdGH[j]);
					}
				}

				//�����̏���
				for (int i = 0; i < buildNum; i++) {
					if (scroll > WIN_WIDTH * 6 && bigBuildFlag[i] == OFF) {
						bigBuildFlag[i] = ON;
						//���W�ݒ�
						bigBuild[i].x = WIN_WIDTH * (i + 1);
						bigBuild[i].y = WIN_HEIGHT - bigBuild[i].sizeY;
					}
					if (bigBuildFlag[i] == ON) {
						//�v���C���[�ɓ���������hp -3
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, bigBuild[i].x, bigBuild[i].y, bigBuild[i].sizeX, bigBuild[i].sizeY)) {
							playerLife -= 3;
						}

						//��ʊO�ɏo���������
						if (OffScreen(bigBuild[i].x + bigBuild[i].sizeX, 0)) {
							bigBuildFlag[i] = F_OFF;
						}

						//�ړ�
						ObjMoveMinus(bigBuild[i].x, bigBuild[i].speed);

						//�`��
						DrawGraph(bigBuild[i].x, bigBuild[i].y, bigBuildGH, true);
					}
				}

				//�_�̏���
				for (int i = 0; i < gimmickNum; i++) {
					//�^�C�}�[
					Timer(cloudTimer, cloudTime);
					if (cloudTimer <= 0 && cloudFlag[i] == OFF) {
						cloudFlag[i] = ON;
						//���W�X�V
						cloud[i].x = WIN_WIDTH;
						cloud[i].y = (rand() * 200) % (WIN_HEIGHT - cloudRange);
					}
					if (cloudFlag[i] == ON) {
						//��ʊO�ɏo���������
						if (OffScreen(cloud[i].x + cloud[i].sizeX, 0)) {
							cloudFlag[i] = OFF;
						}

						//������Ƒ��xdowm
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, cloud[i].x, cloud[i].y, cloud[i].sizeX, cloud[i].sizeY)) {
							cloudFlag[i] = F_OFF;
							PlaySoundMem(kumoHitSE, DX_PLAYTYPE_BACK, TRUE);
						}
					}

					//�ړ�
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
					//�`��
					DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);

				}

				//���̏���
				for (int i = 0; i < gimmickNum; i++) {
					Timer(rainbowTimer, rainbowTime);
					if (rainbowTimer <= 0 && rainbowFlag[i] == OFF) {
						rainbowFlag[i] = ON;
						//���W�X�V
						rainbow[i].x = WIN_WIDTH;
						rainbow[i].y = (rand() * 300) % (WIN_HEIGHT - rainbowRange);
					}
					if (rainbowFlag[i] == ON) {
						//��ʊO�ɏo���������
						if (OffScreen(rainbow[i].x + rainbow[i].sizeX, 0)) {
							rainbowFlag[i] = OFF;
						}

						//�ړ�
						ObjMoveMinus(rainbow[i].x, rainbow[i].speed);

						//���������瑬�xup
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, rainbow[i].x, rainbow[i].y, rainbow[i].sizeX, rainbow[i].sizeY)) {
							rainbowFlag[i] = F_OFF;
							PlaySoundMem(nijiHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�`��
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

				//�~�T�C���̏���
				//�ʒu�ɂ�����^�C�}�[�n��
				if (enemyPlane[2].y >= enemyPositionY * 3) {
					Timer(missileTimer, missileTime);
				}
				for (int i = 0; i < missileNum; i++) {
					//�^�C�}�[��0�ɂȂ�����~�T�C������
					if (missileTimer <= 0 && missileFlag[i] == OFF) {
						missileFlag[i] = ON;
						PlaySoundMem(missileShotSE, DX_PLAYTYPE_BACK, TRUE);
						//�~�T�C�����W�X�V
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

					//�~�T�C�������ֈړ�
					if (missileFlag[i] == ON) {
						//���������烉�C�t������
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, missile[i].x, missile[i].y, missile[i].sizeX, missile[i].sizeY)) {
							missileFlag[i] = OFF;
						}
						if (missileFlag[i] == OFF) {
							playerLife -= 2;
							missileFlag[i] = F_OFF;
							PlaySoundMem(missileHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//��ʊO�ɏo���������
						if (OffScreen(missile[i].x + missile[i].sizeX, 0)) {
							missileFlag[i] = F_OFF;
						}

						//�ړ�
						ObjMoveMinus(missile[i].x, missile[i].speed);

						//�`��
						DrawGraph(missile[i].x, missile[i].y, missileGH, true);
					}
				}


				//�G�@�̓o�ꏈ��
				for (int i = 0; i < enemyNum; i++) {
					if (isEnemyFlag == true) {
						enemyFlag[i] = ON;

					}
					//�~�T�C�����ˈʒu�ɂ�����~�܂�
					if (enemyFlag[i] == ON && enemyPlane[i].y >= enemyPositionY * (i + 1)) {
						enemyPlane[i].y = enemyPositionY * (i + 1);
					}
					//���̏ꏊ�܂ōs���Ɠo��
					else if (enemyFlag[i] == ON && missile[8].x > 0) {
						ObjMovePlus(enemyPlane[i].y, enemyPlane[i].speed);
					}
					//�~�T�C����ł��؂�����t�F�[�h�A�E�g
					if (enemyFlag[i] == ON && missile[8].x < 0) {
						enemyFlag[i] = OFF;
					}
					if (enemyFlag[i] == OFF && enemyPlane[i].y > -enemyPlane[i].sizeY) {
						ObjMoveMinus(enemyPlane[i].y, enemyPlane[i].speed);
					}

					//	�`��
					int j = enemyGHTimer / (enemyGHTime / enemyGHNum);
					AniGH(enemyGHTimer, enemyGHTime, enemyPlane[i].x, enemyPlane[i].y, enemyGH[j]);
				}

				//�^�C�}�[��0�ɂȂ������s�@���łĂ���
				if (enemyTimer >= 0 && isEnemyFlag == false) {
					enemyTimer--;
					if (enemyTimer == 0) {
						isEnemyFlag = true;
						enemyTimer = enemyTime2;
						PlaySoundMem(sirenSE, DX_PLAYTYPE_BACK, true);
					}
				}

				//�N���A
				if (player.x + scroll >= 12800) {
					scene = GAMECLEAR;
					StopSoundMem(stage2BGM);
				}

				//��ʊO�ɗ����ŃQ�[���I�[�o�[
				if (player.y >= WIN_HEIGHT) {
					isPlayerAlive = false;
					StopSoundMem(stage2BGM);
					if (CheckSoundMem(playerbakuhatuSE) == 0) {
						PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}

				//�v���C���[�����Ă�Ƃ��̓v���C���[�`��
				if (isPlayerAlive == true) {
					//�v���C���[�����Ă�Ƃ��͓����Ă�摜��`��
					if (freezeFlag == true) {
						DrawGraph(player.x, player.y, playerColdGH, true);
					}
					//�����ĂȂ��Ƃ�
					if (freezeFlag == false) {
						//�v���C���[ hp���ɂ���ĕω�
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
				//���C�t�������Ȃ����甚�����ĉ�ʐ؂�ւ�
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


			//�|�[�Y�����`��
			if (pauseFlag == true || isPlayerAlive == false) {

				//�v���C���[
				if (isPlayerAlive == true) {
					DrawGraph(player.x, player.y, playerGH3[0], true);
				}
				//��
				for (int i = 0; i < birdNum; i++) {
					if (slowBirdFlag[i] == ON || fastBirdFlag[i] == ON) {
						DrawGraph(slowBird[i].x, slowBird[i].y, birdGH[0], true);
						DrawGraph(fastBird[i].x, fastBird[i].y, birdGH[0], true);
					}
				}

				//����
				for (int i = 0; i < buildNum; i++) {
					if (smallBuildFlag[i] == ON || bigBuildFlag[i] == ON) {
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
						DrawGraph(bigBuild[i].x, bigBuild[i].y, bigBuildGH, true);
					}
				}

				//�~�T�C��
				for (int i = 0; i < missileNum; i++) {
					if (missileFlag[i] == ON) {
						DrawGraph(missile[i].x, missile[i].y, missileGH, true);
					}
				}

				//�G�@
				for (int i = 0; i < enemyNum; i++) {
					if (enemyFlag[i] == ON) {
						DrawGraph(enemyPlane[i].x, enemyPlane[i].y, enemyGH[0], true);
					}
				}

				//�M�~�b�N
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
			//�|�[�Y
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, sound);

			//�m�F
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "TIMER:%d", TIMER);
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "cloudTimer:%d", cloudTimer);

			break;

		case ENDLESS:
			//�w�i�`��
			DrawGraph(back[0] - scroll, 0, haikei, true);
			DrawGraph(back[1] - scroll, 0, haikei, true);

			//�z��Ɋi�[
			score = scroll / 50;
			sprintf_s(strNum, sizeof(strNum), "%d", score);

			//�I�t�Z�b�g�l�ɍ��킹��
			for (int i = 0; i < digits; i++) {
				eachNum[i] = strNum[i] - 48;
			}

			//�^�C�}�[��0�ɂȂ�����X�^�[�g
			if (startTimer > 0 && pauseFlag == false && start == false) {//�^�C�}�[��0�ȏ�̂Ƃ�
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
				//�`��
				//�v���C���[
				DrawGraph(player.x, player.y, playerGH3[0], true);

				//�J�E���g�_�E��
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
					//�����X�N���[��
					scroll += playerSpeed;
					for (int i = 0; i < 2; i++) {
						if (back[i] - scroll <= -WIN_WIDTH * 10) {
							back[i] = WIN_WIDTH * 10 + scroll;
						}
					}

					//�㏸
					UP(keys, oldkeys, yadd, freezeFlag, upSE);


					//�d��
					Gravity(player.y, yadd, gravity);

					//��ɍs���߂���Ɠ���
					Freeze(player.y, topY, freezeFlag, freezeTimer, freezeySE);
				}

				//��
				//�ړ�����
				//�x���� �i�ނɂ�ē�Փx�A�b�v
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
						//��ʊO�ɏo���������
						if (OffScreen(slowBird[i].x + slowBird[i].sizeX, 0)) {
							slowBirdFlag[i] = OFF;
						}
						//�����蔻��
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, slowBird[i].x, slowBird[i].y, slowBird[i].sizeX, slowBird[i].sizeY)) {
							slowBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�ړ�
						ObjMoveMinus(slowBird[i].x, slowBird[i].speed);

						//�`��
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, slowBird[i].x, slowBird[i].y, birdGH[j]);
					}
				}

				//������ �i�ނɂ�ē�Փx�A�b�v
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
						//���W�X�V
						fastBird[i].x = WIN_WIDTH;
						fastBird[i].y = (rand() * 150) % (WIN_HEIGHT - birdRange);
						break;
					}
					if (fastBirdFlag[i] == ON) {
						//��ʊO�ɏo�邩�v���C���[�ɓ��������������
						if (OffScreen(fastBird[i].x + fastBird[i].sizeX, 0)) {
							fastBirdFlag[i] = OFF;
						}
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, fastBird[i].x, fastBird[i].y, fastBird[i].sizeX, fastBird[i].sizeY)) {
							fastBirdFlag[i] = OFF;
							playerLife--;
							PlaySoundMem(toriHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�ړ�
						ObjMoveMinus(fastBird[i].x, fastBird[i].speed);

						//�`��
						int j = birdGHTimer / (birdGHTime / birdGHNum);
						AniGH(birdGHTimer, birdGHTime, fastBird[i].x, fastBird[i].y, birdGH[j]);
					}
				}



				//�_�̏���
				for (int i = 0; i < gimmickNum; i++) {
					//�^�C�}�[
					Timer(cloudTimer, cloudTime);
					if (cloudTimer <= 0 && cloudFlag[i] == OFF) {
						cloudFlag[i] = ON;
						//���W�X�V
						cloud[i].x = WIN_WIDTH;
						cloud[i].y = (rand() * 200) % (WIN_HEIGHT - cloudRange);
					}
					if (cloudFlag[i] == ON) {
						//��ʊO�ɏo���������
						if (OffScreen(cloud[i].x + cloud[i].sizeX, 0)) {
							cloudFlag[i] = OFF;
						}

						//������Ƒ��xdowm
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, cloud[i].x, cloud[i].y, cloud[i].sizeX, cloud[i].sizeY)) {
							cloudFlag[i] = F_OFF;
							PlaySoundMem(kumoHitSE, DX_PLAYTYPE_BACK, TRUE);
						}
					}

					//�ړ�
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
					//�`��
					DrawGraph(cloud[i].x, cloud[i].y, cloudGH, true);

				}

				//���̏���
				for (int i = 0; i < gimmickNum; i++) {
					Timer(rainbowTimer, rainbowTime);
					if (rainbowTimer <= 0 && rainbowFlag[i] == OFF) {
						rainbowFlag[i] = ON;
						//���W�X�V
						rainbow[i].x = WIN_WIDTH;
						rainbow[i].y = (rand() * 300) % (WIN_HEIGHT - rainbowRange);
					}
					if (rainbowFlag[i] == ON) {
						//��ʊO�ɏo���������
						if (OffScreen(rainbow[i].x + rainbow[i].sizeX, 0)) {
							rainbowFlag[i] = OFF;
						}

						//�ړ�
						ObjMoveMinus(rainbow[i].x, rainbow[i].speed);

						//���������瑬�xup
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, rainbow[i].x, rainbow[i].y, rainbow[i].sizeX, rainbow[i].sizeY)) {
							rainbowFlag[i] = F_OFF;
							PlaySoundMem(nijiHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//�`��
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
				//�����̏���
				//������
				for (int i = 0; i < buildNum; i++) {
					Timer(smallBuildTimer, smallBuildTime);
					if (smallBuildTimer <= 0 && smallBuildFlag[i] == OFF) {
						smallBuildFlag[i] = ON;
						//���W�ݒ�
						smallBuild[i].x = WIN_WIDTH + 100;
						smallBuild[i].y = WIN_HEIGHT - smallBuild[i].sizeY;
						break;
					}
					if (smallBuildFlag[i] == ON) {
						//�v���C���[�ɓ���������hp -3
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, smallBuild[i].x, smallBuild[i].y, smallBuild[i].sizeX, smallBuild[i].sizeY)) {
							playerLife -= 3;
						}

						//��ʊO�ɏo���������
						if (OffScreen(smallBuild[i].x + smallBuild[i].sizeX, 0)) {
							smallBuildFlag[i] = OFF;
						}

						//�ړ�
						ObjMoveMinus(smallBuild[i].x, smallBuild[i].speed);

						//�`��
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
					}
				}

				//�傫��
				for (int i = 0; i < buildNum; i++) {
					Timer(bigBuildTimer, bigBuildTime);
					if (bigBuildTimer <= 0 && bigBuildFlag[i] == OFF) {
						bigBuildFlag[i] = ON;
						//���W�ݒ�
						bigBuild[i].x = WIN_WIDTH + 800;
						bigBuild[i].y = WIN_HEIGHT - bigBuild[i].sizeY;
						break;
					}
					if (bigBuildFlag[i] == ON) {
						//�v���C���[�ɓ���������hp -3
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, bigBuild[i].x, bigBuild[i].y, bigBuild[i].sizeX, bigBuild[i].sizeY)) {
							playerLife -= 3;
						}

						//��ʊO�ɏo���������
						if (OffScreen(bigBuild[i].x + bigBuild[i].sizeX, 0)) {
							bigBuildFlag[i] = OFF;
						}

						//�ړ�
						ObjMoveMinus(bigBuild[i].x, bigBuild[i].speed);

						//�`��
						DrawGraph(bigBuild[i].x, bigBuild[i].y, bigBuildGH, true);
					}
				}

				//�~�T�C���̏���
				//�ʒu�ɂ�����^�C�}�[�n��
				if (enemyPlane[2].y >= enemyPositionY * 3) {
					Timer(missileTimer, missileTime);
				}
				for (int i = 0; i < missileNum; i++) {
					//�^�C�}�[��0�ɂȂ�����~�T�C������
					if (missileTimer <= 0 && missileFlag[i] == OFF) {
						missileFlag[i] = ON;
						PlaySoundMem(missileShotSE, DX_PLAYTYPE_BACK, TRUE);
						//�~�T�C�����W�X�V
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

					//�~�T�C�������ֈړ�
					if (missileFlag[i] == ON) {
						//���������烉�C�t������
						if (ObjCollision(player.x, player.y, player.sizeX, player.sizeY, missile[i].x, missile[i].y, missile[i].sizeX, missile[i].sizeY)) {
							missileFlag[i] = OFF;
						}
						if (missileFlag[i] == OFF) {
							playerLife -= 2;
							missileFlag[i] = F_OFF;
							PlaySoundMem(missileHitSE, DX_PLAYTYPE_BACK, TRUE);
						}

						//��ʊO�ɏo���������
						if (OffScreen(missile[i].x + missile[i].sizeX, 0)) {
							missileFlag[i] = F_OFF;
						}

						//�ړ�
						ObjMoveMinus(missile[i].x, missile[i].speed);

						//�`��
						DrawGraph(missile[i].x, missile[i].y, missileGH, true);
					}
				}

				//�G�@�̓o�ꏈ��
				for (int i = 0; i < enemyNum; i++) {
					if (isEnemyFlag == true) {
						enemyFlag[i] = ON;
					}
					//�~�T�C�����ˈʒu�ɂ�����~�܂�
					if (enemyFlag[i] == ON && enemyPlane[i].y >= enemyPositionY * (i + 1)) {
						enemyPlane[i].y = enemyPositionY * (i + 1);
					}
					//���̏ꏊ�܂ōs���Ɠo��
					else if (enemyFlag[i] == ON && missile[8].x > 0) {
						ObjMovePlus(enemyPlane[i].y, enemyPlane[i].speed);
					}
					//�~�T�C����ł��؂�����t�F�[�h�A�E�g
					if (enemyFlag[i] == ON && missile[8].x < 0) {
						enemyFlag[i] = OFF;
						isEnemyFlag = false;
					}
					if (enemyFlag[i] == OFF && enemyPlane[i].y > -enemyPlane[i].sizeY) {
						ObjMoveMinus(enemyPlane[i].y, enemyPlane[i].speed);
					}

					//	�`��
					int j = enemyGHTimer / (enemyGHTime / enemyGHNum);
					AniGH(enemyGHTimer, enemyGHTime, enemyPlane[i].x, enemyPlane[i].y, enemyGH[j]);
				}

				//�^�C�}�[��0�ɂȂ������s�@���łĂ���
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

				//��ʊO�ɗ����ŃQ�[���I�[�o�[
				if (player.y >= WIN_HEIGHT) {
					isPlayerAlive = false;
					StopSoundMem(endlessBGM);
					if (CheckSoundMem(playerbakuhatuSE) == 0) {
						PlaySoundMem(playerbakuhatuSE, DX_PLAYTYPE_BACK, TRUE);
					}
				}

				//�v���C���[�����Ă�Ƃ��̓v���C���[�`��
				if (isPlayerAlive == true) {
					//�v���C���[�����Ă�Ƃ��͓����Ă�摜��`��
					if (freezeFlag == true) {
						DrawGraph(player.x, player.y, playerColdGH, true);
					}
					//�����ĂȂ��Ƃ�
					if (freezeFlag == false) {
						//�v���C���[ hp���ɂ���ĕω�
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

				//���C�t�������Ȃ����甚�����ĉ�ʐ؂�ւ�
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

			//�|�[�Y�����`��
			if (pauseFlag == true || isPlayerAlive == false) {

				//�v���C���[
				if (isPlayerAlive == true) {
					DrawGraph(player.x, player.y, playerGH3[0], true);
				}

				//��
				for (int i = 0; i < birdNum; i++) {
					if (slowBirdFlag[i] == ON || fastBirdFlag[i] == ON) {
						DrawGraph(slowBird[i].x, slowBird[i].y, birdGH[0], true);
						DrawGraph(fastBird[i].x, fastBird[i].y, birdGH[0], true);
					}
				}

				//����
				for (int i = 0; i < buildNum; i++) {
					if (smallBuildFlag[i] == ON || bigBuildFlag[i] == ON) {
						DrawGraph(smallBuild[i].x, smallBuild[i].y, smallBuildGH, true);
						DrawGraph(bigBuild[i].x, bigBuild[i].y, bigBuildGH, true);
					}
				}

				//�~�T�C��
				for (int i = 0; i < missileNum; i++) {
					if (missileFlag[i] == ON) {
						DrawGraph(missile[i].x, missile[i].y, missileGH, true);
					}
				}

				//�G�@
				for (int i = 0; i < enemyNum; i++) {
					if (enemyFlag[i] == ON) {
						DrawGraph(enemyPlane[i].x, enemyPlane[i].y, enemyGH[0], true);
					}
				}

				//�M�~�b�N
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

			//����
			for (int i = 0; i < digits; i++) {
				DrawGraph(48 * i + 32, 16, numberGH[eachNum[i]], true);
			}

			if (start == true) {
				sound = endlessBGM;
			}
			else if (start == false) {
				sound = countdownSE;
			}
			//�|�[�Y
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, sound);;

			//DrawFormatString(0, 0, GetColor(255, 255, 255), "score:%d", true);
			//�m�F
			/*DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", playerSpeed);
			DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", enemyTimer);
			DrawFormatString(0, 150, GetColor(255, 255, 255), "%d", isEnemyFlag);
			DrawFormatString(0, 150, GetColor(255, 255, 255), "score:%d", score, true);
			DrawFormatString(0, 165, GetColor(255, 255, 255), "scroll:%d", scroll, true);*/

			break;

		case OPTION://������@
			DrawGraph(0, 0, optionGH, true);
			if (keys[KEY_INPUT_ESCAPE] == 1 && oldkeys[KEY_INPUT_ESCAPE] == 0) {
				scene = 1;
				PlaySoundMem(cancelSE, DX_PLAYTYPE_BACK, TRUE);
			}
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "�V�ѕ�\nESC�ŃX�e�[�W�I���ɖ߂�", TRUE);
			break;

		case GAMECLEAR://�Q�[���N���A
			if (CheckSoundMem(gameclearBGM) == 0) {
				PlaySoundMem(gameclearBGM, DX_PLAYTYPE_LOOP, TRUE);
			}

			DrawGraph(0, 0, gameClearGH, true);
			//�|�[�Y
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, bgm_null);

			//DrawFormatString(0, 0, GetColor(255, 255, 255), "�N���A���\n�X�y�[�X�Ń^�C�g���ɖ߂�", TRUE);
			break;

		case GAMEOVER://�Q�[���I�[�o�[
			if (CheckSoundMem(gameoverBGM) == 0) {
				PlaySoundMem(gameoverBGM, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, gameOverGH, true);
			//�|�[�Y
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, bgm_null);

			//DrawFormatString(0, 0, GetColor(255, 255, 255), "�Q�[���I�[�o�[���\n�X�y�[�X�Ń^�C�g���ɖ߂�", TRUE);
			break;

		case SCORE://�G���h���X���[�h�X�R�A
			StopSoundMem(endlessBGM);
			if (CheckSoundMem(gameclearBGM) == 0) {
				PlaySoundMem(gameclearBGM, DX_PLAYTYPE_LOOP, TRUE);
			}
			DrawGraph(0, 0, scoreGH, true);
			//����
			for (int i = 0; i < digits; i++) {
				DrawGraph(48 * i + 700, 230, numberGH[eachNum[i]], true);
			}
			Pause(keys, pause, pauseFlag, start, scene, pauseYesGH, pauseNoGH, pauseSE, cursorSE, ketteiSE, cancelSE, bgm_null);

			//�X�R�A���Z�[�u������
			// ---------- �t�@�C���ǂݍ���(read) ----------
			error = fopen_s(&rfp, "resource/save.txt", "r");

			int digitCount = 0;// ���s�ǂݍ��񂾂�
			while (fgets(data, 100, rfp) != NULL)
			{
				int tmp = atoi(data);// ascii to int
				arr[digitCount] = tmp;
				digitCount++;
			}

			fclose(rfp);// ����
			// ---------- �X�R�A���X�V ----------
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
			// ---------- �t�@�C���ɍX�V�����l����������(write) ----------
			error = fopen_s(&wfp, "resource/save.txt", "w");

			// �t�@�C���ɏ�������
			for (int i = 0; i < 3; ++i)
			{
				fprintf(wfp, "%d\n", arr[i]);
			}

			fclose(wfp);// ����

			//�X�R�A�����L���O�`��
			sprintf_s(strNumSave1, sizeof(strNumSave1), "%d", arr[0]);
			sprintf_s(strNumSave2, sizeof(strNumSave2), "%d", arr[1]);
			sprintf_s(strNumSave3, sizeof(strNumSave3), "%d", arr[2]);

			//�I�t�Z�b�g�l�ɍ��킹��
			for (int i = 0; i < digits; i++) {
				eachNumSave1[i] = strNumSave1[i] - 48;
				eachNumSave2[i] = strNumSave2[i] - 48;
				eachNumSave3[i] = strNumSave3[i] - 48;
			}

			//����
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


		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (keys[KEY_INPUT_TAB] == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}