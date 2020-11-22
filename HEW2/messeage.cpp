#include "messeage.h"
#include "font.h"
#include"myd3d.h"
#include "config.h"
#include <d3dx9.h>


LPD3DXFONT font;
int offset_pos;


void InitMesseage() {
	font = GetFont();




}

void UninitMesseage() {

}

void UpdateMesseage() {

}


void DrawMesseage() {
	LPDIRECT3DDEVICE9 device = GetD3DDevice();
	LPD3DXSPRITE sprite = NULL;
	D3DXCreateSprite(device, &sprite);

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc = {
	SCREEN_WIDTH / 2 - 400,		// �����x���W
	SCREEN_HEIGHT / 2 + 250,		// �����y���W
	SCREEN_WIDTH / 2 + 400,		// �E����x���W
	SCREEN_HEIGHT / 2 + 350		// �E����y���W
	};
	auto hdc = font->GetDC();

	font->DrawTextA(sprite, "unicode support", -1, &rc, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	sprite->End();
	sprite->Release();

}
