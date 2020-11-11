#ifndef GRID_H_
#define GRID_H_

#include <d3d9.h>

// �O���b�h�`�惂�W���[���̏�����
//
// size  ... �O���b�h�T�C�Y
// count ... ��ӂ̃O���b�h��
// color ... �O���b�h�J���[

void Grid_Initialize(float size, int count, D3DCOLOR color);

void Grid_Finalize(void);

void Grid_Draw(void);

#endif // !GRID_H_
