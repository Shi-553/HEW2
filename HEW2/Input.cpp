// -------------------------------------------------------------------------
//	���͂��Ƃ鏈��[Input.cpp]
// 
//						Author:Kanna Noda
// -------------------------------------------------------------------------

#include "Input.h"
#include "InputLogger.h"
#include "player.h"


void InitInput() {

}

void UninitInput(){

}

void UpdateInput() {

	// �v���C���[�̈ړ��iif���̒���player�̈ړ������܂��j
	if (PressInputLogger(MYVK_UP)) {
		MoveUpPlayer();
	}
	if (PressInputLogger(MYVK_DOWN)) {
		MoveDownPlayer();
	}
	if (PressInputLogger(MYVK_LEFT)) {
		MoveLeftPlayer();
	}
	if (PressInputLogger(MYVK_RIGHT)) {
		MoveRightPlayer();
	}

	// �v���C���[�̌���i�����_�ł�press�ɂ��Ă܂��j
	if (PressInputLogger(MYVK_ENTER)) {

	}

}

void DrawInput() {

}

