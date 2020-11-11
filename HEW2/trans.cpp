// --------------------------------------------------------------
//							[trans.cpp]
// 
//							Author:Kanna Noda
//----------------------------------------------------------------

#include "trans.h"

void MoveTrans(TRANS* trans, D3DXVECTOR2 addPos) {
	INTVECTOR2 compare;

	// �ʒu��addPos���ǉ�����
	trans->pos += addPos;
	
	// �X�V�����ʒu��ۊ�
	compare.x = (int)trans->pos.x;
	compare.y = (int)trans->pos.y;

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (compare.x == trans->intPos.x && compare.y == trans->intPos.y) {
		return;
	}

	trans->intLastPos.x = trans->intPos.x;
	trans->intLastPos.y = trans->intPos.y;

	// intPos�Ɍ��݂̈ʒu������
	trans->intPos.x = compare.x;
	trans->intPos.y = compare.y;


}

void MoveTransX(TRANS* trans, float x) {
	INTVECTOR2 compare;

	// �ʒu��addPos���ǉ�����
	trans->pos.x += x;

	// �X�V�����ʒu��ۊ�
	compare.x = (int)trans->pos.x;

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (compare.x == trans->intPos.x) {
		return;
	}

	trans->intLastPos.x = trans->intPos.x;

	// intPos�Ɍ��݂̈ʒu������
	trans->intPos.x = compare.x;


}

void MoveTransY(TRANS* trans, float y) {
	INTVECTOR2 compare;

	// �ʒu��addPos���ǉ�����
	trans->pos.y += y;

	// �X�V�����ʒu��ۊ�
	compare.y = (int)trans->pos.y;

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (compare.y == trans->intPos.y) {
		return;
	}

	trans->intLastPos.y = trans->intPos.y;

	// intPos�Ɍ��݂̈ʒu������
	trans->intPos.y = compare.y;


}