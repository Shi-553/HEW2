//ゲーム本体
// テストコメント
// テスト２

//リモート・マスターからブランチ分けて追加
#include "config.h"
#include "texture.h"
#include "sprite.h"
#include "debugFont.h"
#include "player.h"
#include "npc.h"
#include "GameOperation.h"
#include "game.h"


void InitGame() {
	InitPlayer();
	InitGameOperation();
	InitNPC();
	LoadTexture();
	
}

void UpdateGame() {

	UpdateGameOperation();
	UpdatePlayer();
	UpdateNPC();
}

void DrawGame() {
	DrawPlayer();
	DrawNPC();
}

void UninitGame() {
	UninitGameOperation();
	UninitPlayer();
	UninitNPC();
}

