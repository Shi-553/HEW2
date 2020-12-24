﻿#include "flyingObjectSponer.h"
#include "map.h"
#include <vector>
#include "debugPrintf.h"

using namespace std;


void CheckSpone();

static vector<Spone> spones;
static int frame = 0;
static int sponeIndex = 0;

static bool isLoop = true;

static Spone initSpone[24]{
	{100,{5.5,-3.5},FLYING_OBJECT_UFO,{0,1}},
	{150,{-3.5,8.5},FLYING_OBJECT_BLOCK,{1,0}},
	{200,{13.5,7.5},FLYING_OBJECT_ENEMY_BREAK_BLOCK,{-1,0}},
	{250,{13.5,1.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{300,{8.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}},
	{350,{3.5,-3.5},FLYING_OBJECT_ENEMY,{0,1}},
	{450,{13.5,3.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{500,{5.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}},
	{550,{2.5,13.5},FLYING_OBJECT_ENEMY_BREAK_BLOCK,{0,-1}},
	{600,{3.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}},
	{650,{13.5,7.5},FLYING_OBJECT_BLOCK,{-1,0}},
	{700,{-3.5,5.5},FLYING_OBJECT_BLOCK,{1,0}},
	{750,{-3.5,8.5},FLYING_OBJECT_BLOCK,{1,0}},
	{400,{2.5,13.5},FLYING_OBJECT_UFO,{0,-1}},
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
//	{1200,{13.5,1.5},FLYING_OBJECT_BLOCK,{-1,0}},
//	{1250,{7.5,13.5},FLYING_OBJECT_BLOCK,{0,-1}}
//};

void InitFlyingSponer() {
	frame = 0;
	sponeIndex = 0;
	spones.clear();

	for (int i = 0; i < 24; i++)
	{
		spones.push_back(initSpone[i]);
	}
}



void UninitFlyingSponer() {
}
void UpdateFlyingSponer() {
	CheckSpone();
	frame++;

	if (isLoop && sponeIndex == spones.size()) {
		frame = 0;
		sponeIndex = 0;
	}


}
void CheckSpone() {
	while (sponeIndex < spones.size()) {
		if (spones[sponeIndex].frame <= frame) {
			FlyingObject f = { TRANS(spones[sponeIndex].initPos),spones[sponeIndex].type, spones[sponeIndex].dir,sponeIndex };
			AddFlyingObjects(&f);
			sponeIndex++;
		}
		else {
			break;
		}
	}
}

void AddFlyingObjectSponer(Spone s) {
	for (auto itr = spones.begin(); itr != spones.end(); itr++) {
		if (itr->frame > s.frame) {
			spones.insert(itr, s);
			CheckSpone();
			break;
		}
	}
}

Spone* GetFlyingObjectSponer(int index) {
	if (index < 0 || spones.size() <= index) {
		return NULL;
	}
	return &spones[index];
}

void SetFlyingObjectSponerLoop(bool f) {
	isLoop = f;
}

bool GetFlyingObjectSponerLoop() {
	return isLoop;
}

bool FlyingObjectSponerExport(FILE* fp) {

	//	ファイルへの書き込み処理
	int size = spones.size();
	fwrite(&size, sizeof(int), 1, fp);

	for (auto itr = spones.begin(); itr != spones.end(); itr++) {
		fwrite(&*itr, sizeof(Spone), 1, fp);
	}

	return true;
}


bool FlyingObjectSponerImport(FILE* fp) {
	spones.clear();

	//	ファイルからの読み込み処理
	int size;
	fread(&size, sizeof(int), 1, fp);

	for (int i = 0; i < size; i++) {
		Spone s;
		fread(&s, sizeof(Spone), 1, fp);
		spones.push_back(s);
	}


	return true;
}





int GetFlyingObjectSponeFrame() {
	return frame;
}
void SetFlyingObjectSponeFrame(int f) {
	BackFlyingObject(frame - f);

	if (frame < f) {
		frame = f;
		CheckSpone();
	}
	else {
	if (f < 0) {
		f = spones.back().frame;
		sponeIndex = spones.size();
	}

		frame = f;

		while (sponeIndex > 0) {
			if (spones[sponeIndex-1].frame > frame) {
				sponeIndex--;
				auto itr=find_if(GetFlyingObjects()->begin(), GetFlyingObjects()->end(), [](FlyingObject f) {return sponeIndex == f.id; });
				if (itr != GetFlyingObjects()->end()) {
					if (itr->type == FLYING_OBJECT_UFO) {
						DestroyUFO();
					}
					GetFlyingObjects()->erase(itr);
				}
			}
			else {
				break;
			}
		}
		DebugPrintf("%d,\n", sponeIndex);
	}
}
