// --------------------------------------------------------------
//  �����蔻��̏���[judge.cpp]
// 
//							Author:Kanna Noda
//----------------------------------------------------------------

#include "player.h"
#include "flyingObject.h"
#include "judge.h"
void InitJudge(){

}

void UninitJudge() {
	//test
}

void UpdateJudge(){

}

void DrawJudge(){

}

int JudgePlayerandFlyingObjectHit(int playerX, int playerY, int objectX, int objectY) {

	// �������Ă���ꍇ�͂P��Ԃ��܂�
	if (playerX == objectX || playerY == objectY) return 1;

	// �������Ă��Ȃ��ꍇ�͂O��Ԃ��܂�
	return 0;

}

