﻿#define _CRT_SECURE_NO_WARNINGS

#include "InputLogger.h"
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"
#include "debugPrintf.h"
#include "config.h"

#define KEY_CONVERSIOINS_MAX (32)
#define AXIS_CONVERSIOINS_MAX (8)



typedef struct KeyConversion {
	VirtualKey virtualKey;
	int realKey;
};

typedef struct AxisConversion {
	VirtualAxis virtualAxis;
	int realAxis;
};

enum LoggerMode
{
	LOGGER_NORMAL,
	LOGGER_RECORD,
	LOGGER_TRACE,
};

static LoggerMode inputloggerMode = LOGGER_NORMAL;

typedef unsigned long long InputLoggerType;

static InputLoggerType padData = 0;
static InputLoggerType previous = 0;
static InputLoggerType trigger = 0;
static InputLoggerType release = 0;

static InputLoggerType* recordCurrent = NULL;

static int currentAxis[MYVA_MAX] = {};
static int previousAxis[MYVA_MAX] = {};
static int axisMaxs[MYVA_MAX] = {};


static  int* recordCurrentAxis[MYVA_MAX] = {};

static int recordFrame = 0;
static int recordTraceFrame = 0;

static char* recordFilename = NULL;
static int gRecordframeMax = 0;


static Gamepad* gamepad = Gamepad::GetInstance();


static KeyConversion KeyConversions[KEY_CONVERSIOINS_MAX]{
	{MYVK_UP,KK_W},
	{MYVK_DOWN,KK_S},
	{MYVK_LEFT,KK_A},
	{MYVK_RIGHT,KK_D},

	{MYVK_ENTER,KK_ENTER},
	{MYVK_ENTER,KK_DOWN},
	{MYVK_ENTER,KK_UP},

	{MYVK_BEACON,KK_OEMCLOSEBRACKETS},
	{MYVK_BEACON,KK_SPACE},
	{MYVK_BEACON,KK_LEFT},

	{MYVK_PURGE,KK_OEMOPENBRACKETS},
	{MYVK_PURGE,KK_Q},
	{MYVK_PURGE,KK_RIGHT},
#if _DEBUG
	{MYVK_GAME_CLEAR,KK_F1},
	{MYVK_GAME_OVER,KK_F2},
#endif
};

static AxisConversion AxisConversions[AXIS_CONVERSIOINS_MAX]{
	{MYVA_MX,MOUSE_X},
	{MYVA_MY,MOUSE_Y},
	{MYVA_GLX,GAMEPAD_LX},
	{MYVA_GLY,GAMEPAD_LY},
	{MYVA_GRX,GAMEPAD_LRX},
	{MYVA_GRY,GAMEPAD_LRY},
};

void InitInputLogger(HWND hWnd, HINSTANCE hIns) {
	Keyboard_Initialize();
	Mouse_Initialize(hWnd);
	gamepad->Init(hWnd, hIns);


	padData = previous = trigger = release = 0;
	ZeroMemory(currentAxis, sizeof(currentAxis));
	ZeroMemory(previousAxis, sizeof(previousAxis));

	inputloggerMode = LOGGER_NORMAL;
	recordCurrent = NULL;
	for (size_t i = 0; i < MYVA_MAX; i++)
	{
		free(recordCurrentAxis[i]);
		recordCurrentAxis[i] = NULL;
	}
	recordFrame = 0;
	recordTraceFrame = 0;

	const char f[] = "keylogger.dat";
	SetRecordFilename(f, sizeof(f));
}


void UninitInputLogger() {

	free(recordCurrent);
	recordCurrent = NULL;

	for (size_t i = 0; i < MYVA_MAX; i++)
	{
		free(recordCurrentAxis[i]);
		recordCurrentAxis[i] = NULL;
	}
	free(recordFilename);
	recordFilename = NULL;

	Mouse_Finalize();

}

void UpdateInputLogger() {
	gamepad->Update();

	previous = padData;
	for (size_t i = 0; i < MYVA_MAX; i++) {
		previousAxis[i] = currentAxis[i];
		currentAxis[i] = 0;
	}

	if (inputloggerMode == LOGGER_NORMAL || inputloggerMode == LOGGER_RECORD) {
		padData = 0;

		for (int i = 0; i < KEY_CONVERSIOINS_MAX; i++)
		{
			if (KeyConversions[i].realKey == 0)
				continue;

			if (KeyConversions[i].realKey < KK_MAX) {
				if (Keyboard_IsKeyDown((Keyboard_Keys)KeyConversions[i].realKey)) {
					padData |= (InputLoggerType)(1u) << KeyConversions[i].virtualKey;
				}
			}
			else if (KeyConversions[i].realKey < MOUSE_BUTTONS_MAX) {
				if (Mouse_IsKeyDown((Mouse_Buttons)KeyConversions[i].realKey)) {
					padData |= (InputLoggerType)(1u) << KeyConversions[i].virtualKey;
				}
			}
			else if (KeyConversions[i].realKey < GAMEPAD_BUTTONS_MAX) {
				if (gamepad->IsButtonDown((GamepadButtons)KeyConversions[i].realKey)) {
					padData |= (InputLoggerType)(1u) << KeyConversions[i].virtualKey;
				}
			}
		}

		for (int i = 0; i < AXIS_CONVERSIOINS_MAX; i++)
		{
			if (AxisConversions[i].realAxis == 0)
				continue;

			if (AxisConversions[i].realAxis < MOUSE_AXIS_MAX) {
				currentAxis[(int)AxisConversions[i].virtualAxis] = Mouse_GetAxis((Mouse_Axis)AxisConversions[i].realAxis);

				if (AxisConversions[i].realAxis == MOUSE_X) {
					axisMaxs[(int)AxisConversions[i].virtualAxis] = SCREEN_WIDTH;
				}
				else {
					axisMaxs[(int)AxisConversions[i].virtualAxis] = SCREEN_HEIGHT;
				}
			}
			else if (AxisConversions[i].realAxis < GAMEPAD_AXIS_MAX) {
				currentAxis[(int)AxisConversions[i].virtualAxis] = gamepad->GetAxisInt((GamepadAxis)AxisConversions[i].realAxis);
				axisMaxs[(int)AxisConversions[i].virtualAxis] = gamepad->stickMax;

			}
		}

		if (inputloggerMode == LOGGER_RECORD) {
			recordCurrent[recordFrame] = padData;
			for (size_t i = 0; i < MYVA_MAX; i++)
			{
				recordCurrentAxis[i][recordFrame] = currentAxis[i];

			}
			recordFrame++;
			if (recordFrame >= gRecordframeMax) {
				RecordEnd();
			}
		}
	}

	else if (inputloggerMode == LOGGER_TRACE) {
		padData = recordCurrent[recordTraceFrame];

		for (size_t i = 0; i < MYVA_MAX; i++) {
			currentAxis[i] = recordCurrentAxis[i][recordTraceFrame];
		}

		recordTraceFrame++;

		if (recordTraceFrame >= recordFrame) {
			TraceEnd();
		}
	}
	trigger = (previous ^ padData) & padData;
	release = (previous ^ padData) & previous;
}

bool PressInputLogger(VirtualKey key) {
	return padData & ((InputLoggerType)(1u) << (int)key);
}
bool TriggerInputLogger(VirtualKey key) {
	return trigger & ((InputLoggerType)(1u) << (int)key);
}
bool ReleaseInputLogger(VirtualKey key) {
	return release & ((InputLoggerType)(1u) << (int)key);
}
int GetInputLoggerAxisInt(VirtualAxis axis) {
	return currentAxis[(int)axis];
}
int GetInputLoggerAxisAmountInt(VirtualAxis axis) {
	return  currentAxis[(int)axis] - previousAxis[(int)axis];
}
float GetInputLoggerAxis(VirtualAxis axis) {
	return GetInputLoggerAxisInt(axis) / (float)axisMaxs[(int)axis];

}
float GetInputLoggerAxisAmount(VirtualAxis axis) {
	return GetInputLoggerAxisAmountInt(axis) / (float)axisMaxs[(int)axis];
}

void InputLoggerProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Keyboard_ProcessMessage(uMsg, wParam, lParam);
	Mouse_ProcessMessage(uMsg, wParam, lParam);
}

void RecordStart(int recordFrameMax) {
	gRecordframeMax = recordFrameMax;
	free(recordCurrent);

	recordCurrent = (InputLoggerType*)malloc(sizeof(InputLoggerType) * recordFrameMax);
	if (recordCurrent == NULL) {
		throw  "Out of memory";
		return;
	}


	for (size_t i = 0; i < MYVA_MAX; i++)
	{
		free(recordCurrentAxis[i]);

		recordCurrentAxis[i] = (int*)malloc(sizeof(recordCurrentAxis[i]) * recordFrameMax);
		if (recordCurrentAxis[i] == NULL) {
			throw  "Out of memory";
			return;
		}
	}

	inputloggerMode = LOGGER_RECORD;
	recordFrame = 0;
}

void RecordEnd() {
	FILE* fp = fopen(recordFilename, "wb");
	fwrite(&recordFrame, sizeof(recordFrame), 1, fp);

	fwrite(recordCurrent, sizeof(InputLoggerType), recordFrame, fp);
	for (size_t i = 0; i < MYVA_MAX; i++)
	{
		fwrite(recordCurrentAxis[i], sizeof(recordCurrentAxis[i]), recordFrame, fp);
	}
	fclose(fp);

	inputloggerMode = LOGGER_NORMAL;
}

void RecordLoad() {

	FILE* fp = fopen(recordFilename, "rb");
	fread(&recordFrame, sizeof(recordFrame), 1, fp);


	free(recordCurrent);

	recordCurrent = (InputLoggerType*)malloc(sizeof(InputLoggerType) * recordFrame);
	if (recordCurrent == NULL) {
		throw  "Out of memory";
		return;
	}
	for (size_t i = 0; i < MYVA_MAX; i++)
	{
		free(recordCurrentAxis[i]);

		recordCurrentAxis[i] = (int*)malloc(sizeof(recordCurrentAxis[i]) * recordFrame);
		if (recordCurrentAxis[i] == NULL) {
			throw  "Out of memory";
			return;
		}
	}

	fread(recordCurrent, sizeof(InputLoggerType), recordFrame, fp);

	for (size_t i = 0; i < MYVA_MAX; i++)
	{
		fread(recordCurrentAxis[i], sizeof(recordCurrentAxis[i]), recordFrame, fp);
	}
	fclose(fp);
}

void TraceStart() {
	recordTraceFrame = 0;
	inputloggerMode = LOGGER_TRACE;
}

void TraceEnd() {
	recordTraceFrame = 0;
	inputloggerMode = LOGGER_NORMAL;
}

bool IsTrace() {
	return (inputloggerMode == 2);
}

void SetRecordFilename(const char* f, size_t size) {
	if (size <= 0) {
		return;
	}

	free(recordFilename);
	recordFilename = (char*)malloc(size + 1);

	if (recordFilename == NULL) {
		throw  "Out of memory";
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		recordFilename[i] = f[i];
	}
	recordFilename[size] = '\0';
}


void DebugPrintInputLogger() {
	for (int i = 0; i < KK_MAX; i++) {
		if (Keyboard_IsKeyDown((Keyboard_Keys)i)) {
			DebugPrintf("%d\n", i);
		}
	}
}