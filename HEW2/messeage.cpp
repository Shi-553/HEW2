#include "messeage.h"
#include "font.h"
#include"myd3d.h"
#include "config.h"
#include "trans.h"
#include <stdio.h>
#include <mbstring.h>


#define FONT_WIDTH	(long)(15 * 1.3)
#define FONT_HEIGHT	(long)(32 * 1.3)

#define FONT_COUNT_MAX_WIDTH (40)//���p30�����܂�
#define FONT_COUNT_MAX_HEIGHT (6)//10�s�܂�

//�����A�傫������ƍ��E�ɐL�т�
#define RECT_WIDTH (FONT_WIDTH*FONT_COUNT_MAX_WIDTH)
//�����A�傫������Ɖ��ɐL�т�
#define RECT_HEIGHT (FONT_HEIGHT*FONT_COUNT_MAX_HEIGHT)

//���S����ǂꂾ�����ɂ��邩
#define RECT_ADD_Y (75)

void UpdateRect(RECT& rect);

static LPD3DXFONT font;
static INTVECTOR2 offset;
static LPD3DXSPRITE sprite;
static D3DCOLOR color;


void InitMessage() {
	CreateFont(FONT_HEIGHT, FONT_WIDTH, &font);
	LPDIRECT3DDEVICE9 device = GetD3DDevice();
	D3DXCreateSprite(device, &sprite);

	color = D3DCOLOR_RGBA(255, 255, 255, 255);

}

void UninitMessage() {
	sprite->Release();
	font->Release();
}

void ClearMessageOffset() {
	offset = INTVECTOR2(0, 0);
}

void UpdateRect(RECT& rect) {
	rect = {
		(SCREEN_WIDTH - RECT_WIDTH) / 2 + offset.x * FONT_WIDTH,	         	// �����x���W
		SCREEN_HEIGHT / 2 + RECT_ADD_Y + offset.y * FONT_HEIGHT,				// �����y���W
		(SCREEN_WIDTH + RECT_WIDTH) / 2 ,		                                    // �E����x���W
		SCREEN_HEIGHT / 2 + RECT_ADD_Y + RECT_HEIGHT 		                        // �E����y���W
	};
}

void SetMessageColor(D3DCOLOR c) {
	color = c;
}

void DrawMessage(const char* str, va_list argp) {
	int length = _vscprintf(str, argp) + 1;// +1 '\0'
	if (length <= 1) {
		return;
	}
	char* buf = (char*)malloc(sizeof(char) * length);
	if (buf == NULL) {
		return;
	}

	vsprintf_s(buf, length, str, argp);

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	UpdateRect(rc);

	int startIndex = 0;

	for (int i = 0; i < length; i++) {//�I��������1�O�܂�
		//���s��
		bool isNewLine = buf[i] == '\n';
		//�Ōォ
		bool isEnd = i == length - 1;
		//�ő啶�������ǂ����i�ő傩�A�ő傩��1�O��2�o�C�g�����j
		bool isMax = (offset.x == FONT_COUNT_MAX_WIDTH) ||
			(offset.x == FONT_COUNT_MAX_WIDTH - 1 && _mbclen((BYTE*)&(buf[i])) == 2);

		if (isNewLine || isMax || isEnd) {
			font->DrawTextA(sprite,
				&(buf[startIndex]),
				i - startIndex,
				&rc,
				DT_LEFT,//����
				color);

			if (isNewLine || isMax) {
				offset.y++;
				offset.x = 0;
			}

			if (isNewLine) {
				startIndex = i + 1;//���s�����Ȃ炻����X�L�b�v
			}
			else {
				startIndex = i;
			}

			UpdateRect(rc);

			if (!isEnd &&!isNewLine &&isMax) {
				offset.x++;//�����̂Ƃ�������1�E�ւ��炷�ƂȂ������܂������E�E�E
			}

			continue;
		}

		offset.x++;
	}

	sprite->End();

	free(buf);

}

void DrawMessage(const char* str, ...) {
	va_list argp;
	va_start(argp, str);

	DrawMessage(str, argp);

	va_end(argp);
}
