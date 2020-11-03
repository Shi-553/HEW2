#ifndef MAP_H
#define MAP_H

#include "myd3d.h"
#include "flyingObject.h"

enum MapType
{
	MAP_NONE,    // �����Ȓl
	MAP_BLOCK_NONE,  // �u���b�N�Ȃ�
	MAP_BLOCK,       // �u���b�N
	MAP_WALL,        // ��
	MAP_ROCK,        // ��
	MAP_GOAL         // �S�[��
};

#define MAPCHIP_WIDTH  (10)
#define MAPCHIP_HEIGHT (10)


void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

// �u�����Ƃ���̃}�b�v�^�C�v��ς���
void MapChange(FlyingObject flyingobject);

// �ʒu���w�肵�ă}�b�v�^�C�v��Ԃ�
MapType GetMapType(D3DXVECTOR2 pos);

#endif // !MAP_H
