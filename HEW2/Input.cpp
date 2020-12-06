// -------------------------------------------------------------------------
//	���͂��Ƃ鏈��[Input.cpp]
// 
//						Author:Kanna Noda
// -------------------------------------------------------------------------

#include "Input.h"
#include "InputLogger.h"
#include "player.h"
#include "sceneManager.h"


void InitInput() {

}

void UninitInput(){

}

void UpdateInput() {

	// �v���C���[�̈ړ�
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

	// �u���b�N�̌���i�����_�ł�press�ɂ��Ă܂��j
	if (TriggerInputLogger(MYVK_ENTER)) {
		BlockDecision();
	}
	if (TriggerInputLogger(MYVK_BEACON)) {
		PutBeacon();
	}
	if (TriggerInputLogger(MYVK_PURGE)) {
		PurgePlayerFlyingObject();
	}

#if _DEBUG
	DebugPrintInputLogger();
	if (TriggerInputLogger(MYVK_GAME_CLEAR)) {
		GoNextScene(GameClearScene);
	}

	if (TriggerInputLogger(MYVK_GAME_OVER)) {
		GoNextScene(GameOverScene);
	}
#endif
}

void DrawInput() {

}

