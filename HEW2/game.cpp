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
#include "map.h"


void InitGame() 
{
	InitPlayer();
	InitGameOperation();
	InitMap();
	LoadTexture();
}

void UpdateGame() 
{

	UpdateMap();
	UpdateGameOperation();
	UpdatePlayer();

}

void DrawGame() 
{
	DrawMap();
	DrawPlayer();
}

void UninitGame()
{
	UninitGameOperation();
	UninitPlayer();
	UninitMap();
}

