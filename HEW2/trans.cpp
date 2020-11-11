// --------------------------------------------------------------
//							[trans.cpp]
// 
//							Author:Kanna Noda
//----------------------------------------------------------------

#include "trans.h"


void UpdateTrans(TRANS* trans) {
	// �X�V�����ʒu��ۊ�
	INTVECTOR2 compare;
	compare.x = (int)trans->pos.x;
	compare.y = (int)trans->pos.y;

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (compare == trans->intPos) {
		return;
	}

	trans->intLastPos = trans->intPos;

	// intPos�Ɍ��݂̈ʒu������
	trans->intPos = compare;
}
void UpdateTransX(TRANS* trans) {
	// �X�V�����ʒu��ۊ�
	int x = (int)trans->pos.x;

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (x == trans->intPos.x) {
		return;
	}

	trans->intLastPos.x = trans->intPos.x;

	// intPos�Ɍ��݂̈ʒu������
	trans->intPos.x = x;
}
void UpdateTransY(TRANS* trans){
	// �X�V�����ʒu��ۊ�
	int y = (int)trans->pos.y;

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (y == trans->intPos.y) {
		return;
	}

	trans->intLastPos.y = trans->intPos.y;

	// intPos�Ɍ��݂̈ʒu������
	trans->intPos.y = y;
}