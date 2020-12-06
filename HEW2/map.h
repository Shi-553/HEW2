#ifndef MAP_H
#define MAP_H

#include "myd3d.h"
#include "flyingObject.h"
#include "trans.h"



enum MapType
{
	MAP_NONE,    // �����Ȓl
	MAP_BLOCK_NONE,  // �u���b�N�Ȃ�
	MAP_BLOCK,       // �u���b�N
	MAP_WALL,     // ��
	MAP_ROCK,        // ��
	MAP_GOAL,        // �S�[��
	MAP_MAX
};

struct Map
{
	MapType type;
	INTVECTOR2 dir = INTVECTOR2::GetNone();
};


void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

// �u�����Ƃ���̃}�b�v�^�C�v��ς���
void MapChange(FlyingObject flyingobject);

// 4�����Ƀu���b�N�����邩�̔���
bool MapFourDirectionsJudgment(INTVECTOR2 pos);

// �ʒu���w�肵�ă}�b�v�^�C�v��Ԃ�
MapType GetMapType(INTVECTOR2 pos);

bool MapExport(const char* filename);
bool MapImport(const char* filename);

Map& GetMap(int y, int x);

int GetMapHeight();
int GetMapWidth();

#endif // !MAP_H
