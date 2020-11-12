// --------------------------------------------------------------
//							[trans.cpp]
// 
//							Author:Kanna Noda
//----------------------------------------------------------------

#include "trans.h"


void TRANS::UpdatePos() {
	// �X�V�����ʒu��ۊ�
	INTVECTOR2 compare((int)pos.x, (int)pos.y);

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (compare == intPos) {
		return;
	}

	intLastPos = intPos;

	// intPos�Ɍ��݂̈ʒu������
	intPos = compare;
}
void TRANS::UpdateX() {
	// �X�V�����ʒu��ۊ�
	int x = (int)pos.x;

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (x == intPos.x) {
		return;
	}

	intLastPos.x = intPos.x;

	// intPos�Ɍ��݂̈ʒu������
	intPos.x = x;
}
void TRANS::UpdateY(){
	// �X�V�����ʒu��ۊ�
	int y = (int)pos.y;

	// �X�V�����ʒu�ƌ��̈ʒu���r
	if (y == intPos.y) {
		return;
	}

	intLastPos.y = intPos.y;

	// intPos�Ɍ��݂̈ʒu������
	intPos.y = y;
}