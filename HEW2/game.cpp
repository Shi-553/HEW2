//�Q�[���{��
// �e�X�g�R�����g
// �e�X�g�Q

//�����[�g�E�}�X�^�[����u�����`�����Ēǉ�
#include "config.h"
#include "texture.h"
#include "sprite.h"
#include "debugFont.h"
#include "player.h"
#include "npc.h"
#include "GameOperation.h"
#include "game.h"


void InitGame() {
	InitPlayer();
	InitGameOperation();
	LoadTexture();
	InitNPC();
}

void UpdateGame() {

	UpdateGameOperation();
	UpdatePlayer();
	UpdateNPC();
}

void DrawGame() {
	DrawPlayer();
	DrawNPC();
}

void UninitGame() {
	UninitGameOperation();
	UninitPlayer();
	UninitNPC();
}

