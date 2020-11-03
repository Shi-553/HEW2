//�Q�[���{��
// �e�X�g�R�����g
// �e�X�g�Q

//�����[�g�E�}�X�^�[����u�����`�����Ēǉ�
#include "config.h"
#include "texture.h"
#include "sprite.h"
#include "debugFont.h"
#include "player.h"
#include "GameOperation.h"
#include "game.h"
#include "Input.h"


void InitGame() {
	InitPlayer();
	InitInput();
	InitGameOperation();
	LoadTexture();
}

void UpdateGame() {

	UpdateGameOperation();
	UpdatePlayer();
	UninitInput();

}

void DrawGame() {
	DrawPlayer();
	DrawInput();
}

void UninitGame() {
	UninitGameOperation();
	UninitInput();
	UninitPlayer();
}

