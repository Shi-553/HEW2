//Direct3D�̊j��������
// a
#include <Windows.h>


#include "myd3d.h"
#include "config.h"


static LPDIRECT3D9 d3d = NULL;
static LPDIRECT3DDEVICE9 d3dDevice = NULL;


//�߂�l ���s:false
bool InitMyD3D(HWND hWnd) {
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL) {
		MessageBox(NULL, "Direct3D�C���^�[�t�F�[�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�X���b�v���@
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;//�[�x�o�b�t�@�E�X�e���V���o�b�t�@�̎g�p1
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�[�x�o�b�t�@�E�X�e���V���o�b�t�@�̃t�H�[�}�b�g

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//�t���X�N���[���̂Ƃ��̃��t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//���

	HRESULT hr;
	hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice);

	if (FAILED(hr)) {
		MessageBox(NULL, "Direct3D�f�o�C�X�̎擾�Ɏ��s���܂���", "�G���[", MB_OK);
		return false;
	}


	//�e�N�X�`���t�B���^�����O�̐ݒ�
	//�g��k�����ɂ����ԂƁA����Ƀ~�b�v�}�b�v���g�����ǂ���
	//gPDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//�g�厞�t�B���^
	//gPDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//�k�����t�B���^
	//gPDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);//�~�b�v�}�b�v�t�B���^

	d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//�A�h���b�V���O���[�h�̐ݒ�
	//�e�N�X�`���̃A���t�@�l���g����
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//�A���t�@�u�����hON
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//�\�[�X�Ƀ\�[�X�̃A���t�@��������
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//�\�[�X�̉��ɂ�����̂́i�P�|�\�[�X�̃A���t�@�j��������
	d3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);//


	//�f�t�H���g�̃e�N�X�`���X�e�[�W�X�e�[�g
	//�F���ǂ����邩�V�F�[�_�[�g���Ɨv��Ȃ��Ȃ�
	//RGB
	//gPDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_CURRENT);
	//gPDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//gPDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	//gPDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);//OP(���Z�q)SELECTARG1 �e�N�X�`������ SELECTARG2 ���_�J���[����

	//ALPHA
	//gPDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
	//gPDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//gPDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//gPDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	//��Z�ɂȂ�
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	return true;
}

void UninitMyD3D() {
	if (d3dDevice) {
		d3dDevice->Release();
		d3dDevice = NULL;
	}
	if (d3d) {
		d3d->Release();
		d3d = NULL;
	}

}

LPDIRECT3DDEVICE9 GetD3DDevice() {
	return d3dDevice;
}