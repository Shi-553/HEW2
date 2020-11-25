// �e�N�X�`���Ǘ� 2020/6/26 �ēc���F
#define _CRT_SECURE_NO_WARNINGS

#include "texture.h"
#include <string.h>
#include "debugPrintf.h"



typedef struct {
	LPDIRECT3DTEXTURE9 texture;
	char filename[TEXTURE_FILENAME_MAX];
	D3DXVECTOR2* size;
	int referenceCount;
}Texture;

void InitTextureStruct(Texture* t);

// Texture�\���̂̏�����
void InitTextureStruct(Texture* t) {
	if (t->texture != NULL) {
		t->texture->Release();
	}
	t->texture = NULL;

	if (t->size != NULL) {
		free(t->size);
	}
	t->size = NULL;

	t->filename[0] = '\0';
	t->referenceCount = 0;
}

static Texture textures[TEXTURE_MAX];

// texture.cpp�̏�����
void InitTexture() {
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		InitTextureStruct(&textures[i]);
	}
}
void UninitTexture() {
}


//�e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
//�����F�t�@�C����
//�߂�l�F�ő�Ǘ����𒴂��Ă�����INVALID_TEXTURE_ID
int ReserveTextureLoadFile(const char* filename) {

	int freeIndex = -1;

	//���ɗ\�񂳂�Ă���ꍇ�\�񂵂Ȃ�
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (textures[i].referenceCount == 0) {
			//�������󂢂Ă���
			if (freeIndex == -1) {
				freeIndex = i;
			}
			continue;
		}

		//�n�b�V�������Ƒ����Ȃ�
		if (strcmp(filename, textures[i].filename) == 0) {
			textures[i].referenceCount++;

			//���ɗ\�񂳂�Ă���
			return i;
		}
	}

	if (freeIndex == -1) {
		return TEXTURE_INVALID_ID;
	}

	strcpy(textures[freeIndex].filename, filename);

	textures[freeIndex].referenceCount = 1;

	return freeIndex;
}


//�\�񂳂ꂽ�e�N�X�`���t�@�C���̓ǂݍ���
//�߂�l�F�ǂݍ��߂Ȃ������t�@�C����
//---------�f�o�C�X�̎擾�Ɏ��s����� -1
int LoadTexture() {
	LPDIRECT3DDEVICE9 device = GetD3DDevice();
	if (device == NULL) {
		return -1;
	}

	int errorCount = 0;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (textures[i].filename[0] == '\0') {
			//�\�񂳂�Ă��Ȃ�
			continue;
		}
		if (textures[i].texture != NULL) {
			//���ɓǂݍ��܂�Ă���
			continue;
		}
		//�e�N�X�`���T�C�Y���擾
		D3DXIMAGE_INFO info;
		D3DXGetImageInfoFromFile(textures[i].filename, &info);
		textures[i].size = (D3DXVECTOR2*)malloc(sizeof(D3DXVECTOR2));
		if (textures[i].size == NULL) {
			DebugPrintf("�T�C�Y�擾���s Index: %d ,Filename: %s\n", i, textures[i].filename);
			errorCount++;
			continue;
		}
		textures[i].size->x = info.Width;
		textures[i].size->y = info.Height;

		//���I�Ƀ��������m�ۂ��Ă����ɓǂݍ���ŁA���̃���������DirectX�̃e�N�X�`���ɂ���ƌ���������

		HRESULT hr = D3DXCreateTextureFromFileEx(device,
			textures[i].filename, 
			info.Width,info.Height, 
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED, 
			D3DX_DEFAULT, 
			D3DX_DEFAULT,
			0, 
			NULL,
			NULL,
			&textures[i].texture);
		//HRESULT hr = D3DXCreateTextureFromFileInMemory(device, textures[i].filename, &textures[i].texture);

		if (FAILED(hr)) {
			DebugPrintf("�e�N�X�`���ǂݍ��ݎ��s Index: %d ,Filename: %s\n", i, textures[i].filename);
			errorCount++;
		}
	}

	return errorCount;
}

//�e�N�X�`����I�����ĉ��
//����1�F����������e�N�X�`����
void ReleaseTexture(int textureId) {
	if (textureId < 0 || TEXTURE_MAX < textureId) {
		return;
	}

	Texture* t = &textures[textureId];

	if (t->texture == NULL) {
		return;
	}

	t->referenceCount--;

	if (t->referenceCount != 0) {
		return;
	}

	InitTextureStruct(t);
}

//����1�F����������e�N�X�`��ID�̐擪�A�h���X
//����2�F����������e�N�X�`����
void ReleaseTexture(int textureIds[], int count) {
	for (int i = 0; i < count; i++)
	{
		ReleaseTexture(textureIds[i]);

	}
}

//�e�N�X�`����S���
void ReleaseAllTexture() {
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		InitTextureStruct(&textures[i]);
	}

}


//�e�N�X�`���̃T�C�Y���擾
//�����F�e�N�X�`��ID
//�߂�l�F�e�N�X�`���̃T�C�Y
D3DXVECTOR2* GetTextureSize(int textureId) {
	if (textureId < 0 || TEXTURE_MAX < textureId) {
		return NULL;
	}

	return textures[textureId].size;
}

//�e�N�X�`���C���^�[�t�F�[�X�|�C���^�̎擾
//�����F�e�N�X�`��ID
//�߂�l�F�e�N�X�`���C���^�[�t�F�[�X�|�C���^
//---------�_���Ȃ�NULL
LPDIRECT3DTEXTURE9 GetTexture(int textureId) {
	if (textureId < 0 || TEXTURE_MAX < textureId) {
		return NULL;
	}

	return textures[textureId].texture;
}