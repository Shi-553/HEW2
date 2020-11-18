#define _CRT_SECURE_NO_WARNINGS

//�@��ˑ��̃��C�u�����w��
//#pragma comment(lib,"d3d9.lib")
//#if  defined(DEBUG)||defined(_DEBUG)
//#pragma comment(lib,"d3dx9d.lib")
//$else
//#pragma comment(lib,"d3dx9.lib")
//#endif //  defined(DEBUG)||defined(_DEBUG)


#include <Windows.h>
#include "debugPrintf.h"
#include <d3d9.h>

//���w�n�̃��C�u���� DX11�Ƃ����Ƃ܂��ʂɃ����N���Ȃ��Ƃ����Ȃ�
#include <d3dx9.h>

#include "config.h"
#include "myd3d.h"
#include "sprite.h"
#include "texture.h"
#include "debugFont.h"
#include "system_timer.h"
#include "keyboard.h"
#include "mouse.h"
#include "InputLogger.h"
#include "sceneManager.h"
#include "time.h"


#define CLASS_NAME "GameWindow"
#define WINDOW_CAPTION "�E�C���h�E�\������"


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


static bool Init(HWND hWnd);
static void Update(void);
static void Draw();
static void Uninit(void);


int frameCount = 0;
int baseFrame = 0;

double baseTime = 0.0;
double fps = 0.0;
double reserveTime = 0.0;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	//�I���W�i���̃E�C���h�E�N���X������ēo�^
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;                          //�E�C���h�E�v���V�[�W���o�^
	wc.lpszClassName = CLASS_NAME;                     //�I���W�i���p�[�c�̃N���X��
	wc.hInstance = hInstance;                          //�C���X�^���X�n���h����o�^
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);          //�}�E���J�[�\���̎w��
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); //�w�i�F�̐ݒ�   COLOR_BACKGROUND �n�� +1 ���Ȃ��Ƃ����Ȃ�

	RegisterClass(&wc);

	DWORD windowsStyle = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, windowsStyle, false);

	LONG windowWidth = rect.right - rect.left;
	LONG windowHeight = rect.bottom - rect.top;


	//1. �E�C���h�E�̕��A�����̎擾�F�X

	//API�𗘗p���ăE�C���h�E�̕��A�������擾
	//RECT desktopRect;
	//GetWindowRect(GetDesktopWindow(), &desktopRect);

	//int desktopWidth = desktopRect.right - desktopRect.left;
	//int desktopHeight = desktopRect.bottom - desktopRect.top;


	//2. �f�o�C�X�i�V�X�e���j���烂�j�^�[�𑜓x���擾
	int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	int desktopHeight = GetSystemMetrics(SM_CYSCREEN);


	//3. �f���A�����j�^�[�̐^�񒆁i�قږ��ɗ����Ȃ��j
	//int virtualDesktopWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	//int virtualDesktopHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//int virtualDesktopX = GetSystemMetrics(SM_XVIRTUALSCREEN);
	//int virtualDesktopY = GetSystemMetrics(SM_YVIRTUALSCREEN);

	//�E�C���h�E��^�񒆂ɂ��邽�߂�XY
	int windowX = (desktopWidth - windowWidth) / 2;
	if (windowX < 0)
		windowX = 0;

	int windowY = (desktopHeight - windowHeight) / 2;
	if (windowY < 0)
		windowY = 0;


	//�E�C���h�E���
	//�n���h�� = ���j�[�N��ID
	HWND hWnd = CreateWindow(
		CLASS_NAME,              //�E�C���h�E �N���X
		WINDOW_CAPTION,          //�E�C���h�E �e�L�X�g(��ɂłĂ���)
		windowsStyle,     //�E�C���h�E �X�^�C��

		//�T�C�Y�ƈʒu
		windowX,   //��ʂ̍�����̎��g�̍��̍��W
		windowY,   //��ʂ̏ォ��̎��g�̏�̍��W

		windowWidth,   //�E�C���h�E�̕�
		windowHeight,   //�E�C���h�E�̍��� (�t���[�����܂�)

		NULL,            //�e�̃E�C���h�E�n���h��   
		NULL,            //���j���[�n���h��         ���u�t�@�C�� �ҏW �\�� �v���W�F�N�g...�v
		hInstance,       //�C���X�^���X�n���h��
		NULL             //�ǉ��̃A�v���P�[�V�����f�[�^ (�قڎg��Ȃ�)
	);

	if (hWnd == NULL) {
		//�E�C���h�E�n���h�����Ȃ񂩐����ł��Ȃ�����
		return -1;
	}

	if (!Init(hWnd)) {
		return -1;
	}


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//�E�C���h�E���b�Z�[�W�̎擾 
	MSG msg = {};
	while (TRUE) { //GetMessage���Ń��b�Z�[�W�҂����Ă�

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (WM_QUIT == msg.message)
				break;

			TranslateMessage(&msg);//�Ȃ񂩖|�󂷂�񂾂�������񂾂�

			DispatchMessage(&msg);//����ŃE�C���h�E�v���V�[�W�����Ă΂��
		}
		else {
			double time = SystemTimer_GetTime();

			if ((time - reserveTime) < 1.0f / 60.0f) {
				Sleep(0);
				continue;
			}
			reserveTime = time;

			Update();
			Draw();
		}
	}

	Uninit();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
		//�G�X�P�[�v�ŏI���V���[�g�J�b�g
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "�I�����Ă����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);   //WM_QUIT���b�Z�[�W�̑��M
		return 0;
	}

	switch (uMsg)
	{
	case WM_ACTIVATEAPP:
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard_ProcessMessage(uMsg, wParam, lParam);

		break;
	}
	Mouse_ProcessMessage(uMsg, wParam, lParam);

	//�f�t�H���g�̃��b�Z�[�W����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


bool Init(HWND hWnd) {
	Keyboard_Initialize();
	Mouse_Initialize(hWnd);

	InitTime(SystemTimer_GetTime());

	InitInputLogger();

	if (!InitMyD3D(hWnd)) {

		MessageBox(NULL, "�������G���[", "�G���[", MB_OK);
	}
	InitTexture();

	InitSceneManager(GameStartScene);

	InitDebugFont();

	SystemTimer_Initialize();
	reserveTime = baseTime = SystemTimer_GetTime();
	frameCount = baseFrame = 0;
	fps = 0.0;


	InitSprite();

	return true;

}

void Update(void) {
	UpdateInputLogger();
	UpdateSceneManager();

	UpdateTime(SystemTimer_GetTime());

	double time = SystemTimer_GetTime();

	if (time - baseTime > 1.0) {
		fps = (frameCount - baseFrame) / (time - baseTime);

		baseTime = time;
		baseFrame = frameCount;

	}
	frameCount++;
}


void Draw() {

	LPDIRECT3DDEVICE9 d3dDevice = GetD3DDevice();
	if (d3dDevice == NULL) {
		return;
	}

	//��ʂ̃N���ABeginScene,EndScene�̊O�ɏ�����
	//��O�����F(�F�o�b�t�@�A�[�x(Z)�o�b�t�@�A�X�e���V���o�b�t�@)
	//��l�����F(���F�ŃN���A���邩)
	//��܈����F(Z�o�b�t�@�̏������F��O 0�`1 ��)
	//��Z�����F(�X�e���V���̏������p)
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(30, 30,80, 255), 1.0f, 0);

	//�`�施�߂𒙂߂Ă���
	d3dDevice->BeginScene();

	DrawSceneManager();


	DEBUG_FONT_STATE state;
	state.z = -1000;
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	DrawDebugFont(&state,"FPS= %.2f", fps);



	//���߂�̏I���
	d3dDevice->EndScene();

	//���߂���Ƀo�b�t�@�ɊG��`���āA��O�̊G�Ɠ���ւ���
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}



void Uninit(void) {

	UninitSprite();
	UninitSceneManager();


	UninitDebugFont();

	UninitTexture();

	UninitMyD3D();

	UninitTime();

	UninitInputLogger();
}