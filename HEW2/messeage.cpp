#include "messeage.h"
#include "font.h"
#include"myd3d.h"
#include "config.h"
#include <d3dx9.h>
#include "trans.h"

#define FONT_WIDTH	(15)
#define FONT_HEIGHT	(32)


LPD3DXFONT font;
INTVECTOR2 offset_pos;
LPD3DXSPRITE sprite;


void InitMesseage() {
	 CreateFont(32,0,&font);
	LPDIRECT3DDEVICE9 device = GetD3DDevice();
	D3DXCreateSprite(device, &sprite);



}

void UninitMesseage() {
	sprite->Release();

}

void UpdateMesseage() {
	offset_pos = INTVECTOR2(0, 0);

}


void DrawMesseage(const char* str, D3DCOLOR color) {

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc = {
	SCREEN_WIDTH / 2 - 400 + offset_pos.x * FONT_WIDTH,		// �����x���W
	SCREEN_HEIGHT / 2 + 250 + offset_pos.y * FONT_HEIGHT,	// �����y���W
	SCREEN_WIDTH / 2 + 400 + offset_pos.x,					// �E����x���W
	SCREEN_HEIGHT / 2 + 350 + offset_pos.y + 800			// �E����y���W
	};


	font->DrawTextA(sprite, str, -1, &rc, DT_LEFT, color);
	sprite->End();

	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == '\n') {
			offset_pos.x = 0;
			offset_pos.y++;
		}
		else {
			offset_pos.x++;
		}
	}

}
