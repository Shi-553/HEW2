// --------------------------------------------------------------
//  当たり判定の処理[judge.cpp]
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

	// 当たっている場合は１を返します
	if (playerX == objectX || playerY == objectY) return 1;

	// 当たっていない場合は０を返します
	return 0;

}

