﻿#pragma once
#include "myd3d.h"
#include "texture.h"
#include "InputLogger.h"
#include <vector>

struct Button {
	D3DXVECTOR2 pos ;
	D3DXVECTOR2 size = D3DXVECTOR2(0, 0);

	int textureId=TEXTURE_INVALID_ID;
	int pressedTextureId=TEXTURE_INVALID_ID;

	void (*pressedCallback)  ()=NULL;
	void (*triggeredCallback)()=NULL;
	void (*releasedCallback) ()=NULL;
	void (*rightCallback) ()=NULL;
	void (*leftCallback) ()=NULL;

};
class SelectButton {
public:
	void Init();
	void DrawMain();
	void DrawLR();
	void Update();
	void Uninit();


	void Add(Button& button);
	void SetKey(VirtualKey enterKey, VirtualKey forwardKey, VirtualKey backKey);

	void SetFrame(int frame);
	void SetForward(int forward, int forwardPressed, D3DXVECTOR2 pos, D3DXVECTOR2 size = D3DXVECTOR2(0, 0));
	void SetBack(int back, int backPressed, D3DXVECTOR2 pos, D3DXVECTOR2 size = D3DXVECTOR2(0, 0));

	int GetIndex();
	void SetIndex(int index);

	static const int PRESS_FRAME_FIRST_LIMIT = 30;
	static const int PRESS_FRAME_LIMIT = 15;
private:

	void AllReleasePressedFlag();

	 std::vector<Button> buttons;
	 int selectedIndex;


	 bool isPressedEnter = false;
	 bool isPressedForward = false;
	 bool isPressedBack = false;

	 VirtualKey gEnterKey, gForwardKey, gBackKey;


	 int selectFrameTextureId = TEXTURE_INVALID_ID;

	 D3DXVECTOR2 forwardPos, backPos;
	 D3DXVECTOR2 forwardSize, backSize;

	 int forwardTextureId = TEXTURE_INVALID_ID;
	 int forwardPressedTextureId = TEXTURE_INVALID_ID;

	 int backTextureId = TEXTURE_INVALID_ID;
	 int backPressedTextureId = TEXTURE_INVALID_ID;

	 void PressInit();
	 void Press();
	 bool IsExceed();
	 int pressFrame = 0;
	 bool isPressExceeded = false;
};