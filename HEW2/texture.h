// �e�N�X�`���Ǘ� 2020/6/26 �ēc���F
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "myd3d.h"



void InitTexture();

void UninitTexture();



#define TEXTURE_MAX 1024
#define TEXTURE_FILENAME_MAX 256
#define TEXTURE_INVALID_ID -1

//�e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
//�����F�t�@�C����
//�߂�l�F�ő�Ǘ����𒴂��Ă�����INVALID_TEXTURE_ID
int ReserveTextureLoadFile(const char* fileName);


//�\�񂳂ꂽ�e�N�X�`���t�@�C���̓ǂݍ���
//�߂�l�F�ǂݍ��߂Ȃ������t�@�C����
//---------�f�o�C�X�̎擾�Ɏ��s����� -1
int LoadTexture();


//�e�N�X�`����I�����ĉ��
//����1�F����������e�N�X�`��ID
void ReleaseTexture(int textureIds);


//�e�N�X�`����I�����ĉ��
//����1�F����������e�N�X�`��ID�̐擪�A�h���X
//����2�F����������e�N�X�`����
void ReleaseTexture(int textureIds[], int count);


//�e�N�X�`����S���
void ReleaseAllTexture();


//�e�N�X�`���̑傫�����擾
//�����F�e�N�X�`��ID
//�߂�l�F�e�N�X�`���T�C�Y
D3DXVECTOR2* GetTextureSize(int textureId);


//�e�N�X�`���C���^�[�t�F�[�X�|�C���^�̎擾
//�����F�e�N�X�`��ID
//�߂�l�F�e�N�X�`���C���^�[�t�F�[�X�|�C���^
//---------�_���Ȃ�NULL
LPDIRECT3DTEXTURE9 GetTexture(int textureId);

#endif // !_TEXTURE_H_
