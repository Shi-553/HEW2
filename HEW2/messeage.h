#pragma once

#include <d3dx9.h>


void InitMesseage();
void UninitMesseage();

void ClearMesseageOffset();

void SetMessageColor(D3DCOLOR c);

void DrawMesseage(const char* str, va_list argp);
void DrawMesseage(const char* str, ...);

//�f�o�b�O�p
void TestMessage();