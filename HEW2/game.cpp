//�Q�[���{��
// �e�X�g�R�����g
// �e�X�g�Q

//�����[�g�E�}�X�^�[����u�����`�����Ēǉ�
#include "config.h"
#include "texture.h"
#include "sprite.h"
#include "debugFont.h"
#include "player.h"
#include "game.h"


void InitGame() {
	InitPlayer();
	LoadTexture();
}

void UpdateGame() {

	UpdatePlayer();

}

void DrawGame() {
	DrawPlayer();
}

void UninitGame() {
	UninitPlayer();
}

