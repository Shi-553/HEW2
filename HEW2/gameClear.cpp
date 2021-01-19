﻿#include "texture.h"
#include "config.h"
#include "sprite.h"
#include "InputLogger.h"
#include "sceneManager.h"
#include "selectButton.h"


#define GAME_CLEAR_BUTTON_WIDTH 330
#define GAME_CLEAR_BUTTON_HEIGHT 90

#define GAME_CLEAR_LOGO_WIDTH 1024
#define GAME_CLEAR_LOGO_HEIGHT 256

static int frame = 0;

static int backgroundTexture;
static int gameClearTexture;

void InitGameClear()
{
	InitSelectButton();

 Button returnTitleButton, retryButton;


	auto buttonCenter = D3DXVECTOR2(SCREEN_WIDTH / 2 - GAME_CLEAR_BUTTON_WIDTH / 2, (SCREEN_HEIGHT / 2 - GAME_CLEAR_BUTTON_HEIGHT / 2) + 40);

	returnTitleButton.pos = buttonCenter;
	returnTitleButton.size = D3DXVECTOR2(GAME_CLEAR_BUTTON_WIDTH, GAME_CLEAR_BUTTON_HEIGHT);
	returnTitleButton.textureId = ReserveTextureLoadFile("texture/quit.png");
	returnTitleButton.pressedTextureId = ReserveTextureLoadFile("texture/quit_pressed.png");

	returnTitleButton.releasedCallback = []() {
		GoNextScene(GameStartScene);
	};

	retryButton.pos = buttonCenter + D3DXVECTOR2(0, GAME_CLEAR_BUTTON_HEIGHT + 32);
	retryButton.size = D3DXVECTOR2(GAME_CLEAR_BUTTON_WIDTH, GAME_CLEAR_BUTTON_HEIGHT);
	retryButton.textureId = ReserveTextureLoadFile("texture/retry.png");
	retryButton.pressedTextureId = ReserveTextureLoadFile("texture/retry_pressed.png");


	retryButton.releasedCallback = []() {
		GoNextScene(GameScene);
	};

	AddSelectButton(returnTitleButton);
	AddSelectButton(retryButton);

	backgroundTexture = ReserveTextureLoadFile("texture/background/背景１.png");
	gameClearTexture = ReserveTextureLoadFile("texture/stageclear_1024×256.png");

	SetSelectButtonFrame(ReserveTextureLoadFile("texture/select.png"));

	LoadTexture();

	frame = 0;
}

void UninitGameClear()
{
	UninitSelectButton();

	ReleaseTexture(backgroundTexture);
	ReleaseTexture(gameClearTexture);
}

void DrawGameClear()
{
	DrawSprite(backgroundTexture, { 0,0 }, 10, { SCREEN_WIDTH,SCREEN_HEIGHT }, { 0,0 }, { SCREEN_WIDTH,SCREEN_HEIGHT });

		auto tPos = D3DXVECTOR2(
			0,
			GAME_CLEAR_LOGO_HEIGHT * (frame / 16 % 4)
		);

	DrawSprite(gameClearTexture, { 200,64 }, 10, { GAME_CLEAR_LOGO_WIDTH,GAME_CLEAR_LOGO_HEIGHT }, tPos, { GAME_CLEAR_LOGO_WIDTH,GAME_CLEAR_LOGO_HEIGHT });
	DrawSelectButton();
}

void UpdateGameClear()
{
	UpdateSelectButton();

	frame++;
}


