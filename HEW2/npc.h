﻿#ifndef _NPC_H
#define _NPC_H
#include "trans.h"

typedef struct NPC_tag {
	TRANS trans;
	float speed;
	int frame;
	int aniFrame;
	bool isMove;
	bool contactUFO;
	int takeOutFrame;
	INTVECTOR2 responePos;
	D3DXVECTOR2 size;
}NPC;

#define TAKE_OUT_FRAME_LIMIT (10 * 60)

void InitNPC();
void UpdateNPC();
void DrawNPC();
void UninitNPC();

void UpdateNPCShortestPath(INTVECTOR2 beaconPos);
void UpdateNPCShortestPath();

void SecureMapLabelList();

NPC* GetNpc();

bool NPCExport(FILE* fp);
bool NPCImport(FILE* fp);

void SetNPCResponePos(INTVECTOR2 pos);

#endif // !_NPC_H