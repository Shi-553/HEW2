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