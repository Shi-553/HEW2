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
	MAP_WALL,        // ��
	MAP_ROCK,        // ��
	MAP_GOAL,         // �S�[��
	MAP_MAX
};

#define MAPCHIP_WIDTH  (10)
#define MAPCHIP_HEIGHT (10)


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

#endif // !MAP_H
