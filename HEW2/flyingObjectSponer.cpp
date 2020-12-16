﻿#include "flyingObjectSponer.h"
#include "flyingObject.h"
#include "map.h"


struct Spone {
	int frame;
	D3DXVECTOR2 initPos;
	FlyingObjectType type;
	D3DXVECTOR2 dir;
};

static Spone* spones = NULL;
static int frame = 0;
static int sponeIndex = 0;
static int sponeMax = 28;

static Spone initSpone[28]{
	{0,{2.5,1.5},FLYING_OBJECT_ITEM_ADD_SPEED,{0,0}},
	{0,{5.5,5.5},FLYING_OBJECT_ITEM_ADD_MAGNETIC_FORCE,{0,0}},
	{0,{7.5,7.5},FLYING_OBJECT_ITEM_CHAGE_BLOCK_UNBREAKABLE,{0,0}},
	{100,{5.5,-3.5},FLYING_OBJECT_BLOCK,{0,1}},
	{150,{-3.5,8.5},FLYING_OBJECT_BLOCK,{1,0}},
	{200,{13.5,7.5},FLYING_OBJECT_ENEMY_BREAK_BLOCK,{-1,0}},
	{250,{13.5,1.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{300,{8.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}},
	{350,{3.5,-3.5},FLYING_OBJECT_ENEMY,{0,1}},
	{400,{2.5,13.5},FLYING_OBJECT_UFO,{0,-1}},
	{450,{13.5,3.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{500,{5.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}},
	{550,{2.5,13.5},FLYING_OBJECT_ENEMY_BREAK_BLOCK,{0,-1}},
	{600,{3.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}},
	{650,{13.5,7.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{700,{-3.5,5.5},FLYING_OBJECT_BLOCK,{1,0}},
	{750,{-3.5,8.5},FLYING_OBJECT_BLOCK,{1,0}},
	{800,{3.5,13.5},FLYING_OBJECT_ENEMY,{0,-1}},
	{850,{13.5,5.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{900,{2.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}},
	{950,{8.5,-3.5},FLYING_OBJECT_ENEMY_BREAK_BLOCK,{0,1}},
	{1000,{-3.5,8.5},FLYING_OBJECT_BLOCK,{1,0}},
	{1050,{13.5,3.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{1100,{6.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}},
	{1150,{4.5,-3.5},FLYING_OBJECT_ENEMY,{0,1}},
	{1200,{13.5,1.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{1250,{7.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}}
};

void InitFlyingSponer() {
	frame = 0;
	sponeIndex = 0;
	spones = NULL;

	spones = new Spone[sponeMax];
	CopyMemory(spones, initSpone, sizeof(Spone)* sponeMax);


}
void UninitFlyingSponer() {
	if (spones != NULL) {
		delete[] spones;
		spones = NULL;
	}
}
void UpdateFlyingSponer() {
	while (sponeIndex < sponeMax) {
		if (spones[sponeIndex].frame == 0) {
			sponeIndex++;
			continue;
		}
		if (spones[sponeIndex].frame <= frame) {
			FlyingObject f = {TRANS(spones[sponeIndex].initPos),spones[sponeIndex].type, spones[sponeIndex].dir};
			AddFlyingObjects(&f);
			sponeIndex++;
		}
		else {
			break;
		}
	}

	frame++;
	if (sponeIndex== sponeMax){
		frame = 0;
		sponeIndex = 0;
	}


}

bool FlyingObjectSponerExport(FILE* fp) {

	//	ファイルへの書き込み処理
	fwrite(&sponeMax, sizeof(int), 1, fp);
	fwrite(spones, sizeof(Spone), sponeMax, fp);

	return true;
}


bool FlyingObjectSponerImport(FILE* fp) {
	if (spones != NULL) {
		delete[] spones;
		spones = NULL;
	}

	//	ファイルへの読み込み処理
	fread(&sponeMax, sizeof(int), 1, fp);
	spones = new Spone[sponeMax];
	fread(spones, sizeof(Spone), sponeMax, fp);

	return true;
}
