#include "map.h"
#include "myd3d.h"
#include "texture.h"
#include "gameSrite.h"
#include "sprite.h"



static MapType initMapChipList[MAPCHIP_HEIGHT][MAPCHIP_WIDTH]
{
	{MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL, MAP_WALL},
	{MAP_WALL, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_WALL},
	{MAP_WALL, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE,       MAP_GOAL, MAP_BLOCK_NONE, MAP_WALL},
	{MAP_WALL, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_WALL},
	{MAP_WALL, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_WALL},
	{MAP_WALL, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE,       MAP_ROCK, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_WALL},
	{MAP_WALL, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_WALL},
	{MAP_WALL, MAP_BLOCK_NONE,      MAP_BLOCK, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_WALL},
	{MAP_WALL, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_BLOCK_NONE, MAP_WALL},
	{MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL,       MAP_WALL, MAP_WALL},

};

static MapType MapChipList[MAPCHIP_HEIGHT][MAPCHIP_WIDTH];
static int textureIds[MAP_MAX];
static int map_textureIds;

void InitMap(void)
{
	map_textureIds = ReserveTextureLoadFile("texture/�w�i�P.png");

	textureIds[MAP_NONE] = ReserveTextureLoadFile("texture/MAP_NONE.png");
	textureIds[MAP_BLOCK_NONE] = ReserveTextureLoadFile("texture/MAP_BLOCK_NONE.png");
	textureIds[MAP_BLOCK] = ReserveTextureLoadFile("texture/block02.png");
	textureIds[MAP_WALL] = ReserveTextureLoadFile("texture/meteorite_1.png");
	textureIds[MAP_ROCK] = ReserveTextureLoadFile("texture/brokenblock01.png");
	textureIds[MAP_GOAL] = ReserveTextureLoadFile("texture/magnekko_goalflag01.png");

	for (int i = 0; i < MAPCHIP_HEIGHT; i++) {
		for (int j = 0; j < MAPCHIP_WIDTH; j++) {
			MapChipList[i][j] = initMapChipList[i][j];
		}
	}
}

void UninitMap(void)
{
		ReleaseTexture(textureIds, MAP_MAX);
		ReleaseTexture(map_textureIds);
}

void UpdateMap(void)
{

}

void DrawMap(void)
{
	DrawSprite(map_textureIds, { 0,0 }, 10, { SCREEN_WIDTH,SCREEN_HEIGHT }, { 0,0 }, { SCREEN_WIDTH,SCREEN_HEIGHT });

	for (int i = 0; i < MAPCHIP_HEIGHT; i++) {
		for (int j = 0; j < MAPCHIP_WIDTH; j++) {
			DrawGameSprite(textureIds[MapChipList[j][i]], D3DXVECTOR2(i, j), 100);
		}
	}
}

void MapChange(FlyingObject flyingobject)
{
	auto intPos= flyingobject.trans.GetIntPos();

	if (intPos.x < 0 ||intPos.y < 0 || intPos.x >= MAPCHIP_WIDTH || intPos.y >= MAPCHIP_HEIGHT) {
		return;
	}

	if (flyingobject.type == FLYING_OBJECT_BLOCK) {
		MapChipList[intPos.y][intPos.x] = MAP_BLOCK;
	}
}

bool MapFourDirectionsJudgment(D3DXVECTOR2 pos)
{
	int x = pos.x;
	int y = pos.y;

	if (MapChipList[y + 1][x] == MAP_BLOCK) {
		return true;
	}
	if (MapChipList[y - 1][x] == MAP_BLOCK) {
		return true;
	}
	if (MapChipList[y][x + 1] == MAP_BLOCK) {
		return true;
	}
	if (MapChipList[y][x - 1] == MAP_BLOCK) {
		return true;
	}

	return false;
}

MapType GetMapType(D3DXVECTOR2 pos)
{
	int x = pos.x;
	int y = pos.y;

	if (x < 0 || y < 0 || x >= MAPCHIP_WIDTH || y >= MAPCHIP_HEIGHT) {
		return MAP_NONE;
	}

	return MapChipList[y][x];
}