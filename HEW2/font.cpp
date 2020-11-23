
#include "font.h"
#include <stdio.h>
#include "debugPrintf.h"

static LPD3DXFONT	pFont=NULL;
static auto fontPath = "./font/PixelMplus-20130602/PixelMplus10-Regular.ttf";

LPD3DXFONT GetFont() {
		return pFont;
}


void InitFont() {
	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) <= 0) {
		DebugPrintf("error AddFontResourceEx\n");
		return;
	}

	auto device = GetD3DDevice();

	auto hr = D3DXCreateFont(
		device,				// Direct3D�f�o�C�X
		32,						// ����
		15,						// ��
		FW_REGULAR,				// �t�H���g�̑��� ����
		NULL,					// ����
		FALSE,					// �Α�
		DEFAULT_CHARSET,		// �����Z�b�g
		OUT_DEFAULT_PRECIS,		// �o�͐��x�͕���
		PROOF_QUALITY,			// �����i�����d��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~��
		"PixelMplus10",	// �t�H���g��
		&pFont);					

	if (FAILED(hr))
	{
		DebugPrintf("error font\n");
		return;
	}

	//�����Ŏg�����������[�h���Ă����Ƃ��悢
	//pFont->PreloadText("",sizeof(""));
}
void UninitFont() {
	if (pFont != NULL) {
		pFont->Release();
		pFont = NULL;
	}
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL) <= 0) {
		DebugPrintf("error RemoveFontResourceEx\n");
	}
}

//void DrawFont() {
//	auto font = GetFont();
//	LPD3DXSPRITE sprite = NULL;
//	D3DXCreateSprite(d3dDevice, &sprite);
//
//	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
//
//	RECT rc = {
//	SCREEN_WIDTH / 2 - 400,		// �����x���W
//	SCREEN_HEIGHT / 2 + 250,		// �����y���W
//	SCREEN_WIDTH / 2 + 400,		// �E����x���W
//	SCREEN_HEIGHT / 2 + 350		// �E����y���W
//	};
//	auto hdc = font->GetDC();
//
//	font->DrawTextA(sprite, "unicode support", -1, &rc, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//	sprite->End();
//	sprite->Release();
//}